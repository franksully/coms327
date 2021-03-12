#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "dungeon.h"
#include "pc.h"
#include "npc.h"
#include "move.h"
#include "utils.h"

const char *victory =
  "\n                                       o\n"
  "                                      $\"\"$o\n"
  "                                     $\"  $$\n"
  "                                      $$$$\n"
  "                                      o \"$o\n"
  "                                     o\"  \"$\n"
  "                oo\"$$$\"  oo$\"$ooo   o$    \"$    ooo\"$oo  $$$\"o\n"
  "   o o o o    oo\"  o\"      \"o    $$o$\"     o o$\"\"  o$      \"$  "
  "\"oo   o o o o\n"
  "   \"$o   \"\"$$$\"   $$         $      \"   o   \"\"    o\"         $"
  "   \"o$$\"    o$$\n"
  "     \"\"o       o  $          $\"       $$$$$       o          $  ooo"
  "     o\"\"\n"
  "        \"o   $$$$o $o       o$        $$$$$\"       $o        \" $$$$"
  "   o\"\n"
  "         \"\"o $$$$o  oo o  o$\"         $$$$$\"        \"o o o o\"  "
  "\"$$$  $\n"
  "           \"\" \"$\"     \"\"\"\"\"            \"\"$\"            \""
  "\"\"      \"\"\" \"\n"
  "            \"oooooooooooooooooooooooooooooooooooooooooooooooooooooo$\n"
  "             \"$$$$\"$$$$\" $$$$$$$\"$$$$$$ \" \"$$$$$\"$$$$$$\"  $$$\""
  "\"$$$$\n"
  "              $$$oo$$$$   $$$$$$o$$$$$$o\" $$$$$$$$$$$$$$ o$$$$o$$$\"\n"
  "              $\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\""
  "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"$\n"
  "              $\"                                                 \"$\n"
  "              $\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\""
  "$\"$\"$\"$\"$\"$\"$\"$\n"
  "                                   You win!\n\n";

const char *tombstone =
  "\n\n\n\n                /\"\"\"\"\"/\"\"\"\"\"\"\".\n"
  "               /     /         \\             __\n"
  "              /     /           \\            ||\n"
  "             /____ /   Rest in   \\           ||\n"
  "            |     |    Pieces     |          ||\n"
  "            |     |               |          ||\n"
  "            |     |   A. Luser    |          ||\n"
  "            |     |               |          ||\n"
  "            |     |     * *   * * |         _||_\n"
  "            |     |     *\\/* *\\/* |        | TT |\n"
  "            |     |     *_\\_  /   ...\"\"\"\"\"\"| |"
  "| |.\"\"....\"\"\"\"\"\"\"\".\"\"\n"
  "            |     |         \\/..\"\"\"\"\"...\"\"\""
  "\\ || /.\"\"\".......\"\"\"\"...\n"
  "            |     |....\"\"\"\"\"\"\"........\"\"\"\"\""
  "\"^^^^\".......\"\"\"\"\"\"\"\"..\"\n"
  "            |......\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"......"
  "..\"\"\"\"\"....\"\"\"\"\"..\"\"...\"\"\".\n\n"
  "            You're dead.  Better luck in the next life.\n\n\n";

void usage(char *name)
{
  fprintf(stderr,
          "Usage: %s [-r|--rand <seed>] [-l|--load [<file>]]\n"
          "          [-s|--save [<file>]] [-i|--image <pgm file>]\n"
          "          [-n|--nummon <count>] [-d|--delay <microseconds>]\n",
          name);

  exit(-1);
}

void io_init_terminal(void) {
	initscr();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
}

