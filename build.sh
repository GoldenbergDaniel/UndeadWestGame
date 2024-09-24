#!/bin/bash
set -e

SRC="main.c"
OUT="undeadwest"

MODE="dev"
if [[ $1 == "d" || $1 == "debug"   ]]; then MODE="debug"; fi
if [[ $1 == "r" || $1 == "release" ]]; then MODE="release"; fi

TARGET="darwin_amd64"
if [[ $1 == "-target" ]]; then TARGET=$2; fi
if [[ $2 == "-target" ]]; then TARGET=$3; fi

if [[ $1 == "fsan" ]]; then FSAN="-fsanitize=undefined"; fi

if [[ $MODE == "dev"     ]]; then CFLAGS="-std=c17 -O0"; fi
if [[ $MODE == "debug"   ]]; then CFLAGS="-std=c17 -Og -g -DDEBUG"; fi
if [[ $MODE == "release" ]]; then CFLAGS="-std=c17 -O2 -DRELEASE"; fi

if [[ $MODE == "dev"     ]]; then WFLAGS="-Wpedantic -Wno-initializer-overrides"; fi
if [[ $MODE == "debug"   ]]; then WFLAGS="-Wall -Wpedantic -Wno-initializer-overrides -Wno-missing-braces"; fi
if [[ $MODE == "release" ]]; then WFLAGS="-Wno-initializer-overrides"; fi

if [[ $TARGET == "darwin_amd64" ]]; then LFLAGS="-Iextern/ -Lextern/sokol/lib/ -lsokol -framework OpenGL -framework Cocoa"; fi
if [[ $TARGET == "linux_amd64"  ]]; then LFLAGS="-Iextern/ -Lextern/sokol/lib/ -lsokol"; fi

echo "[source:$SRC]"
echo "[target:$TARGET]"
echo "[mode:$MODE]"
if [[ $2 == "fsan" ]]; then echo "[fsan:on]"; fi
if [[ $2 != "fsan" ]]; then echo "[fsan:off]"; fi
# shadertoh src/shaders/ src/render/shaders.h

# -target arm64-apple-macos14
if [[ ! -d "out" ]]; then mkdir out; fi
cc $CFLAGS $WFLAGS $FSAN $LFLAGS src/$SRC -o out/$OUT
if [[ $MODE == "dev" ]]; then out/$OUT; fi
