============COMPILING==============

This was compiled on a computer running ubuntu 64bit (14.04) using the GCC Compiler. 

It requires the SFML (an open source graphics library available online for free) library to be able to run.

There is a unix script called "make.sh" which uses the GCC compiler to compile all the different modules automatically. 

On windows, I assume if you ran the equivalent commands (once you have SFML installed) with the GCC compiler (installable with MinGW or Cygwin), it should work

============EXECUTING=============

Once compiled, it can be run by executing TD-PROJECT-X.out

To edit new maps, select [edit]/[Edit]:

  BLACK: creep tile.
  GREY: wall tile (where neither towers nor creeps go)
  X: tower tile
  GREEN: start tile.
  PURPLE: end tile. 

You can click DONE once you have completed the map, however it won't let you finish until you have one start tile and one end tile, and a path between them. 

After you click DONE, it will prompt you for the name of your map, and save the map in a file of that name. 

To start a new game, select [start]/[Start]
  
  Select your start wave and number of waves
  Then the game begins:
    Add towers to the tower tiles, enter y to place tower.
    Edit towers (upgrade or sell) by clicking on the tower and entering the appropriate command.
    Ask for a new wave by clicking the DONE button.
  The game ends when you defeat your selected number of waves, or the creeps destroy your health by reaching the end