int list_loop(dungeon_t *d) {
	int32_t key = 'm';
	char *blank_line = "                                        ";
	
	//uint16_t mon_count = d->num_monsters;
	
	/*
	character_t *character_list[mon_count];
	int32_t i = 0;
	for (int y = 0; y < DUNGEON_Y; y++) {
		for (int x = 0; x < DUNGEON_X; x++) {
			if (charxy(x,y)) {
				if(charxy(x,y)->position[dim_x] != d->pc.position[dim_x] && charxy(x,y)->position[dim_y] != d->pc.position[dim_y]) {
					&character_list[i] = &d->character[y][x];
					i++;
				}
			}
		}
	}
	*/
	mvprintw(2, 20, "              MONSTER LIST              ");
	mvprintw(3, 20, "----------------------------------------");
	
	for (int j = 4; j < 19; j++) {
		mvprintw(j, 20, blank_line);
	}
	char monList[d->num_monsters][38]; 
	char string[38];
	uint16_t i = 0;
	uint16_t t = 0;
	uint16_t maxNum = 15;
	
	if(d->num_monsters < 15){
		maxNum = d->num_monsters;
	}
	int pc_y = d->pc.position[dim_y];
	int pc_x = d->pc.position[dim_x];
	
	for (int y = 0; y < DUNGEON_Y; y++) {
		for (int x = 0; x < DUNGEON_X; x++) {
			if (charxy(x,y) && !(pc_y == y && pc_x == x)) {
				char lateral[12];
				if (pc_y - y > 0) {
					sprintf(lateral, "north by %d", pc_y - y);
				}
				else if (pc_y - y < 0) {
					sprintf(lateral, "south by %d", -1*(pc_y - y));
				}
				else {
					sprintf(lateral, "not");
				}
				
				char horizontal[12];
				if (pc_x - x > 0) {
					sprintf(horizontal, "west by %d", pc_x - x);
				}
				else if (pc_x - x < 0) {
					sprintf(horizontal, "east by %d", -1*(pc_x - x));
				}
				else {
					sprintf(horizontal, "not");
				}
				
				if(!strcmp(lateral, "not")) {
					sprintf(string, "Monster %c is %s", charxy(x,y)->symbol, horizontal);
				}
				else if (!strcmp(horizontal, "not")) {
					sprintf(string, "Monster %c is %s", charxy(x,y)->symbol, lateral);
				}
				else {
					sprintf(string, "Monster %c is %s, %s", charxy(x,y)->symbol, lateral, horizontal);
				}
				
				strcpy(monList[i], string);
				i++;
			}
		}
	}
	
	for(i = 0; i < maxNum; i++){
		mvprintw(i+4, 22, "%s", monList[i + t]);
	}
	
	/*
	move(0,0);
	clrtoeol();
	printw("num monsters: %d", d->num_monsters);
	*/
	
	while (key != 0033) {
	
		refresh();
		
		key = getch();
		if(key == 0402){ // donw arrow
			for (int j = 4; j < 19; j++) {
				mvprintw(j, 20, blank_line);
			}
			
			i=0;

			if(t < d->num_monsters - maxNum){
				t++;
			}
			for(i = 0; i < maxNum; i++){
				mvprintw(i+4, 22, "%s", monList[i + t]);
			}
			/*for (int y = 0; y < DUNGEON_Y; y++) {
				for (int x = 0; x < DUNGEON_X; x++) {
					if (charxy(x,y)) {


						//(monList + i) = string;
						//printf("%s\n", monList[i]);
					
						mvprintw(i+4, 35, "%s", monList + i + t);
						//mvprintw(i+4, 35, "%s", monList[i]);
						i++;
					}
					if (i > 15) {
						break;
					}
				}
				if (i > 15) {
					break;
				}
			}*/
		}
		if(key == 0403){ // up arrow
			for (int j = 4; j < 19; j++) {
				mvprintw(j, 20, blank_line);
			}
			
			i=0;
			if(t > 0){
				t--;
			}
			for(i = 0; i < maxNum; i++){
				mvprintw(i+4, 22, "%s", monList[i + t]);
			}
			/*for (int y = 0; y < DUNGEON_Y; y++) {
				for (int x = 0; x < DUNGEON_X; x++) {
					if (charxy(x,y)) {


						//(monList + i) = string;
						//printf("%s\n", monList[i]);
					
						mvprintw(i+4, 35, "%s", monList + i + t);
						//mvprintw(i+4, 35, "%s", monList[i]);
						i++;
					}
					if (i > 15) {
						break;
					}
				}
				if (i > 15) {
					break;
				}
			}*/
		}
		if(key == 'Q'){
			return 0;
		}
	}
	return 1;
}

