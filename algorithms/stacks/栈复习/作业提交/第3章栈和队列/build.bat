@echo off
setlocal
chcp 65001 >nul
call "E:\VS产品\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 exit /b 1
cd /d "%~dp0"
if not exist build mkdir build
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /Fo:build\q1.obj /Fe:build\q1.exe 01_栈基本操作模拟.c
if errorlevel 1 exit /b 1
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /Fo:build\q2.obj /Fe:build\q2.exe 02_十进制转八进制.c
if errorlevel 1 exit /b 1
cl /nologo /TP /std:c++14 /EHsc /utf-8 /W4 /WX /Fo:build\q3.obj /Fe:build\q3.exe 03_同色区域颜色置换.cpp
if errorlevel 1 exit /b 1
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /Fo:build\q4.obj /Fe:build\q4.exe 04_队列操作.c
if errorlevel 1 exit /b 1
cl /nologo /TP /std:c++14 /EHsc /utf-8 /W4 /WX /Fo:build\q5.obj /Fe:build\q5.exe 05_双端循环队列.cpp
if errorlevel 1 exit /b 1
cl /nologo /TP /std:c++14 /EHsc /utf-8 /W4 /WX /Fo:build\q6.obj /Fe:build\q6.exe 06_列车编组.cpp
if errorlevel 1 exit /b 1
cl /nologo /TP /std:c++14 /EHsc /utf-8 /W4 /WX /Fo:build\q7.obj /Fe:build\q7.exe 07_链式循环队列.cpp
if errorlevel 1 exit /b 1
cl /nologo /TC /std:c17 /utf-8 /W4 /WX /Fo:build\q8.obj /Fe:build\q8.exe 08_表达式括号匹配.c
exit /b %errorlevel%
