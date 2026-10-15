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
if /i "%~1"=="linked" goto linked
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /MDd /Od /RTC1 /DQUEUE_TEST_ALLOCATOR /Fo:build\ /Fe:build\queue_review.exe Queue.c test.c
if errorlevel 1 goto failed
if /i "%~1"=="test" (
    "build\queue_review.exe"
    if errorlevel 1 goto failed
)
echo Done. Run: .\build\queue_review.exe
goto success

:exam
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /MDd /Od /RTC1 /Fo:build\ /Fe:build\queue_exam.exe "考试背诵版\队列_考试最小背诵版.c"
if errorlevel 1 goto failed
"build\queue_exam.exe"
if errorlevel 1 goto failed
goto success

:linked
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /MDd /Od /RTC1 /Fo:build\ /Fe:build\linked_queue_exam.exe "考试背诵版\链式队列_带头结点.c"
if errorlevel 1 goto failed
"build\linked_queue_exam.exe"
if errorlevel 1 goto failed
goto success

:failed
popd
exit /b 1

:success
popd
endlocal
exit /b 0

