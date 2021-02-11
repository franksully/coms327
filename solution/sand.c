#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "sand.h"

int main(int argc, char *argv[]) {
	int table[23][23];
	int fps = 24;
	int tuples;
  
	init_table(table);
	incrementMid(table);
	
	// check for additional arguments
	if (argc > 1) {
		int i;
	  
		// check if framerate is given
		if (!(strcmp(argv[1], "--fps"))) {
			fps = atoi(argv[2]);
			// get the number of three-tuples (minus the first 3 arguments)
			tuples = (argc - 3) / 3;
			
			// begin parsing triplets at index 3
			i = 3;
		}
		else {
			// get the number of three-tuples (minus the first argument)
			tuples = (argc - 1) / 3;
			
			// begin parsing triplets at index 1
			i = 1;
		}
		
		for (int j = 0; j < tuples; j++) {
			int row = atoi(argv[i]);
			int col = atoi(argv[i+1]);
			int height = atoi(argv[i+2]);
			// set the sink position (cannot be a center-cell sink)
			if (height == -1) {
				if ((row != 11) || (col != 11)) {
					setHeight(table, row, col, height);
				}
			}
			// parse each triplet
			else {
				setHeight(table, row, col, height);
			}
			
			
			i += 3;
		}
	}
	
	while(1) {
  		printtable(table);
		incrementMid(table);
    		
    	      
    		usleep(1000000/fps);
  	}

	return 0;
}

void init_table(int table[23][23]) {
	int i, j;
	for(j=0;j<23;j++) {
		for(i=0;i<23;i++) {
			table[j][i] = 0;
		}
	}
}

void setHeight(int table [23][23], int y, int x, int h) {
	table[y][x] = h;
}

void incrementMid(int table[23][23]) {
  	// increment mid
  	table[11][11]++;
  	// call recursive function if mid exceeds 8
  	if (table[11][11] > 8) {
    		recIncrement(table, 11, 11);
  	}
}

void recIncrement(int table[23][23],int y, int x) {
	// base is set to 0, the for loop will increment it once i + j == 0
	table[y][x] = 0;
    	for(int i=-1; i<=1; i++) {
    		for(int j = -1; j <= 1; j++) {
      			// this if statement ensures the table does not exceed its bounds
        		if (!(y + i > 22 || x + j > 22) && !(y + i < 0 || x + j < 0)) {
          			// increment neighbor if index is not a sink
          			if (table[y + i][x + j] != -1) {
          				table[y + i][x + j]++;
          			}
          			// check if neighbor exceeds 8
          			if (table[y + i][x + j] > 8) {
          				// recursively calls itself
          				recIncrement(table, y + i, x + j);
          			}
        		} 
      		} 
	}
}

void printtable(int table[23][23]) {
	for(int j =0;j<23;j++) {
		for(int i =0;i<23;i++) {
			// check if table index is a sink
			if (table[j][i] == -1) {
				printf("%2c ", '#');
			}
			// if not, print the height
			else {
				printf("%2d ", table[j][i]);
			}
		}
		printf("\n");
	}
	printf("\n");
}
