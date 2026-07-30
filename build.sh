#!/usr/bin/env sh
set -eu

build_type="${1:-Release}"

cmake -S . -B build -DCMAKE_BUILD_TYPE="$build_type"
cmake --build build --config "$build_type"

if [ -x "build/SimulationApp" ]; then
    exec ./build/SimulationApp
elif [ -x "build/$build_type/SimulationApp" ]; then
    exec "build/$build_type/SimulationApp"
else
    echo "Build succeeded, but the SimulationApp executable was not found." >&2
    exit 1
fi
