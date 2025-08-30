# RASC - Really Awful Snake Clone

Terminal based snake clone.

## Description

I was bored of using online versions of snake and wanted to create my own utilising the terminal, C and the ncurses library. The code is very unorganized for now but in the future i will refactor it :)

## Getting Started

### Installing

* Download latest release or compile from source with:
``` gcc -Wall -O2 -o RASC main.c -lncurses ```
* Make a directory in your .local folder:
``` mkdir -p ~/.local/bin ```
* Move RASC to the created folder:
``` mv RASC ~/.local/bin/ ```

### Executing program
* If you followed the "Installing" steps simply type ```RASC``` anywhere in your terminal to run.
* If you didn't and wish to run from the directory that RASC is installed in:
``` ./RASC ```

## License

This project is licensed under the MIT License - see the LICENSE.md file for details

## Acknowledgments

Thanks to tldp for this amazing ncurses guide!
* [tldp](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/)
