@echo off
setlocal
chcp 65001 >nul
rem Usage: build.bat builds; build.bat test builds and runs the checks.
rem Keep this script ASCII-only to work with the cmd.exe system code page.
set "SRCDIR=%~dp0"
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo [ERROR] Visual Studio Installer not found.
    exit /b 1
)
for /f "usebackq delims=" %%i in (`"%VSWHERE%" -utf8 -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSPATH=%%i"
if not defined VSPATH (
    echo [ERROR] No Visual Studio C compiler found.
    exit /b 1
)
set "PATH=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer;%PATH%"
call "%VSPATH%\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b 1
pushd "%SRCDIR%"
if errorlevel 1 exit /b 1
if not exist "build" mkdir "build"
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /MDd /Od /RTC1 /DSQLIST_TEST_ALLOCATOR /Fo:build\ /Fe:build\sqlist_review.exe SqList.c test.c
if errorlevel 1 (
    popd
    exit /b 1
)
if /i "%~1"=="test" (
    "build\sqlist_review.exe"
    if errorlevel 1 (
        popd
        exit /b 1
    )
)
echo Done. Run: .\build\sqlist_review.exe
popd
endlocal
