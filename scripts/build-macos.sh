#!/bin/bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cmake -S "$ROOT" -B "$ROOT/build" -G Xcode -DCMAKE_BUILD_TYPE=Release
cmake --build "$ROOT/build" --config Release --target Glass_VST3 Glass_AU Glass_Standalone
printf '\nBuilt products: %s/build/Glass_artefacts/Release\n' "$ROOT"
