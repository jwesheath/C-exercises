### Description
This is an implementation of the game [Breakout](https://en.wikipedia.org/wiki/Breakout_(video_game)) in C using the Stanford Portable Library (SPL) for GUI functionalty.  All license information for the Standord Portable Library is in `spl/license`.  The learning objectives were to learn and utilize an API, build a game with a GUI, and learn a bit about event handling.

### Requirements
[GCC compiler](https://gcc.gnu.org/) and the [libc6-dev-i386](http://packages.ubuntu.com/trusty/libc6-dev-i386) and [default-jdk](https://packages.debian.org/sid/default-jdk) packages.  The libc6-dev-i386 package is for compiling a 32 bit program on a 64 bit system and is only necessary if you're using a 64 bit system.  This was tested on a 64 bit machine but breakout.c is compiled in 32 bit mode to remain compatible with the SPL.  The default-jdk package is the Java Development Kit, needed to run the game window with the SPL.

### Usage
Download this repo, navigate to this folder, compile with the included makefile, and run the compiled program.

```
$ git clone https://github.com/jwesheath/C-exercises.git
$ cd breakout
$ make
$ ./breakout
```

A new window with the game will open.  Click the window to start and move the paddle with the mouse.  The game continues until all bricks are gone or the ball moves to the bottom of the screen 3 times.  
