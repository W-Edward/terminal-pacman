# Pac-Man: Alpha Edition
ENGG1340 Final Group Project - Group 68

![](https://img.shields.io/badge/Exam%20Preparation-Low-red) ![](https://img.shields.io/badge/Stress%20Levels-High-critical) ![](https://img.shields.io/badge/C%2B%2B%20-100%25-brightgreen)

![alt text](https://m.media-amazon.com/images/S/aplus-media-library-service-media/aab7335f-9acf-46b6-bd3b-ee09c407e7ca.__CR0,0,970,300_PT0_SX970_V1___.jpg)

***Table of Contents***

- [Pac-Man: Alpha Edition](#pac-man-alpha-edition)
  - [Group Members](#group-members)
  - [About the Game](#about-the-game)
    - [Game Description](#game-description)
    - [Game Rules](#game-rules)
  - [Features Implemented](#features-implemented)
    - [Generation of random game sets or events](#generation-of-random-game-sets-or-events)
    - [Data structures for storing game status](#data-structures-for-storing-game-status)
    - [Dynamic memory management](#dynamic-memory-management)
    - [File input/output](#file-inputoutput)
    - [Program codes in multiple files](#program-codes-in-multiple-files)
  - [Non-Standard Libraries Used](#non-standard-libraries-used)
    - [Ncurses](#ncurses)
  - [Compilation and Execution Instructions](#compilation-and-execution-instructions)

<br>

## Group Members
|  Name  |  UID  |  GitHub Username  |
| :------------:  |  :------------: |  :------------: |
|  **Fong Ting Hin**  |  3036......  | FongTingHin
|  **Lok Wang Yi**  |  3036067420  | lokwy-hku
|  **Lui Yik Hang**  |  3036067652  | felixlyh
|  **Widjaja Edward Aryaguna**  |  3036029703  | W-Edward
|  **Wong Hoi Lei**  |  3036063917  | ginngerine

<br>

##  About the Game
Pac-man was a trending video game in the 1980s, and we have decided to bring back the retro game in a text-based form for users to relive their great memories. 

###  Game Description
Pac-Man is a video game back in the 1980s which was once extremely popular across the globe. The game design is intended to be a harmonious-themed arcade game which is made to be suitable for everyone, including female gamers. Pac-Man managed to stand out among other video games in its era since most computer games were oriented for male users, since the majority of information technology staff were men.

###  Game Rules

1. In the map, pacman spawns along with 4 other ghosts which attempts to eat him. The player should avoid letting pacman approach the ghosts by controlling its movement pattern.

2. To increase the game score, pacman should absorb the circular points along different paths in the map.

3. Pacman may collect a powerup pill which allows it to eat the ghosts and return the ghosts to their spawning points. Ghosts are allowed to be smashed by pacman only when they have frightened mode trigerred.

4. Once pacman received 3 damages from the ghosts, the game will be concluded.

<br>

##  Features Implemented

-Variable ghost behaviour
  The four ghosts in our game are not necessarily chasing Pac-man all the time. Occasionally, ghosts will be in a "scatter" mode where they target their corner tiles instead of pac-man.  On the other hand, when ghosts engaged their "chase" mode, the program will check pac-man's positions and assign ghosts to chase after it.

### Generation of random game sets or events
 Pacman's fruits will appear in random positions of the map in random times. This helps increases the game score.

### Data structures for storing game status
 Objects' positions and direction (Pacman, ghosts) are stored in sets of integers. (two variables namely x,y representing coordinates)
 Game score will be stored as an integer.

### Dynamic memory management


### File input/output


### Program codes in multiple files

Our project consists of three c++ source code files (StartnEndSequence.cpp, main.cpp and ghost.cpp.

StartnEndSequence.cpp stores the startup game menu and ending screen, which will be used at the beginning of execution and when the user exits the game.

main.cpp stores the source code for the pacman game, which includes details for controlling the colors & manners of screen display, call relevant ghost behaviour functions from the ghost.cpp file and the 2D game map.

ghost.cpp stores the source code for all 4 ghosts' behaviours. Since the ghost behaviour are relatively complicated which requires a higher source code line count, we have decided to separate it to another source code file for easier management.

entities.h is a header file which stores a c++ class named ghost, containing its various statuses like positions, true/false status for situations such as whether ghost is eaten, frightened, chasing pacman or escaping from pacman.

StartnEndSequence.h is a header file stating the starting screen and ending screen functions involved in StartnEndSequence.cpp file which is used when compiling the game program by Makefile.

<br>

## Non-Standard Libraries Used
Not applicable

### Ncurses


<br>

## Compilation and Execution Instructions
In order to compile the game, you may choose to execute `make pacman`.
If you wish to not have .o files remaining in the folder after compiling, you may remove them by `make clean`

After that, you may start the game program by executing `./pacman`

You will be directed to the start menu when the program is executed. You may navigate through the menu options with up/down arrow keys, and press ENTER to run the command. To play the game, you may navigate to "Play the Pac-Man Game!" and press enter. The selected option will be highlighted in yellow in the main menu.

You may navigate with pressing "W,A,S,D" keys during gameplay.
Pac-Man moves automatically based on your previously pressed key.
Press "W" once for turning upwards, or "A" for turning left, or "S" for turning downward, or "D" for turning right.

To exit the game while playing, simply type "quit" on the keyboard. The ending screen will then displayed and program will exit afterwards.
