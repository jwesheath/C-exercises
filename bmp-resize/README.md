### Description
This program copies a bitmap image and scales the copy by a user specified factor.  The learning objective was to learn about file I/O, data structures, pointers, and a bit of hexadecimal.

### Requirements
Just a [GCC compiler](https://gcc.gnu.org/).

### Usage
Download this repo, navigate to this folder, and compile with the included makefile.

```
$ git clone https://github.com/jwesheath/C-exercises.git
$ cd bmp-resize
$ make
```

The program requires 3 command line arguments:

```
$ ./resize 10 input.bmp output.bmp
```

The first is an integer value by which you want to scale the image, the second is the original bitmap file, and the third is the bitmap file to be created.
