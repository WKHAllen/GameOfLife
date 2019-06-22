# Conway's Game of Life

This is John Conway's Game of Life, a cellular automaton that simulates a basic form of evolution.

## Info

At the moment, it only function in the console window, but in time I might make it into a windowed application using SFML or a similar library to make it look more normal.

The application has only been tested on Windows, but is designed to work on Unix as well.

## Usage

To run the application, simply invoke it in a terminal:

```console
$ ./game_of_life
```

The command line switch `-w` can be used to change the width of the game screen, and `-h` can be used to change the height.

```console
$ ./game_of_life -w 20 -h 20
```

`-t` changes the board to toroid.

```console
$ ./game_of_life -t
```

`-fg` and `-bg` change the background color and foreground color respectively.

```console
$ ./game_of_life -fg 1 -bg 0
```
