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
#include "CurrencyExchangerAPI.h"
#include "CurrencyExchanger.h"

static CurrencyExchanger g_ex{};

bool CurrencyExchangerAPI::syncFromEuropeanCentralBank(int _timeout) {
	return g_ex.syncFromEuropeanCentralBank(_timeout);
}

const char* CurrencyExchangerAPI::lastError(void) {
	return g_ex.lastError().c_str();
}

const char* CurrencyExchangerAPI::exchangeRateDate(void) {
	return g_ex.exchangeRateDate().c_str();
}

const char* CurrencyExchangerAPI::baseCurrency(void) {
	return g_ex.baseCurrency().c_str();
}

bool CurrencyExchangerAPI::hasRate(const char* _currency) {
	return g_ex.hasRate(_currency);
}

const char* CurrencyExchangerAPI::rates(void) {
	return g_ex.rates().c_str();
}

double CurrencyExchangerAPI::exchangeRate(const char* _targetCurrency) {
	return g_ex.exchangeRate(_targetCurrency);
}

double CurrencyExchangerAPI::exchangeValue(double _value, const char* _fromCurrency, const char* _toCurrency) {
	return g_ex.exchangeValue(_value, _fromCurrency, _toCurrency);
}

void CurrencyExchangerAPI::clearData(void) {
	g_ex.clearData();
}