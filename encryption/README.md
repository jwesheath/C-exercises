### Description
This folder contains implementations of the caesar and vigenere ciphers.  The learning objective was to learn a bit about encryption with C programming basics.  A helper library was provided.  This library is not mine and license information is included in the code.

### Requirements
Just a [GCC compiler](https://gcc.gnu.org/).

### Usage
Download this repo, navigate to this folder, and compile with the included makefile.

```
$ git clone https://github.com/jwesheath/C-exercises.git
$ cd encryption
$ make
```

The Caesar cipher program requires a single numerical string as a command line argument to be used as the key.  The Vigenere cipher program requires a single alphabetical string as a command line argument to be used as the key.  Both programs will prompt the user for a phrase to be encrypted and then return the encrypted string. 


```
$ ./caesar 15
Input phrase for caesar encryption: Secret message!
Htrgti bthhpvt!

$ ./vigenere mysecretkey
Input phrase for vigenere encryption: Another secret message!
Mlgxjvv logpqr eiujezo!
```
