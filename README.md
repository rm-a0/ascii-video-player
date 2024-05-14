# Overview
__ASCII Media Player written in C.__ \
\
Terminal layout is done using _ncurses_ library. \
Video decoding is done using _ffmpeg-dev_ libraries.

# How to use
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
# Updates and Features
<input type="checkbox" id="checkbox1" checked style="color: orange;">
<label for="checkbox1">Dynamic window resizing</label><br>

<input type="checkbox" id="checkbox2" checked style="color: orange;">
<label for="checkbox2">Help instructions</label><br>

<input type="checkbox" id="checkbox3" checked style="color: orange;">
<label for="checkbox3">Pause and Resume commands</label><br>

<input type="checkbox" id="checkbox4" style="color: green;">
<label for="checkbox4">Enhanced user interface</label><br>

<input type="checkbox" id="checkbox5" style="color: green;">
<label for="checkbox5">Video playback in color</label><br>

<input type="checkbox" id="checkbox6" style="color: green;">
<label for="checkbox6">Video quality filter</label><br>

<input type="checkbox" id="checkbox7" style="color: green;">
<label for="checkbox7">Video speed filter</label><br>

<input type="checkbox" id="checkbox8" style="color: green;">
<label for="checkbox8">Dynamic linking for Windows</label><br>

<input type="checkbox" id="checkbox9" style="color: green;">
<label for="checkbox9">Semaphore tweaks for MacOS</label><br>
