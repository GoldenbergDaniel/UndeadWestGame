#!/bin/bash
set -e

SOURCES="sokol_app.h sokol_time.h"
DEFINES="-DSOKOL_IMPL -DSOKOL_NO_ENTRY -DSOKOL_GLCORE"

TARGET="darwin_amd64"
if [[ $1 == "-target" ]]; then TARGET=$2; fi

LANG="-x c"
if [[ $TARGET == "darwin_amd64" ]]; then LANG="-x objective-c"; fi

if [[ $TARGET == "darwin_amd64" ]]; then LIB_NAME="libsokol_darwin_amd64.a"; fi
if [[ $TARGET == "linux_amd64"  ]]; then LIB_NAME="libsokol_linux_amd64.a"; fi

echo "[target:$TARGET]"

clang $DEFINES $LANG $SOURCES -O2 -c
ar -cs lib/$LIB_NAME *.o
rm -f *.o
