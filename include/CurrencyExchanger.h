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

#pragma once

#include <string>
#include <map>

class CurrencyExchanger {
public:

	CurrencyExchanger();
	~CurrencyExchanger();

	// ####################################################

	// Getter

	const std::string& lastError(void) const;

	const std::string& exchangeRateDate(void) const;

	const std::string& baseCurrency(void) const;

	bool hasRate(const std::string& _currency);

	std::string rates(void);

	double exchangeRate(const std::string& _targetCurrency);

	double exchangeValue(double _value, const std::string& _fromCurrency, const std::string& _toCurrency);

	// ####################################################

	// Setter

	void clearData(void);

	// ####################################################

	// Data sync

	bool syncFromEuropeanCentralBank(int _timeout);

private:

	std::string						m_error;
	std::string						m_lastDate;

	std::string						m_baseCurrency;
	std::map<std::string, double>	m_rates;

	CurrencyExchanger(CurrencyExchanger&) = delete;
	CurrencyExchanger& operator = (CurrencyExchanger&) = delete;
};