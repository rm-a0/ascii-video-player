# Overview
__ASCII Media Player written in C.__

Terminal layout is done using _ncurses_ library. \
Video decoding is done using _ffmpeg-dev_ libraries.

# Table of Contents
- [Description](#description)
- [Installation](#how-to-install-and-run)
    - [Linux](#linux)
    - [Windows](#windows)
    - [MacOS](#macos)
- [Usage](#how-to-use)
- [Updates](#updates-and-features)
- [Bugs](#bugs-and-issues)
- [License](#license)

# Description

After execution, terminal window will be split into 2 parts.
<pre>
+-------------------------+
|                         |
|       Main Window       |
|                         |
+-------------------------+
|      Command Window     |
+-------------------------+
</pre>
In the command window, you can enter [commands](#list-of-commands), while the main window displays most of the content using ASCII characters.

Decoding, frame separation, and conversion occur dynamically at runtime without the need for temporary folders.

Synchronization and multithreading between the main window and command window are achieved using semaphores and shared variables.

Dynamic window resizing relies on _SIGWINCH_ (from signal.h), which may encounter issues on Windows but should function correctly on Unix-based operating systems, including MacOS.
# How to Install and Run
### Linux:
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
### Windows:
Currently not supported on Windows.
Statically linked libraries and CMake will be added in the future.
### MacOS:
Currently not supported on MacOS.
CMake will be added in the future.

# How to Use
After you run the program type _help_ to display instructions

### List of commands
| Command                       | Description                                 |
|-------------------------------|---------------------------------------------|
| `help`                        | Displays instructions                       |
| `exit`, `quit`                | Exits the program                           |
| `play [file]`                 | Plays specified file                        |
| `stop`, `pause`               | Stops video that is currently playing       |
| `resume`                      | Resumes a paused video                      |
| `end`                         | Ends video that is currently playing        |
| `speed [float]`               | Changes speed of video playback globally    |

# Updates and Features
- [x]  Dynamic window resizing
- [x]  Help instructions
- [x]  Pause and Resume commands
- [ ]  Enhanced user interface
- [ ]  Video playback in color
- [ ]  Video quality filter
- [x]  Video speed filter
- [ ]  CMake and DLLs for MacOS and Windows support
- [ ]  Semaphore tweaks for MacOS

# Bugs and Issues
- [x]  Resizing causes crash when video is playing
- [x]  Windows are not being resized properly
- [x]  Major memory leaks after exiting program
- [x]  Thread arguments not accessible in the thread
- [x]  After video ends new video does not play (pause causes deadlock)
- [ ]  Resizing causes crash (Illegal operation) when font is too small (Ctrl -)
- [x]  Resizing causes crash when terminal is too small

# License