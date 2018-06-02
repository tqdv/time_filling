# time\_filling

## Requirements
For the library:
* C++17
* cmake 1.11 or something

For `display.py`:
* python with matplotlib and the GTK3Cairo backend (or whichever you get to work)

## Building

Set `g++-8` or any C++17 compiler as your `CXX` environmnet variable,
then run `cmake` in your `$BUILDROOT`

To view the path, you can currently use
    $BUILDROOT/Cli/tfill | python $REPO/display.py
