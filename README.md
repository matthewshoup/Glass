# GLASS Rev III
macOS AU/VST3/Standalone 300B-inspired harmonic processor built with JUCE 8 + CMake.

Controls: Drive, 2nd Harmonic, Bias, Mix, Output, Original Circuit.

## Build on macOS
Requires Xcode command-line tools, CMake 3.22+, Git.

    ./scripts/build-macos.sh
    ./scripts/install-user.sh

CMake fetches JUCE 8.0.6 automatically. Targets universal arm64 + x86_64 and macOS 11+.

Rev III is a physically motivated real-time model, not a component-by-component SPICE solver. Circuit-sensitive values are centralized in Source/CircuitCalibration.h for calibration against the original schematic/SPICE/bench measurements.
