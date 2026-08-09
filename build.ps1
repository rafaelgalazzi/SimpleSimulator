$ErrorActionPreference = "Stop"

cmake -S . -B build
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

cmake --build build --config Debug
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

& .\build\Debug\simulator.exe
