
## About

> Final Project of Fundemental Programming

> Under The Supervision of [Prof.Bahador Bakhshi](https://scholar.google.com/citations?user=cdjKqjUAAAAJ&hl=en)

> Fall 2019


## Explaination

This game features cells designated for each player, with a maximum of two players, capable of moving, splitting, and increasing the energy of each cell. Prior to running the game, a binary map file must be generated. The map file comprises an integer followed by nxn characters arranged in row-major form. The integer represents the length of the map (equivalent to its width, as the map is square), while each character denotes the type of block within the map. A value of 1 signifies a source, 2 indicates Mitosis, 3 denotes forbidden blocks, and 4 represents normal blocks, with Mitosis blocks denoted by 'M' in the map and sources by 'E'. Cells can only split in Mitosis blocks and increase energy solely in source blocks, while forbidden blocks, depicted as '-', are inaccessible to cells. Normal blocks, illustrated as '0', can be traversed. Player 1's cells are represented by 'X', and Player 2's by 'Y'. Each cell can boost its energy to a maximum of 100, with a prerequisite of reaching level 80 to undergo splitting. Additionally, the game features an undo button, enabling players to revert their moves. Saved games can also be loaded at any time.
