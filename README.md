# OBS Live Indicator Plugin

## Description
This plugin adds a small dock to OBS Studio that displays a red "● LIVE" indicator whenever streaming is active.

## Build Instructions

### Prerequisites
- Windows
- Visual Studio 2019 or 2022 (Desktop development with C++)
- CMake 3.20 or newer
- Qt development libraries (matching OBS's Qt version)
- OBS Studio source or development files (recommended to build in-tree)

### Building In-tree (Recommended)
1. Clone `obs-studio` repository and check out your OBS version.
2. Place this plugin folder inside `obs-studio/plugins/obs-live-indicator/`.
3. From the root of `obs-studio`, create a build directory and run: cmake -G "Visual Studio 17 2022" -A x64
4. Build the solution or the plugin project.
5. Copy the resulting DLL from the build folder to your OBS install `obs-plugins/64bit/`.

### Out-of-tree Building
Adjust `CMakeLists.txt` and provide paths to OBS includes/libs and Qt manually.

---

## Using GitHub Actions CI

Push this repo to GitHub, and the workflow at `.github/workflows/windows.yml` will build the plugin for you automatically.  
Download the artifact from the Actions tab and place it into your OBS plugins folder.

---

## Usage

- Load OBS Studio.
- The "Live Indicator" dock will be available.
- When streaming starts, the dock shows "● LIVE" in red.
- When streaming stops, the dock hides.

---

## License

MIT License
