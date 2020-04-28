# Decipherer-Affine-Vigenere
20.08.2019
by @vdsau

Additional project for researching POSIX-standart.

Implemented in C++ for Linux OS, using POSIX-standart's multithreading (pthread), 
and represented by CLI.

Compiler - GCC 7.3.0 (Ubuntu 7.3.0-27ubuntu~18.04)

Platform - x86_64

Linux Ver. - Linux Lite 4.2

Working only with txt files.

Command syntax:

./decipherer input-file output-file cipher[vig/aff] parameters[vig_key/aff_a_b]

Examples:

./decipherer encrypted.txt decrypted.txt vig software

./decipherer encrypted.txt decrypted.txt aff key_a key_b
