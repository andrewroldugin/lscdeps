# LSD - List dependencies for C/C++ files
## How to use:
```
./lsd --help
```
## How to build
### Requirements:
It requires `gtest` & `gmock` to be installed on your system for building tests.

To build only `lsd` delete `-lgtest` from `LDLIBS` in `Makefile` and run:
```
make lsd
```

To install required packages on ArchLinux run the following:
```
sudo pacman -S gtest gmock
```
### Building:
Using `gcc`:
```
make
```
Using `clang`:
```
./make_clang
```
To build & run tests:
```
make test
```
