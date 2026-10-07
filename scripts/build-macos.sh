#!/bin/bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cmake -S "$ROOT" -B "$ROOT/build" -G Xcode -DCMAKE_BUILD_TYPE=Release
cmake --build "$ROOT/build" --config Release --target Glass_VST3 Glass_AU Glass_Standalone

ART="$ROOT/build/Glass_artefacts/Release"
# Give every Mach-O/bundle a valid ad-hoc signature. This fixes malformed/unsigned
# local-development bundles, but is intentionally not represented as Apple notarization.
find "$ART" -type f -perm -111 -exec codesign --force --sign - {} \; || true
for bundle in "$ART"/*.vst3 "$ART"/*.component "$ART"/*.app; do
  [ -e "$bundle" ] || continue
  codesign --force --deep --sign - "$bundle"
  codesign --verify --deep --strict --verbose=2 "$bundle"
done
printf '\nBuilt and ad-hoc signed products: %s\n' "$ART"
