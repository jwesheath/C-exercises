### Description
This folder contains an implementation of a rudimentary spell checker in C.  The learning objectives were to design and implement a data structure and optimize the code by preventing memory leaks in the context of a low level programming language.  I implement a hash table where collisions are handled by separate chaining with linked lists.

### Requirements
Just a [GCC compiler](https://gcc.gnu.org/).

### Usage
Download this repo, navigate to this folder, and compile with the included makefile.

```
$ git clone https://github.com/jwesheath/C-exercises.git
$ cd spellchecker
$ make
```

The `speller` program requires the user to designate a text file to spellcheck as a command line argument.  An example file, `text-to-check.txt` is included in this repository, but any text file can be checked.

```
$ ./speller text-to-check.txt


MISSPELLED WORDS

tetx
byy
spel
worrds
speled
spelld
inkorrectly

WORDS MISSPELLED:     7
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        25
TIME IN load:         0.02
TIME IN check:        0.00
TIME IN size:         0.00
TIME IN unload:       0.01
TIME IN TOTAL:        0.04

```

The output includes the misspelled words, the number of misspelled words in the spellchecked file, the number of words in the dictionary, and the total number of words in the spellchecked file.

Since one of the learning objectives of this exercise was to understand how memory works in a low level programming language, there is also quite a bit of information in the output about how quickly various pieces of the program run, including how quickly the words in `dictionary.txt` are loaded into memory/the hash table, how quickly the words in the text are located in the hash table and checked for spelling, and how quickly the dictionary is unloaded from memory.  Valgrind was utilized to ensure there are no memory leaks.  A dictionary, `dictionary.txt`, is also included in this repository and is hardcoded into the program in order to avoid needing to specify it as an additional command line argument.  Users can substitute this file with their own dictionary.
