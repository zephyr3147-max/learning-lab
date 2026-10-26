@echo off
call "E:\VS产品\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b 1
cd /d "%~dp0.."
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /Fo:"build\merge_sorted.obj" /Fe:"build\merge_sorted.exe" "单链表_有序合并_题解.c"
exit /b %errorlevel%
