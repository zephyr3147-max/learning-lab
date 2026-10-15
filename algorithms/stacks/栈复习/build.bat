@echo off
setlocal
chcp 65001 >nul
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
if /i "%~1"=="exam" goto exam
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /MDd /Od /RTC1 /DSTACK_TEST_ALLOCATOR /Fo:build\ /Fe:build\stack_review.exe Stack.c test.c
if errorlevel 1 goto failed
if /i "%~1"=="test" (
    "build\stack_review.exe"
    if errorlevel 1 goto failed
)
echo Done. Run: .\build\stack_review.exe
goto success

:exam
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /MDd /Od /RTC1 /Fo:build\ /Fe:build\stack_exam.exe "考试背诵版\栈_考试最小背诵版.c"
if errorlevel 1 goto failed
"build\stack_exam.exe"
if errorlevel 1 goto failed
goto success

:failed
popd
exit /b 1

:success
popd
endlocal
exit /b 0

