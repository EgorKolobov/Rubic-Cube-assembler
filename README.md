# Rubic-Cube-assembler
1)	lab8.cpp - the main cpp file. Starts the menu.
2)	rubic.h - the header file of the "cube" and "side" classes. All the terminal colours are here.
3)	rubic.cpp - realization of "cube" and "side" methods.
4)	menu.h - the header file of of the "menu" class. 
5)	menu.cpp - realization of "menu" methods.
6)	hint.txt - here's all the steps for assebling Rubic's cube.
7)	saved_config.txt - saved configuration of Rubic's cube. You can save and load configuration from the menu.

The program works fine on macOS. if you're using Windows, some issues with colored output may occur. To fix that, go to rubic.h and delete all colours (D_GREEN,D_RED, CYAN, RESET,  etc). Then go to rubic.cpp and delete all lines from 14 to 39. And finaly, you should remove all colour usages from menu.cpp This problem is going to be fixed in later versions.
