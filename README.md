# CurrencyExchanger
A small library to get the current exchange rates and calculate currencies.

## Synchronization
The library provides the following sources of exchange rates:
- EuropeanCentralBank (ECB), base currency EUR (Euro), updated weekly, 32 target currencies

## Interface
The library has a language independent interface so it can be used with any language

### Build: Windows
- Install VisualStudio 2017 or newer
- Create two environment variables:
- - CURRENCY_EXCHANGER_ROOT : The directory this library is located at
- - DEVENV_ROOT : The directory where the VS2017 installation is located at (e.g. ...\Common7\IDE)
- use the build.bat To build the library

### Use: Windows
- To use the library you need also the curl library and zlib (Third_Party_Libraries)
