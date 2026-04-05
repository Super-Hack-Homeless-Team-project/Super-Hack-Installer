# Super Hack Installer

An experimental Geometry Dash mod built with the Geode SDK.

## 🚀 Features
- Hooks directly into the game via Geode.
- Easy integration with other mods.
- Clean, modern C++23 codebase.

## 📦 Requirements
- [Geode SDK](https://geode-sdk.org) (set the `GEODE_SDK` environment variable to point to the SDK).
- CMake >= 3.21
- Visual Studio (MSVC) or any compiler supporting C++23.

## 🔧 Build Instructions
```bash
# Remove old build
rmdir /s /q build

# Build again
geode build




Super Hack Installer/
├─ src/
│  └─ main.cpp
├─ CMakeLists.txt
└─ README.md




