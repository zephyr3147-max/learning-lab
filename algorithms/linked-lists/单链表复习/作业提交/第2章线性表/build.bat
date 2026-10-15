@echo off
setlocal
chcp 65001 >nul
call "E:\VS产品\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b 1
cd /d "%~dp0"
if not exist build mkdir build
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /Fo:build\q3.obj /Fe:build\q3.exe 03_交替合并.c
if errorlevel 1 exit /b 1
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /Fo:build\q4.obj /Fe:build\q4.exe 04_删除开区间元素.c
if errorlevel 1 exit /b 1
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /Fo:build\q5.obj /Fe:build\q5.exe 05_有序链表合并.c
if errorlevel 1 exit /b 1
cl /nologo /TP /std:c++14 /EHsc /utf-8 /W4 /WX /Fo:build\q6.obj /Fe:build\q6.exe 06_有序链表去重.cpp
exit /b %errorlevel%