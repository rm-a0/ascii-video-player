# Overview
ASCII Media Player written in C. \
Terminal layout is done using ncurses library. \
Video decoding is done using ffmpeg-dev libraries.

# Updates and Features
- [x]  Dynamic window resizing
- [x]  Help instructions
- [x]  Pause and Resume commands
- [ ]  Video playback in color
- [ ]  Video quality filter
- [ ]  Video speed filter

# Bugs and Issues
- [x]  Resizing causes crash when video is playing
- [x]  Windows are not being resized properly
- [x]  Major memory leaks after exiting program
- [ ]  Resizing causes crash when font or command window are too small

# How to use (will be updated)
Download this repository \
Compile using (install ncurses and ffmpeg before compilation)
<pre>
  make
</pre>
Run using either
<pre>
  make run
</pre> 
<pre>
  ./video_player
</pre>
