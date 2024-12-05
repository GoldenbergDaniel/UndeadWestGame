#!/bin/bash
set -e

SRC="main.c"
OUT="undeadwest"

MODE="dev"
if [[ $1 == "d" || $1 == "debug"   ]]; then MODE="debug"; fi
if [[ $1 == "r" || $1 == "release" ]]; then MODE="release"; fi

TARGET="linux_amd64"
if [[ $1 == "-target" ]]; then TARGET=$2; fi
if [[ $2 == "-target" ]]; then TARGET=$3; fi

if [[ $MODE == "dev"     ]]; then CFLAGS="-std=c17 -O0"; fi
if [[ $MODE == "debug"   ]]; then CFLAGS="-std=c17 -Og -g -DDEBUG"; fi
if [[ $MODE == "release" ]]; then CFLAGS="-std=c17 -O2 -DRELEASE"; fi

if [[ $MODE == "dev"     ]]; then WFLAGS="-Wpedantic -Wno-initializer-overrides"; fi
if [[ $MODE == "debug"   ]]; then WFLAGS="-Wall -Wpedantic -Wno-initializer-overrides -Wno-missing-braces"; fi
if [[ $MODE == "release" ]]; then WFLAGS="-Wno-initializer-overrides"; fi

if [[ $TARGET == "darwin_amd64" ]]; then LFLAGS="-Iext/ -Lext/sokol/lib/ -lsokol_darwin_amd64 -framework OpenGL -framework Cocoa"; fi
if [[ $TARGET == "linux_amd64"  ]]; then LFLAGS="-Iext/ -Lext/sokol/lib/ -lsokol_linux_amd64 -lX11 -lXi -lXcursor -lGL -ldl -lpthread -lm"; fi

echo "[source:$SRC]"
echo "[target:$TARGET]"
echo "[mode:$MODE]"

# -target arm64-apple-macos14
if [[ ! -d "out" ]]; then mkdir out; fi
clang $CFLAGS $WFLAGS $FSAN src/$SRC $LFLAGS -o out/$OUT
#if [[ $MODE == "dev" ]]; then out/$OUT; fi
