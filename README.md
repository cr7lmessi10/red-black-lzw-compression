# lzw
This is a project to show how Red-Black Trees can be used to memory-optimize
applications that use hashmaps.

The project contains one core file named lzw.cpp

lzw.cpp implements the Lempel-Ziv-Welch compression algorithm using stl-map which are by default Red-Black Trees. It uses hashmaps
to create its dictionary. It has two functions compress and decompress which are self explanatory.

main.cpp is the starting point of the application

# Installation
The repository comes with a makefile. So you dont have to do anything.
Once executed, makefile creates a lzw executable.

lzw -c [filename] is for compression
lzw -d [filename] is for decompression

compression adds a .lzw extension to the output file.