void game_loop(dungeon_t *d) {
	uint32_t no_op = 0;
  int32_t key;
	
	render_dungeon(d);
	while (pc_is_alive(d) && dungeon_has_npcs(d)) {
		key = getch();
    move(0,0);
		clrtoeol();
		switch (key) {
    // down-left
		case '1':
		case 'b':
			if (d->map[d->pc.position[dim_y] + 1][d->pc.position[dim_x] - 1] != ter_wall_immutable &&
					d->map[d->pc.position[dim_y] + 1][d->pc.position[dim_x] - 1] != ter_wall) {
				do_moves(d, d->pc.position[dim_x] - 1, d->pc.position[dim_y] + 1);
				no_op = 0;
			}
			else {
				no_op = 1;
				mvprintw(0, 0, "Invalid move to %d, %d! PC cannot tunnel", d->pc.position[dim_x] - 1, d->pc.position[dim_y] + 1);
			}
			break;
		// down
		case '2':
		case 'j':
			if (d->map[d->pc.position[dim_y] + 1][d->pc.position[dim_x]] != ter_wall_immutable &&
					d->map[d->pc.position[dim_y] + 1][d->pc.position[dim_x]] != ter_wall) {
				do_moves(d, d->pc.position[dim_x], d->pc.position[dim_y] + 1);
				no_op = 0;
			}
			else {
				no_op = 1;
				mvprintw(0, 0, "Invalid move to %d, %d! PC cannot tunnel", d->pc.position[dim_x], d->pc.position[dim_y] + 1);
			}
			break;
		// down-right
		case '3':
		case 'n':
			if (d->map[d->pc.position[dim_y] + 1][d->pc.position[dim_x] + 1] != ter_wall_immutable &&
					d->map[d->pc.position[dim_y] + 1][d->pc.position[dim_x] + 1] != ter_wall) {
				do_moves(d, d->pc.position[dim_x] + 1, d->pc.position[dim_y] + 1);
				no_op = 0;
			}
			else {
				no_op = 1;
				mvprintw(0, 0, "Invalid move to %d, %d! PC cannot tunnel", d->pc.position[dim_x] + 1, d->pc.position[dim_y] + 1);
			}
			break;
		// left
		case '4':
		case 'h':
			if (d->map[d->pc.position[dim_y]][d->pc.position[dim_x] - 1] != ter_wall_immutable &&
					d->map[d->pc.position[dim_y]][d->pc.position[dim_x] - 1] != ter_wall) {
				do_moves(d, d->pc.position[dim_x] - 1, d->pc.position[dim_y]);
				no_op = 0;
			}
			else {
				no_op = 1;
				mvprintw(0, 0, "Invalid move to %d, %d! PC cannot tunnel", d->pc.position[dim_x] - 1, d->pc.position[dim_y]);
			}
			break;
		// rest
		case '5':
		case 0040:
		case '.':
			if (d->map[d->pc.position[dim_y]][d->pc.position[dim_x]] != ter_wall_immutable) {
				do_moves(d, d->pc.position[dim_x], d->pc.position[dim_y]);
				no_op = 0;
			}
			else {
				no_op = 1;
			}
			break;
		// right
		case '6':
		case 'l':
			if (d->map[d->pc.position[dim_y]][d->pc.position[dim_x] + 1] != ter_wall_immutable &&
					d->map[d->pc.position[dim_y]][d->pc.position[dim_x] + 1] != ter_wall) {
				do_moves(d, d->pc.position[dim_x] + 1, d->pc.position[dim_y]);
				no_op = 0;
			}
			else {
				no_op = 1;
				mvprintw(0, 0, "Invalid move to %d, %d! PC cannot tunnel", d->pc.position[dim_x] + 1, d->pc.position[dim_y]);
			}
			break;
		// up-left
		case '7':
		case 'y':
			if (d->map[d->pc.position[dim_y] - 1][d->pc.position[dim_x] - 1] != ter_wall_immutable &&
					d->map[d->pc.position[dim_y] - 1][d->pc.position[dim_x] - 1] != ter_wall) {
				do_moves(d, d->pc.position[dim_x] - 1, d->pc.position[dim_y] - 1);
				no_op = 0;
			}
			else {
				no_op = 1;
				mvprintw(0, 0, "Invalid move to %d, %d! PC cannot tunnel", d->pc.position[dim_x] - 1, d->pc.position[dim_y] - 1);
			}
			break;
		// up
		case '8':
		case 'k':
			if (d->map[d->pc.position[dim_y] - 1][d->pc.position[dim_x]] != ter_wall_immutable &&
					d->map[d->pc.position[dim_y] - 1][d->pc.position[dim_x]] != ter_wall) {
				do_moves(d, d->pc.position[dim_x], d->pc.position[dim_y] - 1);
				no_op = 0;
			}
			else {
				no_op = 1;
				mvprintw(0, 0, "Invalid move to %d, %d! PC cannot tunnel", d->pc.position[dim_x], d->pc.position[dim_y] - 1);
			}
			break;
		// up-right
		case '9':
		case 'u':
			if (d->map[d->pc.position[dim_y] - 1][d->pc.position[dim_x] + 1] != ter_wall_immutable &&
					d->map[d->pc.position[dim_y] - 1][d->pc.position[dim_x] + 1] != ter_wall) {
				do_moves(d, d->pc.position[dim_x] + 1, d->pc.position[dim_y] - 1);
				no_op = 0;
			}
			else {
				no_op = 1;
				mvprintw(0, 0, "Invalid move to %d, %d! PC cannot tunnel", d->pc.position[dim_x] + 1, d->pc.position[dim_y] - 1);
			}
			break;
		case '>':
			if (d->map[d->pc.position[dim_y]][d->pc.position[dim_x]] == ter_stairs_down) {
				no_op = 0;
				pc_delete(d->pc.pc);
				delete_dungeon(d);
				init_dungeon(d);
				gen_dungeon(d);
				config_pc(d);
				gen_monsters(d);
				mvprintw(0, 0, "Moved downward to a new level");
			}
			else {
				no_op = 1;
				mvprintw(0, 0, "Cannot perform action, not standing on a downward staircase!");
			}
			break;
		case '<':
			if (d->map[d->pc.position[dim_y]][d->pc.position[dim_x]] == ter_stairs_up) {
				no_op = 0;
				pc_delete(d->pc.pc);
				delete_dungeon(d);
				init_dungeon(d);
				gen_dungeon(d);
				config_pc(d);
				gen_monsters(d);
				mvprintw(0, 0, "Moved upward to a new level");
			}
			else {
				no_op = 1;
				mvprintw(0, 0, "Cannot perform action, not standing on an upward staircase!");
			}
			break;
		// quit
		case 'm':
			no_op = 0;
			if(list_loop(d)) {
				break;
			}
			key = 'Q';
		case 'Q':
			d->pc.alive = 0;
			no_op = 1;
			break;
		default:
			no_op = 1;
			mvprintw(0, 0, "Invalid input, octal ID: %o" , key);
			break;
		}
		
		refresh();
		if (!no_op) {
			render_dungeon(d);
		}
	}
	
	erase();
	
	if (pc_is_alive(d)) {
		mvprintw(0, 0, victory);
	}
	else {
		mvprintw(0, 0, tombstone);
	}
	mvprintw(21, 8, "You defended your life in the face of %u deadly beasts.", d->pc.kills[kill_direct]);
  mvprintw(22, 4, "You avenged the untimely murders of %u peaceful dungeon residents.",
										d->pc.kills[kill_avenged]);
	mvprintw(23, 30, "(Press 'Q' to quit)");
	refresh();
	
	while(key != 'Q') {
		key = getch();
	}
}

