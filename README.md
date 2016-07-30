# gba-libs
Libraries to help developing GBA games.

### Setting up environment
You must download devkitARM from [here](https://sourceforge.net/projects/devkitpro/files/devkitARM/devkitARM_r45/).
Then you can extract wherever you want in your system. I'll assume you extracted to `/home/carlovan/`.

Clone this repository:
    git clone https://github.com/Carlovan/gba-libs.git

Then modify the file `Makefile`: in the first line substitute `../SDK` with the path where you extracted devkitARM.
In this case it should be :
    BINPATH := $(realpath /home/carlovan/devkitARM/bin)

Now you are ready to compile!

### Building
First of all run `make libs` to compile libraries.

The you can run `make` to compile the test program to `test.gba`.
You can delete all binary files with `make clean`.

DONE! You can now open `test.gba` with your favourite GBA Emulator (I recommend VisualBoyAdvance).
