#include "pch.h"
#include <iostream>
#include <conio.h>
#include "../ClassInCpp/consts.h"
#include "../ClassInCpp/strutils.h"
#include "../ClassInCpp/consoleroutine.h"
#include "../ClassInCpp/tgeom.h"
#include "../ClassInCpp/tpoint.h"
#include "../ClassInCpp/trect.h"
#include "../ClassInCpp/list2link.h"

void printStatus2(short x, short y, short Left, short Top) {
	char *s = (char *)malloc(255 * sizeof(char));
	nullStr(s, 255);
	strcpy_s(s, 255, "F3=Load");
	consoleSetColors(clBlack, clLightRed);
	consoleGotoXY(Left, Top);
	printf("x:3%d y:%3d      %s", x, y, s);
	free(s);
}


int main(){
	TRect *console = new TRect();
	console->x = 1;
	console->y = 1;
	console->width = consoleSizeX() - 1;
	console->height = consoleSizeY() - 1;

	TPoint *tank = new TPoint();
	tank->x = console->x + console->width / 2;
	tank->y = console->y + console->height / 2;
	tank->typ     = ptTank;
	tank->bgcolor = clLightGreen;
	tank->color   = clBlack;

	list2 *map = list2_loadfromfile(NULL, "d:\\Learn\\map.txt");
	list2_print(map);

	int flagExit = 0;
	int keyPressed = 0;
	do {
		printStatus2(tank->x, tank->y, 0, 0);
		list2_print(map);
		tank->Print();
		consoleGotoXY(tank->x, tank->y);
		keyPressed = _getch();
		tank->Erase();
		switch (keyPressed) {
		    case KEY_ESCAPE: {
				flagExit = 1;
				break;
			}
		case KEY_LEFT: {
			if( (tank->x > console->x) && (0 == list2_contains(map, (tank->x-1), tank->y)) ) {
				tank->x--;
			}
			break;
		}
		case KEY_RIGHT: {
			if( (tank->x < console->width) && (0 == list2_contains(map, (tank->x + 1), tank->y)) ){
				tank->x++;
			}
			break;
		}
		case KEY_UP: {
			if( (tank->y > console->y) && (0 == list2_contains(map, tank->x, (tank->y-1))) ){
				tank->y--;
			}
			break;
		}
		case KEY_DOWN: {
			if( (tank->y < console->height) && (0 == list2_contains(map, tank->x, (tank->y+1))) ){
				tank->y++;
			}
			break;
		}
		}
	} while (0 == flagExit);

	delete tank;
	//delete console;
	consoleGotoXY(0, consoleBuffSizeY() - 1);
	consoleSetColors(clWhite, clBlack);
	return 0;// gg Dortmund
}