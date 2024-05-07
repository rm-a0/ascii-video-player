# Overview
ASCII Media Player written in C. \
Terminal layout is done using ncurses library. \
Video decoding is done using ffmpeg-dev libraries.

# Bugs and Issues
Resizing sometimes causes crash (FIXED) \
Resizing doesnt work properly when video is playing \
Window is sometimes not resized properly (FIXED) \
Memory leaks after exiting program (fixed in main)

# TODO
Implement Pause button (DONE) \
Implement dynamic resizing when video is playing (ALMOST DONE) \
Add additional commands (video quality, speed, help function...) \

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
