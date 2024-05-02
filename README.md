# Overview
ASCII Media Player written in C. \
Terminal layout is done using ncurses library. \
Video decoding is done using ffmpeg-dev libraries.

# Bugs and Issues
Resizing sometimes causes crash (fixed) \
Resizing doesnt work properly when video is playing \
Window is sometimes not resized properly (when using dynamic resizing) \
Memory leaks after exiting program 

# TODO
Implement Pause button
Implement dynamic resizing when video is playing
Add additional commands (video quality, speed, help function...)

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
