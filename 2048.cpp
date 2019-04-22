/* The game 2048*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
/* definition of bool */
#define up 0x4800
#define down 0x5000
#define left 0x4d00
#define right 0x4b00
#define SIZE 10
#define bool int
#define true 1
#define false 0
typedef enum {
	UNKNOWN,
	UP,
	DOWN,
	LEFT,
	RIGHT,
} Directions;
/* map:restore the info*/
int map[4][4];
int score = 0;
/* the posibility of create two or four*/
int twoorfour(int x);
/*print the map */
void printmap();
/* get char from keyboard */
Directions getdir();
/* judge whether can move or not*/
bool canmove(Directions direction);
/* if canmove do actions */
void doit(Directions direction);
/* move in one direction */
void move(Directions direction);
/* make a new pile*/
void makenew();
int main()
{
	char *get = (char*)malloc(SIZE);
	memset(map, 0, sizeof(map));
	srand(time(NULL));
	makenew();
	makenew();
	printmap();
	while(1) {
		/* if cannot move game over */
		if(!canmove(UP) && !canmove(DOWN) && !canmove(LEFT) && !canmove(RIGHT))
			break;
			/* get the next direction */
		Directions nextdir = getdir();
		/*if(nextdir == UP)
			printf("up\n");
		if(nextdir == LEFT)
			printf("left\n");*/
		if(nextdir == UNKNOWN)
			continue;
		if(!canmove(nextdir))
			continue;
		system("cls");
		doit(nextdir);
		makenew();
		printmap();
	}
	/* game over */
	printf("You died\n");
	printf("Your final score is %d\n", score);
		//fgets(get, SIZE, stdin);
		//get[strlen(get) - 1] = '\0';
	while(1);
	return 0;
}
/* 90 percent 2 and 10 percent 4 */
int twoorfour(int x) {
	if(x == 10)
		return 4;
	else return 2;
}
bool canmove(Directions direction) {
	switch(direction) {
		case UP:
			/* if top lane is 0 can move up*/
			/*for(int i = 0; i < 4; i++) {
				if(map[0][i] == 0)
					return true;
			}/*
			/* if a pile which is not empty  equals to its upper pile  or its upper pile is empty then we can move */ 
			for(int i = 1; i < 4; i++) {
				for(int j = 0; j < 4; j++) {
					if((map[i][j] != 0) && (map[i - 1][j] == map[i][j] || map[i - 1][j] == 0))
						return true;
				}
			}
			break;
			/* similar to up */
		case DOWN:
			/*for(int i = 0; i < 4; i++) {
				if(map[3][i] == 0)
					return true;
			}*/
			for(int i = 0; i < 3; i++) {
				for(int j = 0; j < 4; j++) {
					if((map[i][j] != 0) && (map[i + 1][j] == map[i][j] || map[i + 1][j] == 0))
						return true;
				}
			}
			break;
			/* similar to up */
		case LEFT:
			/*for(int i = 0; i < 4; i++) {
				if(map[i][0] == 0)
					return true;
			}*/
			for(int i = 0; i < 4; i++) {
				for(int j = 1; j < 4; j++) {
 					if((map[i][j] != 0) && (map[i][j] == map[i][j - 1] || map[i][j - 1] == 0))
						return true;
				}
			}
			break;
			/* similar to up */
		case RIGHT:
			/*for(int i = 0; i < 4; i++) {
				if(map[i][3] == 0)
					return true;
			}*/
			for(int i = 0; i < 4; i++) {
				for(int j = 0; j < 3; j++) {
					if((map[i][j] != 0) && (map[i][j] == map[i][j + 1] || map[i][j + 1] == 0))
						return true;
				}
			}
			break;
			/* if press button error*/
		case UNKNOWN:
			printf("Press Button Error");
			break;
	}
	/* if all condition not then return false*/
	return false;
}
void doit(Directions direction) {
	/* move the piles */
	move(direction);
	/* then combine piles which has the same neighbour*/
	switch(direction) {
		case UP:
			/* search in sequence*/
			for(int i = 0; i < 3; i++) {
				for(int j = 0; j < 4; j++) {
					/* if a pile has the same neighbour then combine them upwards */
					if(map[i][j] != 0 && map[i][j] == map[i + 1][j]) {
						map[i][j] = map[i][j] * 2;
						score += map[i][j];
						map[i + 1][j] = 0;
					}
				}
			}
			move(direction);
			break;
			/* similar to up */
		case DOWN:
			for(int i = 3; i > 0; i--) {
				for(int j = 0; j < 4; j++) {
					if(map[i][j] != 0 && map[i][j] == map[i - 1][j]) {
						map[i][j] = map[i][j] * 2;
						score += map[i][j];
						map[i - 1][j] = 0;
					}
				}
			}
			move(direction);
			break;
			/* similar to up */
		case LEFT:
			for(int i = 0; i < 4; i++) {
				for(int j = 0; j < 3; j++) {
					if(map[i][j] != 0 && map[i][j] == map[i][j + 1]) {
						map[i][j] = map[i][j] * 2;
						score += map[i][j];
						map[i][j + 1] = 0;
					}
				}
			}
			move(direction);
			break;
			/* similar to up*/
		case RIGHT:
			for(int i = 0; i < 4; i++) {
				for(int j = 3; j > 0; j--) {
					if(map[i][j] != 0 && map[i][j] == map[i][j - 1]) {
						map[i][j] = map[i][j] * 2;
						score += map[i][j];
						map[i][j - 1] = 0;
					}
				}
			}
			move(direction);
			break;
			/* if press button error */
		case UNKNOWN:
			printf("Press Button Error\n");
			break;
	}
}
void move(Directions direction) {
	switch(direction) {
		case UP:
			/* search in sequence*/
			for(int i = 1; i < 4; i++) {
				for(int j = 0; j < 4; j++) {
					for(int k = i; k > 0; k--) {
					/* if its upper pile is 0 then move the pile upside*/
						if(map[k - 1][j] == 0) {
							map[k - 1][j] = map[k][j];
							map[k][j] = 0;
						}
					}
				}
			}
			break;
			/* similar to up */
		case DOWN:
			for(int i = 2; i >=0; i--) {
				for(int j = 0; j < 4; j++) {
					for(int k = i; k < 3; k++) {
						if(map[k + 1][j] == 0) {
							map[k + 1][j] = map[k][j];
							map[k][j] = 0;
						}
					}
				}
			}
			break;
			/* similar to up*/
		case LEFT:
			for(int i = 0; i < 4; i++) {
				for(int j = 1; j < 4; j++) {
					for(int k = j; k > 0; k--) {
						if(map[i][k - 1] == 0) {
							map[i][k - 1] = map[i][k];
							map[i][k] = 0;
						}
					}
				}
			}
			break;
			/* similar to up */
		case RIGHT:
			for(int i = 0; i < 4; i++) {
				for(int j = 2; j >= 0; j--) {
					for(int k = j; k < 3; k++) {
						if(map[i][k + 1] == 0) {
							map[i][k + 1] = map[i][k];
							map[i][k] = 0;
						}
					}
				}
			}
			break;
			/* if press button error*/
		case UNKNOWN:
			printf("Press Button Error\n");
			break;
	}
}
void printmap() {
	/* print the layout */
	printf("*.......*.......*.......*.......*\n");
	for(int i = 0; i < 4; i++) {
		printf("|");
		for(int j = 0; j < 4; j++) {
			/* print the number*/
			/* if value is 0 print ' '*/
			if(map[i][j] != 0) {
				printf("%d", map[i][j]);
			} else
				printf(" ");
			/* print the space */
			printf("\t|");
		}
		printf("\n");
		/* print the layout*/
		printf("*.......*.......*.......*.......*\n");
	}
	printf("Score: %d\n", score);
}
void makenew() {
	/* x is random*/
	int x = rand();
	/* determine the new pile is two or four*/
	int c = twoorfour((x % 10) + 1);
	/* calculate the sum of empty pile*/
	/* choose which empty pile to get the new number*/
	int cnt = 0;
	/* maps restore the order number of the empty pile*/
	int maps[4][4];
	memset(maps, 0, sizeof(maps));
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(map[i][j] == 0) {
				cnt ++;
				maps[i][j] = cnt;
			}
		}
	}
	/* create the new pile*/
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(maps[i][j] == ((x % cnt) + 1))
				map[i][j] = c;
		}
	}
}
Directions getdir() {
	/* get the next direction from the keyboard*/
	//int key = bioskey();
	/* change \n into \0 */
	//get[strlen(get) - 1] = '\0';
	/* get the direction*/
	int ch;
   	while((ch = getch()) != 0x1B) {/* Press ESC to quit... */
      	switch(ch) {
      		case 0xE0:
         		switch(ch=getch()) {
            		case 72: return UP; break;
            		case 80: return DOWN; break;
            		case 75: return LEFT; break;
            		case 77: return RIGHT; break;
            	default:
            		return UNKNOWN; 
               		break;
         		}
         		break;
      		default:
         		break;
      	}
   	}
	/* if not up down left right, return unknown */
	return UNKNOWN;
}

