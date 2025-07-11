# 🎧 Uphonic

**Uphonic** is a digital audio workstation (DAW) designed to be a modern, lightweight alternative to tools like FL Studio. Built from the ground up using C++, Uphonic aims to provide a fast, modular, and extensible environment for music production.

> ⚠️ This project is in early development. Expect rapid changes and limited functionality.

---

## ✨ Features (So Far)

- 🎼 Basic MIDI composer  
- 🎛️ VST2 plugin support  
- 🪶 Lightweight and minimal design philosophy  

---

## 🧀 Initial Setup
Choose a directory you want to clone the project to.
```bash
git clone --recursive https://github.com/boxDev2008/Uphonic.git
```

## 🛠️ Building Uphonic

Currently, Uphonic supports building on **Windows** via simple batch scripts:

```bash
generate.bat
build.bat
```
Also, Uphonic supports building on **Linux** (X11):
```bash
./tools/premake5 gmake
make
```
macOS support is planned, but is expected to take longer due to limited access to testers on that platform.
#### 📦 Dependencies and build instructions for other platforms will be added as the project evolves.


## 🚧 Roadmap
- Cross-platform support (Linux, macOS)
- Audio engine improvements
- Full mixer and track view
- Plugin manager and automation
- UI/UX enhancements
- Even more audio tools

## 🤝 Contributing
We welcome contributions! Whether it's bug fixes, feature suggestions, or code improvements, feel free to open an issue or submit a pull request. See [**CONTRIBUTING.md**](CONTRIBUTING.md) for details.

## 📄 License
This project is licensed under the [GNU General Public License v3.0 (GPLv3)](https://www.gnu.org/licenses/gpl-3.0.en.html).
