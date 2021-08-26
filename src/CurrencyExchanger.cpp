/*

MIT License

Copyright (c) 2021 Alexander Kuester

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "pch.h"
#include "CurrencyExchanger.h"

// Curl
#include <curl/curl.h>
#include <curl/easy.h>

// C++
#include <list>
#include <sstream>

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

CurrencyExchanger::CurrencyExchanger() : m_lastDate("1000-01-01") {}

CurrencyExchanger::~CurrencyExchanger() {}

// ####################################################

// Getter

const std::string& CurrencyExchanger::lastError(void) const { return m_error; }

const std::string& CurrencyExchanger::exchangeRateDate(void) const { return m_lastDate; }

const std::string& CurrencyExchanger::baseCurrency(void) const { return m_baseCurrency; }

bool CurrencyExchanger::hasRate(const std::string& _currency) {
	if (_currency == m_baseCurrency) { return true; }
	auto itm = m_rates.find(_currency);
	return itm != m_rates.end();
}

std::string CurrencyExchanger::rates(void) {
	std::string ret;
	bool first{ true };
	for (auto itm : m_rates) {
		if (!first) { ret.append(";"); }
		first = false;
		ret.append(itm.first);
	}
	return ret;
}

double CurrencyExchanger::exchangeRate(const std::string& _targetCurrency) {
	if (_targetCurrency == m_baseCurrency) { return 1.; }
	auto itm = m_rates.find(_targetCurrency);
	if (itm != m_rates.end()) {
		return itm->second;
	}
	else {
		return 0.;
	}
}

double CurrencyExchanger::exchangeValue(double _value, const std::string& _fromCurrency, const std::string& _toCurrency) {
	if (!hasRate(_fromCurrency)) { m_error = "'From' currency not found"; return 0.; }
	if (!hasRate(_toCurrency)) { m_error = "'To' currency not found"; return 0.; }
	double f = exchangeRate(_fromCurrency);
	if (f != 0.) {
		return (_value / f) * exchangeRate(_toCurrency);
	}
	else {
		m_error = "'From' currency rate is 0"; return 0.;
	}
}

// ####################################################

// Setter

void CurrencyExchanger::clearData(void) {
	m_rates.clear();
	m_baseCurrency = "";
}

// ####################################################

// Data sync

bool CurrencyExchanger::syncFromEuropeanCentralBank(int _timeout) {
	std::string curlURL("https://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml");
	std::string response;

	auto curl = curl_easy_init();
	if (!curl)
	{
		m_error = "Failed to initialize curl";
		return false;
	}

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Accept: application/xml");
	headers = curl_slist_append(headers, "Content-Type: application/xml");
	headers = curl_slist_append(headers, "charset: utf-8");

	curl_easy_setopt(curl, CURLOPT_URL, curlURL.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcrp/0.1");
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, _timeout);

	std::string header_string;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

	// Send the request
	CURLcode res = curl_easy_perform(curl);
	//std::cout << "URL Code received: " << res << std::endl;

	curl_easy_cleanup(curl);
	curl = NULL;

	// Check response
	if (res != CURLE_OK) {
		m_error = "Request to ECB failed";
		return false;
	}

	if (response.empty()) { m_error = "Invalid response from server"; return false; }

	if (response.find("<Cube currency='") == std::string::npos) {
		m_error = "Unexpected reponse syntax"; return false;
	}

	// Parse data
	clearData();
	m_baseCurrency = "EUR";

	std::list<std::string> lines;
	std::stringstream reader(response);
	std::string line;

	while (std::getline(reader, line)) {
		// Check if the line is the date line
		size_t ix = line.find("<Cube time='");
		if (ix != std::string::npos) {
			m_lastDate = line.substr(ix + 12);
			ix = m_lastDate.find("'");
			if (ix != std::string::npos) {
				m_lastDate = m_lastDate.substr(0, ix);
			}
			else {
				m_lastDate = "1000-01-01";
			}
		}
		
		// Check if the line is the currency line
		ix = line.find("<Cube currency='");
		if (ix != std::string::npos) {
			std::string currencyLine = line.substr(ix + 16);
			ix = currencyLine.find("'");
			if (ix != std::string::npos) {
				std::string currencyKey = currencyLine.substr(0, ix + 1);
				std::string rate = currencyLine.substr(ix);
				ix = rate.find("rate='");
				if (ix != std::string::npos) {
					rate = rate.substr(ix + 6);
					ix = rate.find("'");
					if (ix != std::string::npos) {
						rate = rate.substr(0, ix);
						std::stringstream converter(rate);
						double val;
						converter >> val;
						bool failed = false;
						if (!converter.fail()) {
							std::string rest;
							converter >> rest;
							if (rest.empty()) {
								m_rates.insert_or_assign(currencyKey, val);
							}
						}
					}
				}
			}
		}
	}

	if (m_rates.empty()) {
		m_error = "No data found";
		return false;
	}

	return true;
}