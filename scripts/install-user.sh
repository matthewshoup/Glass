#!/bin/bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"; A="$ROOT/build/Glass_artefacts/Release"
mkdir -p "$HOME/Library/Audio/Plug-Ins/VST3" "$HOME/Library/Audio/Plug-Ins/Components"
cp -R "$A/VST3/Glass.vst3" "$HOME/Library/Audio/Plug-Ins/VST3/"
cp -R "$A/AU/Glass.component" "$HOME/Library/Audio/Plug-Ins/Components/"
echo "Installed Glass VST3 + AU."
