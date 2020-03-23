# apps

Currently gets all the executable app inside the system PATH.

### Usage

The app prints out the names of the apps that can be found in the system PATH.

### Build steps

1. Download the [Mingw Compiler](https://osdn.net/projects/mingw/releases/), installing it and adding to PATH. It is also possile (and recommanded) to use the [scoop](https://scoop.sh/) package manager : `scoop install gcc make`
2. Make sure `gcc.exe` and `make` is in your PATH.
3. Clone this repo (`git clone https://gitlab.com/xdavidel/apps.git`)
4. Run `make` 

### Build with TCC

The Tiny C Compiler can produce smaller size apps and compiles faster most of the time.

1. Download the [Tiny C Compiler](http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.27-win32-bin.zip).
3. Make sure `tcc.exe` is in your PATH.
4. Clone this repo (`git clone https://gitlab.com/xdavidel/apps.git`)
5. Run `maketcc.bat` 

### Credits

* [dirent.h](https://github.com/tronkko/dirent/tree/master/include/stretchy_buffer.h) - by [Toni Rönkkö](https://github.com/tronkko)
  
### Contributing

All issues and PRs related to fixing bugs or other strange behavior are welcome. 

### License

This project is licensed under the GNU General Public License v3.0. See LICENSE for more details.

