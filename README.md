# Overview
__ASCII Media Player written in C.__

Terminal layout is done using _ncurses_ library. \
Video decoding is done using _ffmpeg-dev_ libraries.gi

# Table of Contents
- [Installation](#installation)
    - [Linux](#linux)
    - [Windows](#windows)
    - [MacOS](#macos)
- [Usage](#usage)
- [Updates](#updates)
- [Bugs](#bugs)
- [License](#license)

# How to Install and Run {#installation}
### Linux: {#linux}
Download or clone this repository 
```
git clone https://github.com/rm-a0/ASCII-Video-Player
```
Install [__ffmpeg__](https://github.com/FFmpeg/FFmpeg) and [__ncurses__](https://github.com/mirror/ncurses) before compilation
```
sudo apt install libncurses-dev
sudo apt install ffmpeg
```
Compile using __make__
```
make
```
> [!NOTE]
> If compilation fails make sure you have correct library and include paths specified in the Makefile.
> ```makefile
> LDPATHS = -L/path/to/libraries
> INCPATHS = -I/path/to/include
> ```
Run using
```
./video_player
```
### Windows: {#windows}
Currently not supported on Windows.
Statically linked libraries and CMake will be added in the future.
### MacOS: {#macos}
Currently not supported on MacOS.
CMake will be added in the future.

# How to Use {#usage}


# Updates and Features {#updates}
- [x]  Dynamic window resizing
- [x]  Help instructions
- [x]  Pause and Resume commands
- [ ]  Enhanced user interface
- [ ]  Video playback in color
- [ ]  Video quality filter
- [ ]  Video speed filter
- [ ]  CMake and DLLs for MacOS and Windows support
- [ ]  Semaphore tweaks for MacOS

# Bugs and Issues {#bugs}
- [x]  Resizing causes crash when video is playing
- [x]  Windows are not being resized properly
- [x]  Major memory leaks after exiting program
- [ ]  Resizing causes crash when font is too small (Ctrl -)
- [ ]  Resizing causes crash when terminal is too small

# License {#license}