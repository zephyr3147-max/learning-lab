@echo off
setlocal
chcp 65001 >nul
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" exit /b 1
for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSPATH=%%i"
if not defined VSPATH exit /b 1
call "%VSPATH%\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b 1
pushd "%~dp0"
if errorlevel 1 exit /b 1
if not exist build mkdir build
if /i "%~1"=="exam" goto exam
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /Od /RTC1 /Fo:build\ /Fe:build\tree_review.exe BiTree.c test.c
if errorlevel 1 goto failed
if /i "%~1"=="test" (
    "build\tree_review.exe"
    if errorlevel 1 goto failed
)
goto success
:exam
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /Od /RTC1 /Fo:build\ /Fe:build\tree_exam.exe "考试背诵版\二叉树_考试最小背诵版.c"
if errorlevel 1 goto failed
"build\tree_exam.exe"
if errorlevel 1 goto failed
goto success
:failed
popd
exit /b 1
:success
popd
endlocal
exit /b 0
