@echo off
setlocal

set SRC=main.c
set OUT=undeadwest.exe

set MODE=dev
if "%1%"=="d"    set MODE=debug
if "%1%"=="r"    set MODE=release
if "%1%"=="push" set MODE=push

if "%MODE%"=="push" (
  echo - Pushing to Itch.io -
  pushd build || exit /b 1
    if not exist undead-west-windows mkdir undead-west-windows
    pushd undead-west-windows
      move ..\%OUT% .
      xcopy ..\..\res\ .\res\ /E /y
    popd
    butler push undead-west-windows goldenbergdev/undead-west:windows --userversion 0.7-dev || /b exit 1
  popd
  exit /b 0
)

if "%1%"=="d" (
  if "%2%"=="fsan" set FSAN= /fsanitize=address
)

set COMMON= /std:c17 /nologo /Iext\

if "%MODE%"=="dev"     set CFLAGS= /Od /DDEBUG
if "%MODE%"=="debug"   set CFLAGS= /Od /Z7 /W1 /DDEBUG
if "%MODE%"=="release" set CFLAGS= /O2 /DRELEASE

set LFLAGS= /link /incremental:no /libpath:ext\sokol\lib sokol.lib

echo [mode:%MODE%]

if     "%2"=="fsan" echo [fsan:on]
if not "%2"=="fsan" echo [fsan:off]

shadertoh src\shaders\ src\render\shaders.h

set BUILD=1
if "%MODE%"=="push" set BUILD=0

if "%BUILD%"=="1" (
  if not exist build mkdir build 
  cl %COMMON% %CFLAGS% %FSAN% src\%SRC% /Feout\%OUT% %LFLAGS% || exit /b 1
  del *.obj
)
