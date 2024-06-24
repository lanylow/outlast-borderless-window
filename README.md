# Outlast Borderless Window Mod [![License](https://img.shields.io/badge/License-GPL3.0-green.svg)](https://github.com/lanylow/outlast-borderless-window/blob/main/LICENSE) ![OS](https://img.shields.io/badge/OS-Windows-yellow.svg)

Free and open-source mod for Outlast that adds the borderless window funcionality. Compatible with all versions of the game released on Windows.

## FAQ

### Why?
The game often completely freezes when Alt-Tabbing in fullscreen, which is especially annoying when trying to follow guides online. This mod solves that issue.

### How do I install it?
1. Download the archive from the [latest release](https://github.com/lanylow/genshin-utility/releases).
2. Open the directory where Outlast is installed.
3. Open the archive you downloaded.
4. If you're playing on the 64-bit version of the game, extract `64\dinput8.dll` into `Outlast\Binaries\Win64`, otherwise extract `32\dinput8.dll` into `Outlast\Binaries\Win32`.
5. Open the game and enable fullscreen in settings, the game should now be in borderless window mode.

## Utilized third-party libraries

* [minhook](https://github.com/TsudaKageyu/minhook) - API Hooking Library for Windows

## License

This project is licensed under the GPL-3.0 License - see the [LICENSE](https://github.com/lanylow/outlast-borderless-window/blob/main/LICENSE) file for details.
