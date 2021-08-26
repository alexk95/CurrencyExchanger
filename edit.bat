@ECHO OFF
REM This script requires the following environment variables to be set:
REM 1. CURRENCY_EXCHANGER_ROOT
REM 2. DEVENV_ROOT

IF "%CURRENCY_EXCHANGER_ROOT%" == "" (
	ECHO Please specify the following environment variables: CURRENCY_EXCHANGER_ROOT
	goto END
)

IF "%DEVENV_ROOT%" == "" (
	ECHO Please specify the following environment variables: DEVENV_ROOT
	goto END
)

REM Setup eviroment
CALL "%CURRENCY_EXCHANGER_ROOT%\setupEnvironment.bat"

ECHO Launching development enviroment

REM Open project
START "" "%DEVENV_ROOT%\devenv.exe" "%CURRENCY_EXCHANGER_ROOT%\CurrencyExchanger.vcxproj"

:END