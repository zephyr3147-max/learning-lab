@echo off
setlocal
chcp 65001 >nul
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
for /f "usebackq delims=" %%i in (`"%VSWHERE%" -utf8 -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSPATH=%%i"
if not defined VSPATH exit /b 1
call "%VSPATH%\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b 1
pushd "%~dp0"
if not exist build mkdir build
for %%F in (*.c) do (
    cl /nologo /TC /std:c17 /utf-8 /W4 /WX /Od /RTC1 /Fo:build\ /Fe:"build\%%~nF.exe" "%%F"
    if errorlevel 1 exit /b 1
)
for %%F in (*.cpp) do (
    cl /nologo /TP /std:c++20 /EHsc /utf-8 /W4 /WX /Od /RTC1 /Fo:build\ /Fe:"build\%%~nF.exe" "%%F"
    if errorlevel 1 exit /b 1
)
popd
endlocal