int main(int argc, char *argv[])
{
  dungeon_t d;
  time_t seed;
  struct timeval tv;
  uint32_t i;
  uint32_t do_load, do_save, do_seed, do_image, do_save_seed, do_save_image;
  uint32_t long_arg;
  char *save_file;
  char *load_file;
  char *pgm_file;
  uint32_t delay = 33000;
  
  /* Quiet a false positive from valgrind. */
  memset(&d, 0, sizeof (d));
  
  /* Default behavior: Seed with the time, generate a new dungeon, *
   * and don't write to disk.                                      */
  do_load = do_save = do_image = do_save_seed = do_save_image = 0;
  do_seed = 1;
  save_file = load_file = NULL;
  d.max_monsters = MAX_MONSTERS;

  /* The project spec requires '--load' and '--save'.  It's common  *
   * to have short and long forms of most switches (assuming you    *
   * don't run out of letters).  For now, we've got plenty.  Long   *
   * forms use whole words and take two dashes.  Short forms use an *
    * abbreviation after a single dash.  We'll add '--rand' (to     *
   * specify a random seed), which will take an argument of it's    *
   * own, and we'll add short forms for all three commands, '-l',   *
   * '-s', and '-r', respectively.  We're also going to allow an    *
   * optional argument to load to allow us to load non-default save *
   * files.  No means to save to non-default locations, however.    *
   * And the final switch, '--image', allows me to create a dungeon *
   * from a PGM image, so that I was able to create those more      *
   * interesting test dungeons for you.                             */
 
 if (argc > 1) {
    for (i = 1, long_arg = 0; i < argc; i++, long_arg = 0) {
      if (argv[i][0] == '-') { /* All switches start with a dash */
        if (argv[i][1] == '-') {
          argv[i]++;    /* Make the argument have a single dash so we can */
          long_arg = 1; /* handle long and short args at the same place.  */
        }
        switch (argv[i][1]) {
        case 'd':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-delay")) ||
              argc < ++i + 1 /* No more arguments */ ||
              !sscanf(argv[i], "%u", &delay)) {
            usage(argv[0]);
          }
          break;
        case 'n':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-nummon")) ||
              argc < ++i + 1 /* No more arguments */ ||
              !sscanf(argv[i], "%hu", &d.max_monsters)) {
            usage(argv[0]);
          }
          break;
        case 'r':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-rand")) ||
              argc < ++i + 1 /* No more arguments */ ||
              !sscanf(argv[i], "%lu", &seed) /* Argument is not an integer */) {
            usage(argv[0]);
          }
          do_seed = 0;
          break;
        case 'l':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-load"))) {
            usage(argv[0]);
          }
          do_load = 1;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            /* There is another argument, and it's not a switch, so *
             * we'll treat it as a save file and try to load it.    */
            load_file = argv[++i];
          }
          break;
        case 's':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-save"))) {
            usage(argv[0]);
          }
          do_save = 1;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            /* There is another argument, and it's not a switch, so *
             * we'll save to it.  If it is "seed", we'll save to    *
	     * <the current seed>.rlg327.  If it is "image", we'll  *
	     * save to <the current image>.rlg327.                  */
	    if (!strcmp(argv[++i], "seed")) {
	      do_save_seed = 1;
	      do_save_image = 0;
	    } else if (!strcmp(argv[i], "image")) {
	      do_save_image = 1;
	      do_save_seed = 0;
	    } else {
	      save_file = argv[i];
	    }
          }
          break;
        case 'i':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-image"))) {
            usage(argv[0]);
          }
          do_image = 1;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            /* There is another argument, and it's not a switch, so *
             * we'll treat it as a save file and try to load it.    */
            pgm_file = argv[++i];
          }
          break;
        default:
          usage(argv[0]);
        }
      } else { /* No dash */
        usage(argv[0]);
      }
    }
  }

  if (do_seed) {
    /* Allows me to generate more than one dungeon *
     * per second, as opposed to time().           */
    gettimeofday(&tv, NULL);
    seed = (tv.tv_usec ^ (tv.tv_sec << 20)) & 0xffffffff;
  }

  if (!do_load && !do_image) {
    mvprintw(0, 0, "Seed is %ld.\n", seed);
  } else {
    mvprintw(0, 0, "Seed is %ld.  Dungeon loaded from file.\n", seed);
  }
  srand(seed);

  init_dungeon(&d);

  if (do_load) {
    read_dungeon(&d, load_file);
  } else if (do_image) {
    read_pgm(&d, pgm_file);
  } else {
    gen_dungeon(&d);
  }

  /* Ignoring PC position in saved dungeons.  Not a bug. */
  config_pc(&d);
  gen_monsters(&d);

	io_init_terminal();
	
	game_loop(&d);

	/*
  while (pc_is_alive(&d) && dungeon_has_npcs(&d)) {
    render_dungeon(&d);
    do_moves(&d);
    if (delay) {
      usleep(delay);
    }
  }

  render_dungeon(&d);
	*/

  if (do_save) {
    if (do_save_seed) {
       /* 10 bytes for number, plus dot, extention and null terminator. */
      save_file = malloc(18);
      sprintf(save_file, "%ld.rlg327", seed);
    }
    if (do_save_image) {
      if (!pgm_file) {
	fprintf(stderr, "No image file was loaded.  Using default.\n");
	do_save_image = 0;
      } else {
	/* Extension of 3 characters longer than image extension + null. */
	save_file = malloc(strlen(pgm_file) + 4);
	strcpy(save_file, pgm_file);
	strcpy(strchr(save_file, '.') + 1, "rlg327");
      }
    }
    write_dungeon(&d, save_file);

    if (do_save_seed || do_save_image) {
      free(save_file);
    }
  }

	/*
  printf("%s", pc_is_alive(&d) ? victory : tombstone);
  printf("You defended your life in the face of %u deadly beasts.\n"
         "You avenged the cruel and untimely murders of %u "
         "peaceful dungeon residents.\n",
         d.pc.kills[kill_direct], d.pc.kills[kill_avenged]);
	*/

	endwin(); // ends curses screen

  pc_delete(d.pc.pc);

  delete_dungeon(&d);

  return 0;
}
