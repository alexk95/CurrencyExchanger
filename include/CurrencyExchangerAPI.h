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

//! Contains functions to work with the CurrencyExchanger
namespace CurrencyExchangerAPI {

	//! @brief Will load the current exchange rates from the European Central bank
	//! If the return value is false, an error occured. The latest error can be retreived by calling the lastError() function.
	//! The base currency of the exchange rate is EUR (Euro)
	__declspec(dllexport) bool syncFromEuropeanCentralBank(int _timeout = 3000);

	//! @brief Will return the last occured error
	__declspec(dllexport) const char* lastError(void);

	//! @brief Will return the date the exchange rate is based on
	__declspec(dllexport) const char* exchangeRateDate(void);

	//! @brief Will return the base currency for the exchange rates
	__declspec(dllexport) const char* baseCurrency(void);

	//! @brief Will return true if the provided currency is listed in the CurrencyExchanger
	//! @param _currency The currency
	__declspec(dllexport) bool hasRate(const char* _currency);

	//! @brief Will return a string representation of all rates, all rates are separated by a semicolon ";"
	__declspec(dllexport) const char* rates(void);

	//! @brief Will return the exchange rate for the provided target currency
	//! Will return 1 if the target currency is the base currency
	//! Will return 0 if the target currency is not listed in the CurrencyExchanger
	//! @param _targetCurrency The currency
	__declspec(dllexport) double exchangeRate(const char* _targetCurrency);

	//! @brief Will exchange the provided value to the target currency
	//! @param _value The value to exchange
	//! @param _fromCurrency The currency of the provided value
	//! @param _toCurrency The target currency
	__declspec(dllexport) double exchangeValue(double _value, const char* _fromCurrency, const char* _toCurrency);

	//! @brief Will clear all the data in the CurrencyExchanger
	__declspec(dllexport) void clearData(void);

}
