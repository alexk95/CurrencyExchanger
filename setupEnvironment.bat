@ECHO OFF
REM This script requires the following environment variables to be set:
REM 1. CURRENCY_EXCHANGER_ROOT
REM 2. DEVENV_ROOT

REM Ensure that the setup will only be performed once
if "%CURRENCY_EXCHANGER_ENV_DEFINED%"=="1" (
	goto END
)

SET CURRENCY_EXCHANGER_ENV_DEFINED=1

ECHO Setup CurrencyExchanger lib environment

IF "%CURRENCY_EXCHANGER_ROOT%" == "" (
	ECHO Please specify the following environment variables: CURRENCY_EXCHANGER_ROOT
	goto END
)

IF "%DEVENV_ROOT%" == "" (
	ECHO Please specify the following environment variables: DEVENV_ROOT
	goto END
)

REM Set CURL Directory
IF "%CURL_ROOT%" == "" (
	SET CURL_ROOT=%CURRENCY_EXCHANGER_ROOT%\Third_Party_Libraries\curl
)
IF "%CURL_LIB%" == "" (
	SET CURL_LIB=%CURL_ROOT%\lib
)
IF "%CURL_INC%" == "" (
	SET CURL_INC=%CURL_ROOT%\include
)
IF "%CURL_DLL%" == "" (
	SET CURL_DLL=%CURL_ROOT%\bin
)
IF "%CURL_LIBD%" == "" (
	SET CURL_LIBD=%CURL_ROOT%\debug\lib
)
IF "%CURL_DLLD%" == "" (
	SET CURL_DLLD=%CURL_ROOT%\debug\bin
)

SET CURRENCY_EXCHANGER_INC=%CURRENCY_EXCHANGER_ROOT%\include;%CURL_INC%
SET CURRENCY_EXCHANGER_LIB=CurrencyExchanger.lib;libcurl.lib
SET CURRENCY_EXCHANGER_LIBD=CurrencyExchanger.lib;libcurl-d.lib
SET CURRENCY_EXCHANGER_LIB_ROOT=%CURRENCY_EXCHANGER_ROOT%\x64\Release;%CURL_LIB%
SET CURRENCY_EXCHANGER_LIBD_ROOT=%CURRENCY_EXCHANGER_ROOT%\x64\Debug;%CURL_LIBD%
SET CURRENCY_EXCHANGER_DLL=%CURRENCY_EXCHANGER_ROOT%\x64\Release\;%CURL_DLL%
SET CURRENCY_EXCHANGER_DLLD=%CURRENCY_EXCHANGER_ROOT%\x64\Debug\;%CURL_DLLD%

:END