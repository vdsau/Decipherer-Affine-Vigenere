# Decipherer-Affine-Vigenere
20.08.2019
by @vdsau

Implemented in C++ for Linux OS, using POSIX-standart's multithreading (pthread), 
and represented by CLI.

Working only with txt files.

Command syntax:
./decipherer input-file output-file cipher[vig/aff] parameters[vig_key/aff_a_b]

Examples:
./decipherer encrypted.txt decrypted.txt vig software
./decipherer encrypted.txt decrypted.txt aff key_a key_b
