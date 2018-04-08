@echo off
rem -- This batch file is used to set system ENV of wxWidgets
rem -- The ENV is: WXWIN

@echo Set wxWidgets development environment variable
set WXWIN=c:\\devtools\\Libs\\wxWidgets
@echo %WXWIN%

@echo Done
@echo.
@echo Open solution file

wxfreechart_vc14.sln
