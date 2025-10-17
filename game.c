#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include <conio.h>
#include<time.h>
#pragma warning(disable:4996)
#define second 1000
#define LEN 32
#define MALEN 10
#define MAPLINE 100
#define MAPCOL 40
#define MAPCOUNT 4
#define scope 5
#define player_icon 4
#define time_to_finish 90
#define games_in_history 3
#define copyuserfile "copyuser.bin"
#define usersfile "users.bin"
#define massagefile "massages.bin"
#define copymassagefile "copymassages.bin"
#define mapsfile "map.txt"
#define clear "cls"
#define buyingcode "bp_project"
#define type_color "\033[38;2;20;255;255m"
#define console_color "\033[48;2;0;0;0m"
#define chosing_color "\033[48;2;20;20;200m"
typedef struct gamesave {
	int time;
	int coins;
	int stars;
	int win_lose;
	time_t start;
}gamesave;
typedef struct unreaddef {
	char user1[LEN];
	int id;
	int count;
}unreaddef;
typedef struct userdef {
	char name[LEN];
	char pass[LEN];
	char mail[LEN];
	char num[LEN];
	int coin;
	int id;
	int multipyer;
	double timelapser;
	gamesave game[3];
	unreaddef unread[MALEN];
}userdef;
typedef struct massagedef {
	int id1;
	int id2;
	char mass[10000];
}massagedef;
typedef struct nodedef {
	char enter;
	struct nodedef* next;
	struct nodedef* back;
}nodedef;
char map[MAPCOL][MAPLINE];
char map2[MAPCOL][MAPLINE];
char temname[LEN + 1];
int maptell = 1;
int I = 0;
int J = 0;
int droppedI = 0;
int droppedJ = 0;
int droppedI2 = 0;
int droppedJ2 = 0;
char droppedwall=0;
char droppedwall2 = 0;
nodedef* startnode;
void afterhome(FILE * file,userdef* user) {
	static int entered=0;
	static int flag = 0;
	system(clear);
	printf("\n\t\twelcome %s :)", user->name);
	_sleep(second * 1);
	char change = 0;
	while (1) {
		entered = 1;
		while (1) {
			system(clear);
			printf("\n\t\tUSE w AND s TO MOVE AND esc FOR EXIT.");
			printf("\n\t\t");
			if (entered == 1) {
				printf(chosing_color);
			}
			printf("choosing maps and play");
			printf(console_color);
			printf("\n\t\t");
			if (entered == 2) {
				printf(chosing_color);
			}
			printf("history of games");
			printf(console_color);
			printf("\n\t\t");
			if (entered == 3) {
				printf(chosing_color);
			}
			printf("changing user info");
			printf(console_color);
			printf("\n\t\t");
			if (entered == 4) {
				printf(chosing_color);
			}
			printf("massages");
			printf(console_color);
			printf("\n\t\t");
			if (entered == 5) {
				printf(chosing_color);
			}
			printf("histogram");
			printf(console_color);
			printf("\n\t\t");
			if (entered == 6) {
				printf(chosing_color);
			}
			printf("buying coins");
			printf(console_color);
			printf("\n\t\t");
			change = getch();
			if (change == 'w' && entered > 1) {
				entered -= 1;
			}
			else if (change == 's' && entered < 6) {
				entered += 1;
			}
			else if (change == 's' && entered == 6) {
				entered = 1;
			}
			else if (change == 'w' && entered == 1) {
				entered = 6;
			}
			else if (change == 27) {
				entered = 7;
				break;
			}
			else if (change == 13) {
				break;
			}
		}
		flag = 0;
		if (entered == 1) {
			int manum=1;
			char change = 0;
			while (1) {
				system(clear);
				printf("\n\t\tUSE w AND s TO MOVE AND esc FOR EXIT.");
				printf("\n\t\t");
				if (manum == 1) {
					printf(chosing_color);
				}
				printf("easy");
				printf(console_color);
				printf("\n\t\t");
				if (manum == 2) {
					printf(chosing_color);
				}
				printf("medium");
				printf(console_color);
				printf("\n\t\t");
				if (manum == 3) {
					printf(chosing_color);
				}
				printf("Nightmare");
				printf(console_color);
				printf("\n\t\t");
				change = getch();
				if (change == 'w' && manum > 1) {
					manum -= 1;
				}
				else if (change == 's' && manum < MAPCOUNT-1) {
					manum += 1;
				}
				else if (change == 's' && manum == MAPCOUNT-1) {
					manum = 1;
				}
				else if (change == 'w' && manum == 1) {
					manum = MAPCOUNT-1;
				}
				else if (change == 27) {
					manum = MAPCOUNT;
					break;
				}
				else if (change == 13) {
					break;
				}
			}
			if (manum == 1) {
				getmap(manum);
			}
			else if (manum == 2) {
				getmap(manum);
			}
			else if (manum == 3) {
				getmap(manum);
			}
			else {
				continue;
			}
			buying_stuff(file, user);
			
			show_game(game(user,manum,file),manum);
		}
		else if (entered == 2) {
			history_of_games(user);
			continue;
		}
		else if (entered == 3) {
			static int which=0;
			system(clear);
			printf("\n\t\tfirst enter your password.\n\t\t");
			//scanf("%s", temname);
			getpass(temname);
			hasher(temname);
			if (strcmp(user->pass, temname) == 0) {
				printf("\n\t\t1) changing username\n\t\t2) changing password\n\t\t3) changing email\n\t\t4) changing number\n\t\t");
				scanf("%d", &which);
				spacef();
				if (which == 1) {
					printf("\n\t\tenter new username(less than %d charecters):\n\t\t",LEN-2);
					scanf("%s", temname);
					spacef();
					fseek(file, 0, SEEK_SET);
					userdef* usercop = (userdef*)calloc(1, sizeof(userdef));
					while (fread(usercop, sizeof(userdef), 1, file) > 0) {
						if (strcmp(temname, usercop->name) == 0) {
							flag = -1;
							break;
						}
					}
					if (flag == -1) {
						printf("\n\t\tusername already exist.");
						_sleep(second * 2);

						continue;
					}
					else {
						strcpy(user->name, temname);
						fileupdater(file, user);
						printf("\n\t\tusername updated to %s .",user->name);
						_sleep(second * 2);
						continue;
					}
				}
				else if (which == 2) {
					printf("\n\t\tenter new password(less than %d charecters):\n\t\t",LEN-2);
					//scanf("%s", temname);
					getpass(temname);
					hasher(temname);
					//spacef();
					strcpy(user->pass, temname);
					fileupdater(file, user);
					unhash(temname);
					printf("\n\t\tpassword updated to %s .", temname);
					_sleep(second * 1);
					continue;
				}
				else if(which==3){
					printf("\n\t\tenter new email(less than %d charecters):\n\t\t",LEN-2);
					scanf("%s", temname);
					spacef();
					strcpy(user->mail, temname);
					fileupdater(file, user);
					printf("\n\t\temail updated to %s .", user->mail);
					_sleep(second * 2);
					continue;
				}
				else if (which == 4) {
					printf("\n\t\tenter new number(less than %d charecters):\n\t\t",LEN-2);
					scanf("%s", temname);
					spacef();
					strcpy(user->num, temname);
					fileupdater(file, user);
					printf("\n\t\tnumber updated to %s .", user->num);
					_sleep(second * 2);
					continue;
				}
			}
			else {
				printf("\n\t\twrong password.");
				_sleep(second * 2);
				continue;
			}
		}
		else if (entered == 4) {
			massager(file,user);


		}
		else if (entered == 5) {
			histogram_print(user);


		}
		else if (entered == 6) {
			coinbuy(file, user);
			continue;
		}
		else if (entered == 7) {
			return;
		}
		else {
			printf("\n\t\twrong input:/");
			_sleep(second);
			continue;
		}
	}
}
int histogram_print(userdef* user) {
	system(clear);
	int points[games_in_history] = { 0 };
	int time[games_in_history] = { 0 };
	int coinsc[games_in_history] = { 0 };
	int mostamount = 0;
	gamesave* game;
	for (int i = 0; i < games_in_history; i++) {
		game = &user->game[i];
		points[i] = game->coins;
		time[i] = game->time;
		coinsc[i] = game->stars;
		if (points[i] > mostamount) {
			mostamount = points[i];
		}
		if (time[i] / 2 > mostamount) {
			mostamount = time[i] / 2;
		}
		if (coinsc[i] > mostamount) {
			mostamount = coinsc[i];
		}
	}
	printf("\n\t\tTime taken: ");
	printf("\033[48;2;20;250;20m");
	printf("\033[38;2;20;250;20m");
	printf(".");
	printf(console_color);
	printf(type_color);
	printf("\n\t\tCoins earned: ");
	printf("\033[48;2;250;20;20m");
	printf("\033[38;2;250;20;20m");
	printf(".");
	printf(console_color);
	printf(type_color);
	printf("\n\t\tStars collected: ");
	printf("\033[48;2;252;219;3m");
	printf("\033[38;2;252;219;3m");
	printf(".");
	printf(console_color);
	printf(type_color);
	for (; mostamount > 0; mostamount--) {
		printf("\n\t\t");
		for (int i = 0; i < games_in_history; i++) {
			printf("    ");
			if (time[i] / 2 >= mostamount && time[i] % 2 == 0) {
				printf("\033[48;2;20;250;20m");
				printf("\033[38;2;20;250;20m");
				printf(".");
				printf(console_color);
				printf(type_color);
			}
			else {
				printf(" ");
			}
			if (points[i] >= mostamount) {
				printf("\033[48;2;250;20;20m");
				printf("\033[38;2;250;20;20m");
				printf(".");
				printf(console_color);
				printf(type_color);
			}
			else {
				printf(" ");
			}
			if (coinsc[i] >= mostamount) {
				printf("\033[48;2;252;219;3m");
				printf("\033[38;2;252;219;3m");
				printf(".");
				printf(console_color);
				printf(type_color);
			}
			else {
				printf(" ");
			}
			printf("    ");
		}
	}
	printf("\n\t\t");
	for (int i = 0; i < games_in_history; i++) {
		printf("  game :%d  ", i+1);
	}
	printf("\n\t\tClick enter to return.");
	spacef();
	return;
}
int buying_stuff(FILE* file, userdef* user) {
	int entered=1;
	char change=0;
	system(clear);
	while (1) {
		system(clear);
		printf("\n\t\tchoose what you want to buy.(coins: %d)",user->coin);
		printf("\n\t\t");
		if (entered == 1) {
			printf(chosing_color);
		}
		printf("none");
	

		printf(console_color);
		printf("\n\t\t");
		if (entered == 2) {
			printf(chosing_color);
		}
		printf("multiplye the coins -> 20 coins (x%d)",user->multipyer);
		printf(console_color);
		printf("\n\t\t");
		if (entered == 3) {
			printf(chosing_color);
		}
		printf("time passing slower -> 20 coins");
		if (user->timelapser == 1) {
			printf(" (off)");
		}
		else {
			printf(" (on)");
		}
		printf(console_color);
		printf("\n\t\t");
		change = getch();
		if (change == 'w' && entered > 1) {
			entered -= 1;
		}
		else if (change == 's' && entered < 3) {
			entered += 1;
		}
		else if (change == 's' && entered == 3) {
			entered = 1;
		}
		else if (change == 'w' && entered == 1) {
			entered = 3;
		}
		else if (change == 13) {
			break;
		}
	}
	if (entered == 3) {
		if (user->timelapser == 1&&user->coin>9) {
			user->timelapser == 0.5;
			user->coin -= 20;
			fileupdater(file, user);
			system(clear);
			printf("\n\t\tsuccessful buy.");
			_sleep(second * 1);
			return;
		}
		else if (user->coin < 10) {
			system(clear);
			printf("\n\t\tYou don't have enough coins.");
			_sleep(second * 1);
			return;
		}
		else {
			system(clear);
			printf("\n\t\talready activated.");
			_sleep(second * 1);
			return;
		}
	}
	else if (entered == 2) {
		if (user->coin > 9) {
			user->multipyer += 1;
			user->coin -= 20;
			fileupdater(file, user);
			system(clear);
			printf("\n\t\tsuccessful buy.");
			_sleep(second * 1);
		}
		else {
			system(clear);
			printf("\n\t\tYou don't have enough coins.");
			_sleep(second * 1);
			return;
		}
	}
	else {
		return;
	}
}
int history_of_games(userdef* user) {
	system(clear);
	gamesave* game;
	int r, g, b;
	for (int i = 0; i<3; i++) {
		game = &user->game[i];
		if (game->win_lose == 0) {
			if (i == 0) {
				printf("\n\t\tyou have no history.");
			}
			break;
		}
		r = rand() % 155 + 100;
		g= rand() % 155 + 100;
		b= rand() % 155 + 100;
		printf("\033[38;2;%d;%d;%dm", r, g, b);
		printf("\n\t\tgame:%d\n\t\tresult: ", i+1);
		if (game->win_lose == 1) {
			printf("\033[38;2;20;250;20m");
			printf("won :)");
			printf("\033[38;2;%d;%d;%dm", r, g, b);
		}
		else {
			printf("\033[38;2;250;20;20m");
			printf("lost :(");
			printf("\033[38;2;%d;%d;%dm", r, g, b);
		}
		printf("\n\t\tstars collected: %d\n\t\tcoins earned: %d\n\t\ttime taken to finish(in seconds): %d", game->stars,game->coins,game->time);
		char* time_info;
		time_info = ctime(&game->start);
		printf("\n\t\tstarting time: %s\n",time_info);
	}
	printf(type_color);
	printf("\n\t\tpress enter to get back to menu.");
	spacef();
	return;
}
void lose_efect() {
	for (int i = 0; i < 5; ++i) {
		system(clear);
		printf("\033[48;2;205;50;50m");
		_sleep(10);
		system(clear);
		printf("\033[48;2;1;1;1m");
		_sleep(10);
	}
}
void win_efect() {
	for (int i = 0; i < 3; ++i) {
		system(clear);
		printf("\033[48;2;20;220;20m");
		_sleep(300);
		system(clear);
		printf("\033[48;2;1;1;1m");
		_sleep(300);
	}
}
int game(userdef* user,int chosen,FILE* file) {
	nodedef* head = (nodedef*)calloc(1, sizeof(nodedef));
	startnode = head;
	nodedef* move =head;
	nodedef* copy;
	gamesave* this_game=NULL;
	int flag_game = 0;
	gamesave* copy8 = (gamesave*)calloc(1, sizeof(gamesave));
	for (int i = 0; i < 3; i++) {
		this_game = &user->game[i];
		if (this_game->win_lose == 0) {
			flag_game = 1;
			break;
		}
		this_game = NULL;
	}
	if (this_game == NULL) {
		gamesave* copy = &user->game[0];
		gamesave* next = &user->game[1];
		*copy8 = user->game[0];
		*copy = *next;
		copy = &user->game[1];
		next = &user->game[2];
		*copy=*next;
		this_game = &user->game[2];
	}
	head->back = NULL;
	head->next = NULL;
	maptell = 1;
	clock_t start_time, end_time;
	int timetaken = 0;
	system(clear);
	char op;
	
	printf("\n\t\tuse W for up, S for down, A for lef, D for right and ESC for exiting.");
	_sleep(second * 2);
	printmap_full(maptell);
	printf("\n\t\t3");
	_sleep(second / 2);
	printf("\n\t\t2");
	_sleep(second / 2);
	printf("\n\t\t1");
	_sleep(second / 2);
	int coincount = 0;
	start_time = clock();
	time(&this_game->start);
	while (1) {
		system(clear);
		printf("\n\t\tcoins collected: %d", coincount);
		printmap(maptell);
		op = getch();
		if (op == 27) {
			if (flag_game == 1) {
				for (int i = 0; i < 3; i++) {
					this_game = &user->game[i];
					if (this_game->win_lose == 0) {
						*this_game = *copy8;
					}
				}
			}
			else {
				user->game[2] = user->game[1];
				user->game[1] = user->game[0];
				user->game[0] = *copy8;
			}
			free(copy8);
			fileupdater(file, user);
			return 0;
		}
		else if (op == 'w') {
			J--;

		}
		else if (op == 'a') {
			I--;
		}
		else if (op == 's') {
			J++;
		}
		else if (op == 'd') {
			I++;
		}
		else if (op == 'q') {
			maptell *= -1;
		}
		move->enter = op;
		copy = move;
		move->next = (nodedef*)calloc(1, sizeof(nodedef));
		move = move->next;
		move->next = NULL;
		move->back = copy;
		if (maptell == 1 && (map[J][I] == '|' || map[J][I] == '+'|| map[J][I] == '-')) {
			if (user->coin > 9) {
				system(clear);
				char op2;
				printf("\n\t\tyou ran into a wall.\n\t\tpress b if you want to go back one move for 10 coins.");
				op2 = getch();
				if (op2 == 'b') {
					if (op == 'w') {
						J++;
					}
					else if (op == 's') {
						J--;
					}
					else if (op == 'a') {
						I++;
					}
					else if (op == 'd') {
						I--;
					}
					else if (op == 'q') {
						maptell *= -1;
					}
					user->coin -= 10;
					move = move->back;
					gamesave* fr = move->next;
					free(fr);
					continue;
				}
			}
			end_time = clock();
			timetaken = ((int)(end_time - start_time)) / CLOCKS_PER_SEC;
			timetaken = user->timelapser * timetaken;
			this_game->time = timetaken;
			this_game->coins = 0;
			this_game->stars = coincount;
			this_game->win_lose = -1;
			user->multipyer = 1;
			user->timelapser = 1;
			fileupdater(file, user);
			lose_efect();
			printf("\n\t\tYou lost by smashing into a wall. (NO COINS FOR U)\n\t\tStars collected: %d\n\t\tTimer: %d seconds\n\t\tPress enter to continue.",this_game->stars,this_game->time);
			spacef();
			return 2;
		}
		else if (maptell == -1 && (map2[J][I] == '|' || map2[J][I] == '+'|| map2[J][I] == '-')) {
			if (user->coin > 9) {
				system(clear);
				char op2;
				printf("\n\t\tyou ran into a wall.\n\t\tpress b if you want to go back one move for 10 coins.");
				op2 = getch();
				if (op2 == 'b') {
					if (op == 'w') {
						J++;
					}
					else if (op == 's') {
						J--;
					}
					else if (op == 'a') {
						I++;
					}
					else if (op == 'd') {
						I--;
					}
					else if (op == 'q') {
						maptell *= -1;
					}
					user->coin -= 10;
					move = move->back;
					gamesave* fr = move->next;
					free(fr);
					continue;
				}
			}
			end_time = clock();
			timetaken = ((int)(end_time - start_time)) / CLOCKS_PER_SEC;
			timetaken = user->timelapser * timetaken;
			this_game->time = timetaken;
			this_game->coins = 0;
			this_game->stars = coincount;
			this_game->win_lose = -1;
			user->multipyer = 1;
			user->timelapser = 1;
			fileupdater(file, user);
			lose_efect();
			printf("\n\t\tYou lost by smashing into a wall. (NO COINS FOR U)\n\t\tStars collected: %d\n\t\tTimer: %d seconds\n\t\tPress enter to continue.", this_game->stars, this_game->time);
			spacef();
			return 2;
		}
		else if (maptell == 1 && map[J][I] == '>') {
			end_time = clock();
			timetaken = ((int)(end_time - start_time)) / CLOCKS_PER_SEC;
			timetaken = user->timelapser * timetaken;
			this_game->time = timetaken;
			this_game->stars = coincount;
			this_game->win_lose = 1;
			if (timetaken < time_to_finish / 2) {
				timetaken = 3;
			}
			else if (timetaken < time_to_finish) {
				timetaken = 2;
			}
			else {
				timetaken = 1;
			}
			win_efect();
			user->coin += coincount * timetaken * user->multipyer;
			this_game->coins = coincount * timetaken * user->multipyer;
			user->multipyer = 1;
			user->timelapser = 1;
			fileupdater(file, user);
			system(clear);
			printf("\n\t\tYou won by escaping.\n\t\tStars collected: %d\n\t\tCoins earned: %d\n\t\tTimer: %d seconds.\n\t\tPress enter to continue.", this_game->stars, this_game->coins, this_game->time);
			spacef();
			return 1;
		}
		else if (maptell == -1 && map2[J][I] == '>') {
			end_time = clock();
			timetaken = ((int)(end_time - start_time)) / CLOCKS_PER_SEC;
			timetaken = user->timelapser * timetaken;
			this_game->time = timetaken;
			this_game->stars = coincount;
			this_game->win_lose = 1;
			if (timetaken < time_to_finish / 2) {
				timetaken = 3;
			}
			else if (timetaken < time_to_finish) {
				timetaken = 2;
			}
			else {
				timetaken=1;
			}
			win_efect();
			user->coin += coincount*timetaken*user->multipyer;
			this_game->coins = coincount * timetaken * user->multipyer;
			user->multipyer = 1;
			user->timelapser = 1;
			fileupdater(file, user);
			printf("\n\t\tYou won by escaping.\n\t\tStars collected: %d\n\t\tCoins earned: %d\n\t\tTimer: %d seconds.\n\t\tPress enter to continue.", this_game->stars, this_game->coins, this_game->time);
			spacef();
			return 1;
		}
		else if (map[J][I + 1] == '0' || map[J][I - 1] == '0' || map[J + 1][I] == '0' || map[J - 1][I] == '0' || map[J - 1][I + 1] == '0' || map[J - 1][I - 1] == '0' || map[J + 1][I + 1] == '0' || map[J + 1][I - 1] == '0') {
			if (user->coin > 9) {
				system(clear);
				char op2;
				printf("\n\t\tyou ran into a bomb.\n\t\tpress b if you want to go back one move for 10 coins.");
				op2 = getch();
				if (op2 == 'b') {
					if (op == 'w') {
						J++;
					}
					else if (op == 's') {
						J--;
					}
					else if (op == 'a') {
						I++;
					}
					else if (op == 'd') {
						I--;
					}
					else if (op == 'q') {
						maptell *= -1;
					}
					user->coin -= 10;
					move = move->back;
					gamesave* fr = move->next;
					free(fr);
					continue;
				}
			}
			end_time = clock();
			timetaken = ((int)(end_time - start_time)) / CLOCKS_PER_SEC;
			timetaken = user->timelapser * timetaken;
			this_game->time = timetaken;
			this_game->coins = 0;
			this_game->stars = coincount;
			this_game->win_lose = -1;
			user->multipyer = 1;
			user->timelapser = 1;
			fileupdater(file, user);
			bomb_efect(maptell);
			lose_efect();
			system(clear);
			printf("\n\t\tYou lost by exploding. (NO COINS FOR U)\n\t\tStars collected: %d\n\t\tTimer: %d seconds\n\t\tPress enter to continue.", this_game->stars, this_game->time);
			spacef();
			return 3;
		}
		else if (maptell == 1 && map[J][I] > 48 && map[J][I] < 58) {
			teleporter(map[J][I],maptell);
		}
		else if (maptell == -1 && map2[J][I] > 48 && map2[J][I] < 58) {
			teleporter(map2[J][I], maptell);
		}
		else if (maptell == 1 && map[J][I] == '*') {
			map[J][I] = 32;
			if (map2[J][I] == 32||map2[J][I]=='*') {
				map2[J][I] = 32;
			}
			coincount++;
		}
		else if (maptell == -1 && map2[J][I] == '*') {
			map2[J][I] = 32;
			if (map[J][I] == 32||map[J][I]=='*') {
				map[J][I] = 32;
			}
			coincount++;
		}
		else if (maptell == 1 && map[J][I] == '&') {
			system(clear);
			printf("\n\t\tcoins collected: %d", coincount);
			printmap(maptell);
			move->enter = shoot_wall(maptell, chosen,0);
			copy = move;
			move->next = (nodedef*)calloc(1, sizeof(nodedef));
			move = move->next;
			move->next = NULL;
			move->back = copy;
			map[J][I] = 32;
		}
		else if (maptell == -1 && map2[J][I] == '&') {
			system(clear);
			printf("\n\t\tcoins collected: %d", coincount);
			printmap(maptell);
			move->enter = shoot_wall(maptell, chosen,0);
			copy = move;
			move->next = (nodedef*)calloc(1, sizeof(nodedef));
			move = move->next;
			move->next = NULL;
			move->back = copy;
			map2[J][I] = 32;
		}
	}
}
int show_game(int result,int chosen) {
	char ent=0;
	char go=0;
	int coincount=0;
	int starcount = 0;
	int shootcount = 0;
	int shootcount2 = 0;
	getmap(chosen);
	maptell = 1;
	system(clear);
	printf("\n\t\tUse a and d to go back and forward, and esc to end review.\n\t\tcoins collected: 0");
	printmap_full(maptell);
	nodedef* move=startnode;
	while (1) {
		ent = getch();
		if (ent == 'd') {
			go = move->enter;
			result=show_game_move_next(go,chosen,move,&starcount,&shootcount,&shootcount2,&coincount);
			if (result == 1) {
				printf("\n\t\tyou won the game by scaping.\n\t\tpress enter to continue.");
				spacef();
				freelinklist(startnode);
				return;
			}
			else if (result == 2) {
				printf("\n\t\tyou ran into a wall.\n\t\tpress enter to continue.");
				spacef();
				freelinklist(startnode);
				return;
			}
			else if (result == 3) {
				printf("\n\t\tyou ran into a BOMB.\n\t\tpress enter to continue.");
				spacef();
				freelinklist(startnode);
				return;
			}
			else if (result == 5) {
				move = move->next;
			}
			if (move->next == NULL) {
					printf("\n\t\tyou quit the game here.\n\t\tpress enter to continue.");
					spacef();
					freelinklist(startnode);
					return;
				
			}
			move = move->next;
		}
		else if (ent == 'a') {
			if (move -> back == NULL) {
				continue;
			}
			move = move->back;
			if (shootcount == 1) {
				move = move->back;
			}
			else if (shootcount2 == 1) {
				move = move->back;
			}
			go = move->enter;
			if (go == 'w') {
				go = 's';
			}
			else if (go == 's') {
				go = 'w';
			}
			else if (go == 'a') {
				go = 'd';
			}
			else if (go == 'd') {
				go = 'a';
			}
			result = show_game_move_back(go, chosen, move,&starcount,&shootcount,&shootcount2,&coincount);
		}
		else if (ent == 27) {
			return;
		}
	}
}
int show_game_move_back(char op, int chosen, nodedef* move,int* starcount,int* shootcount,int* shootcount2,int* coincount) {
	if (*starcount == 1) {
		if (map[J][I] == 32) {
			map[J][I] = '*';
		}
		if (map2[J][I] == 32) {
			map2[J][I] = '*';
		}
		*coincount-=1;
	}
	else if (*shootcount == 1) {
			map[J][I] = '&';
			map[droppedJ][droppedI] = droppedwall;
	}
	else if (*shootcount2 == 1) {
		map2[J][I] = '&';
		map2[droppedJ2][droppedI2] = droppedwall2;
	}

	if (*starcount > 0) {
		*starcount-=1;
	}
	if (*shootcount > 0) {
		*shootcount-=1;
	}
	if (*shootcount2 > 0) {
		*shootcount2 -= 1;
	}
	if (maptell == 1 && map[J][I] > 48 && map[J][I] < 58) {
		teleporter(map[J][I], maptell);
		move = move->back;
		if (move->enter == 'a') {
			I += 1;
		}
		else if (move->enter == 'd') {
			I -= 1;
		}
		else if (move->enter == 'w') {
			J += 1;
		}
		else if (move->enter == 's') {
			J -= 1;
		}
		move = move->next;
	}
	else if (maptell == -1 && map2[J][I] > 48 && map2[J][I] < 58) {
		teleporter(map2[J][I], maptell);
		move = move->back;
		if (move->enter == 'a') {
			I += 1;
		}
		else if (move->enter == 'd') {
			I -= 1;
		}
		else if (move->enter == 'w') {
			J += 1;
		}
		else if (move->enter == 's') {
			J -= 1;
		}
		move = move->next;
	}
	else if (op == 'w') {
		J--;

	}
	else if (op == 'a') {
		I--;
	}
	else if (op == 's') {
		J++;
	}
	else if (op == 'd') {
		I++;
	}
	else if (op == 'q') {
		maptell *= -1;
	}
	system(clear);
	printf("\n\t\tUse a and d to go back and forward, and esc to end review.\n\t\tcoins collected: %d", *coincount);
	printmap_full(maptell);
	return -1;
}
int freelinklist(nodedef* head) {
	nodedef* next;
	nodedef* now;
	now = head;
	while (now->next != NULL) {
		next = now->next;
		free(now);
		now = next;
	}
	free(now);
	return;
}
int show_game_move_next(char op,int chosen,nodedef* move, int* starcount, int* shootcount,int* shootcount2, int* coincount) {
	if (*shootcount > 0) {
		*shootcount+=1;
	}
	if (*shootcount2 > 0) {
		*shootcount2 += 1;
	}
	if (*starcount > 0) {
		*starcount+=1;
	}
	if (op == 27) {
		return 0;
	}
	else if (op == 'w') {
		J--;

	}
	else if (op == 'a') {
		I--;
	}
	else if (op == 's') {
		J++;
	}
	else if (op == 'd') {
		I++;
	}
	else if (op == 'q') {
		maptell *= -1;
	}
	if (maptell == 1 && (map[J][I] == '|' || map[J][I] == '+' || map[J][I] == '-')) {
		*coincount = 0;
		return 2;
	}
	else if (maptell == -1 && (map2[J][I] == '|' || map2[J][I] == '+' || map2[J][I] == '-')) {
		*coincount = 0;
		return 2;
	}
	else if (maptell == 1 && map[J][I] == '>') {
		*coincount = 0;
		return 1;
	}
	else if (maptell == -1 && map2[J][I] == '>') {
		*coincount = 0;
		return 1;
	}
	else if (map[J][I + 1] == '0' || map[J][I - 1] == '0' || map[J + 1][I] == '0' || map[J - 1][I] == '0' || map[J - 1][I + 1] == '0' || map[J - 1][I - 1] == '0' || map[J + 1][I + 1] == '0' || map[J + 1][I - 1] == '0') {
		*coincount = 0;
		return 3;
	}
	else if (maptell == 1 && map[J][I] > 48 && map[J][I] < 58) {
		teleporter(map[J][I], maptell);
	}
	else if (maptell == -1 && map2[J][I] > 48 && map2[J][I] < 58) {
		teleporter(map2[J][I], maptell);
	}
	else if (maptell == 1 && map[J][I] == '*') {
		map[J][I] = 32;
		if (map2[J][I] == 32) {
			map2[J][I] = 32;
		}
		*starcount = 1;
		*coincount+=1;
	}
	else if (maptell == -1 && map2[J][I] == '*') {
		map2[J][I] = 32;
		if (map[J][I] == 32) {
			map[J][I] = 32;
		}
		*starcount = 1;
		*coincount+=1;
	}
	else if (maptell == 1 && map[J][I] == '&') {
		move = move->next;
		shoot_wall(maptell, chosen,move->enter);
		system(clear);
		printf("\n\t\tUse a and d to go back and forward, and esc to end review.\n\t\tcoins collected: %d", *coincount);
		printmap_full(maptell);
		map[J][I] = 32;
		*shootcount = 1;
		return 5;
	}
	else if (maptell == -1 && map2[J][I] == '&') {
		move = move->next;
		shoot_wall(maptell, chosen, move->enter);
		system(clear);
		printf("\n\t\tUse a and d to go back and forward, and esc to end review.\n\t\tcoins collected: %d", *coincount);
		printmap_full(maptell);
		map2[J][I] = 32;
		*shootcount2 = 1;
		return 5;
	}
	system(clear);
	printf("\n\t\tUse a and d to go back and forward, and esc to end review.\n\t\tcoins collected: %d", *coincount);
	printmap_full(maptell);
	return -1;
}
int shoot_wall(int maptell,int chosen,int flag) {
	char a=0;
	int leni = 0, lenj = 0;
	if (chosen == 1) {
		leni = 32;
		lenj = 16;
	}
	else if (chosen == 2) {
		leni = 31;
		lenj = 16;
	}
	else if (chosen == 3) {
		leni = 53;
		lenj = 26;
	}
	int go=0;
	if (flag == 0) {
		a = getch();
	}
	else {
		a = flag;
	}
	if (maptell == 1) {
		if (a == 'w') {
			while (J - go > 0) {
				if (map[J - go][I] == '|' || map[J - go][I] == '+' || map[J - go][I] == '-'){
					droppedwall = map[J - go][I];
					map[J - go][I] = 32;
					droppedI = I;
					droppedJ = J - go;
					
					return a;
				}
				go++;
			}
		}
		else if (a == 'a') {
			while (I - go > 0) {
				if (map[J][I - go] == '|' || map[J][I - go] == '+' || map[J][I - go] == '-') {
					droppedwall = map[J][I - go];
					map[J][I - go] = 32;
					droppedI = I - go;
					droppedJ = J;
					
					return a;
				}
				go++;
			}
		}
		else if (a == 's') {
			while (J + go < lenj) {
				if (map[J+go][I] == '|' || map[J+go][I] == '+' || map[J+go][I] == '-') {
					droppedwall = map[J + go][I];
					map[J + go][I] = 32;
					droppedI = I;
					droppedJ = J + go;
					
					return a;
				}
				go++;
			}
		}
		else if (a == 'd') {
			while (I + go < leni) {
				if (map[J][I+go] == '|' || map[J][I+go] == '+' || map[J][I+go] == '-') {
					droppedwall = map[J][I + go];
					map[J][I + go] = 32;
					droppedI = I + go;
					droppedJ = J;
					
					return a;
				}
				go++;
			}
		}

	}
	else if (maptell = -1) {
		if (a == 'w') {
			while (J - go > 0) {
				if (map2[J - go][I] == '|' || map2[J - go][I] == '+' || map2[J - go][I] == '-') {
					droppedwall2 = map2[J - go][I];
					map2[J - go][I] = 32;
					droppedI2 = I;
					droppedJ2 = J - go;

					return a;
				}
				go++;
			}
		}
		else if (a == 'a') {
			while (I - go > 0) {
				if (map2[J][I - go] == '|' || map2[J][I - go] == '+' || map2[J][I - go] == '-') {
					droppedwall2 = map2[J][I - go];
					map2[J][I - go] = 32;
					droppedI2 = I - go;
					droppedJ2 = J;

					return a;
				}
				go++;
			}
		}
		else if (a == 's') {
			while (J + go < lenj) {
				if (map2[J + go][I] == '|' || map2[J + go][I] == '+' || map2[J + go][I] == '-') {
					droppedwall2 = map2[J + go][I];
					map2[J + go][I] = 32;
					droppedI2 = I;
					droppedJ2 = J + go;

					return a;
				}
				go++;
			}
		}
		else if (a == 'd') {
			while (I + go < leni) {
				if (map2[J][I + go] == '|' || map2[J][I + go] == '+' || map2[J][I + go] == '-') {
					droppedwall2 = map2[J][I + go];
					map2[J][I + go] = 32;
					droppedI2 = I + go;
					droppedJ2 = J;
					return a;
				}
				go++;
			}
		}
	}
}
int bomb_efect(int maptell) {
	if (maptell == 1) {
		for (int i = -1; i < 2; i++) {
			for (int v = -1; v < 2; v++) {
				map[i+J][v+I] = '#';
			}
		}
	}
	else if (maptell == -1) {
		for (int i = -1; i < 2; i++) {
			for (int v = -1; v < 2; v++) {
				map2[i+J][v+I] = '#';
			}
		}
	}
	system(clear);
	printmap(maptell);
	_sleep(second * 1);
	if (maptell == 1) {
		for (int i = -2; i < 3; i++) {
			for (int v = -2; v < 3; v++) {
				map[i + J][v + I] = '#';
			}
		}
	}
	else if (maptell == -1) {
		for (int i = -2; i < 3; i++) {
			for (int v = -2; v < 3; v++) {
				map2[i + J][v + I] = '#';
			}
		}
	}
	system(clear);
	printmap(maptell);
	_sleep(second * 1);
	if (maptell == 1) {
		for (int i = -3; i < 4; i++) {
			for (int v = -3; v < 4; v++) {
				map[i + J][v + I] = '#';
			}
		}
	}
	else if (maptell == -1) {
		for (int i = -3; i < 4; i++) {
			for (int v = -3; v < 4; v++) {
				map2[i + J][v + I] = '#';
			}
		}
	}
	system(clear);
	printmap(maptell);
	_sleep(second * 1);
}
int teleporter(char port,int maptell) {
	if (maptell == 1) {
		for (int i = 0; i < MAPCOL * MAPCOUNT; i++) {
			for (int v = 0; v < MAPLINE; v++) {
				if (map[i][v] == port && (i != J || v != I)) {
					I = v;
					J = i;
					return;
				}
				else if (map[i][v] == 'n') {
					break;
				}
				else if (map[i][v] == 'D') {
					return;
				}
			}
		}
	}
	else if (maptell == -1) {
		for (int i = 0; i < MAPCOL * MAPCOUNT; i++) {
			for (int v = 0; v < MAPLINE; v++) {
				if (map2[i][v] == port && (i != J || v != I)) {
					I = v;
					J = i;
					return;
				}
				else if (map2[i][v] == 'n') {
					break;
				}
				else if (map2[i][v] == 'L') {
					return;
				}
			}
		}
	}
}
int massager(FILE* file,userdef* user) {
	userdef* secuser = (userdef*)calloc(1, sizeof(userdef));
	massagedef* chat = (massagedef*)calloc(1, sizeof(massagedef));
	FILE* fmass = fopen(massagefile, "rb+");
    unreaddef* idn = (unreaddef*)calloc(1, sizeof(unreaddef));
	static int flag = 0;
	static int who = 0;
	static int idi = 0;
	static char c;
	while (1) {
		system(clear);
		unreadprint(file,user);
		printf("\n\t\tenter the username you want to massage to:\n\t\t'exit' for returning.\n\t\t");
		scanf("%s", temname);
		spacef();
		if (strcmp(temname, user->name) == 0) {
			system(clear);
			printf("\n\t\tThat's you :)");
			_sleep(second * 1);
			continue;
		}
		who = 0;
		idi = 0;
		fseek(file, 0, SEEK_SET);
		while (fread(secuser, sizeof(userdef), 1, file) > 0) {
			if (strcmp(temname, secuser->name) == 0) {
				idi = secuser->id;
				break;
			}
		}
		if (strcmp(temname, "exit") == 0) {
			fclose(fmass);
			free(chat);
			free(secuser);
			return;
		}
		if (idi == 0) {
			printf("\n\t\tuser not found.");
			_sleep(second * 2);
			continue;
		}
		else {
			fseek(fmass, 0, SEEK_SET);
			while (fread(chat, sizeof(massagedef), 1, fmass) > 0) {
				if (chat->id1==user->id&&chat->id2==secuser->id) {
					who ='>';
					break;
				}
				else if (chat->id1==secuser->id&&chat->id2==user->id) {
					who ='^';
					break;
				}
			}
			if (who == 0) {
				who = '>';
				massagedef* chat2 = (massagedef*)calloc(1, sizeof(massagedef));
				chat2->id1 = user->id;
				chat2->id2 = secuser->id;
				*(chat) = *(chat2);
				for (int i = 0; i < MALEN; i++) {
					idn = &user->unread[i];
					if (idn->id == 0) {
						strcpy(idn->user1, secuser->name);
						idn->id = secuser->id;
						idn->count = 0;
						break;
					}
				}
				fileupdater(file, user);
				for (int i = 0; i < MALEN; i++) {
					idn = &secuser->unread[i];
					if (idn->id== 0) {
						strcpy(idn->user1,user->name);
						idn->count = 0;
						idn->id = user->id;
						break;
					}
				}
				fileupdater(file, secuser);
				//strcat(chat->mass, "enjoy:)\0");
				fseek(fmass, 0, SEEK_END);
				fwrite(chat2, sizeof(massagedef), 1, fmass);
				FILE* fcopym = fopen(copymassagefile, "rb+");
				fwrite(chat2, sizeof(massagedef), 1, fcopym);
				fclose(fcopym);
			}
		}
		printf("\n\t\there is your previous chat:");
		chatprinter(chat,who,secuser);
		for (int i = 0; i < MALEN; i++) {
			idn = &user->unread[i];
			//if (strcmp(idn->user1, secuser->name) == 0) {
			if(idn->id==secuser->id){
				idn->count = 0;
				break;
			}
		}
		fileupdater(file, user);
		char* newmass = (char*)calloc(1000, sizeof(char));
		newmass[0]=who;
		printf("\n\t\twrite a new massage ('#' for canceling):\n\t\t");
		for(int i=1;1;i++) {
			c = getchar();
			if (c == '#') {
				free(newmass);
				break;
			}
			else if (c == '\n') {
				newmass[i] = '\0';
				strcat(chat->mass, newmass);
				free(newmass);
				break;
			}
			else {
				newmass[i] = c;
			}
		}
		if (c == '#') {
			continue;
		}
		for (int i = 0; i < MALEN; i++) {
			idn = &secuser->unread[i];
			//if (strcmp(idn->user1,user->name) == 0) {
			if(idn->id==user->id){
				idn->count += 1;
				break;
			}
		}
		fileupdater(file, secuser);
		chatupdater(fmass,chat);
		system(clear);
		printf("\n\t\tmassage sent.");
		chatprinter(chat,who,secuser);
		getchar();
	}
}
int unreadprint(FILE* file,userdef* user) {
	unreaddef* idn11 = (unreaddef*)calloc(1, sizeof(unreaddef));
	unreaddef* idn22 = (unreaddef*)calloc(1, sizeof(unreaddef));
	unreaddef* idn33 = (unreaddef*)calloc(1, sizeof(unreaddef));
	userdef* copy = (userdef*)calloc(1,sizeof(userdef));
	for (int i = MALEN,flag=0; i > 0; i--) {
		for (int v = 0; v < i-1; v++) {
			idn11= &user->unread[v];
			idn22 = &user->unread[v + 1];
			if (idn11->count < idn22->count) {
				*(idn33) = *(idn11);
				*(idn11) = *(idn22);
				*(idn22) = *(idn33);
			}
			if (flag == 0&&i==MALEN) {
				fseek(file, 0, SEEK_SET);
				while (fread(copy, sizeof(userdef), 1, file) > 0) {
					if (idn11->id == copy->id) {
						strcpy(idn11->user1,copy->name);
						break;
					}
				}
				flag = 1;
			}
			if (i == MALEN) {
				fseek(file, 0, SEEK_SET);
				while (fread(copy, sizeof(userdef), 1, file) > 0) {
					if (idn22->id == copy->id) {
						strcpy(idn22->user1, copy->name);
						break;
					}
				}
			}
		}
	}
	printf("\033[38;2;150;100;150m");
	for (int i = 0; i < MALEN; i++) {
		idn11 = &user->unread[i];
		if (idn11->id != 0) {
			printf("\n\t\t%d massages from %s.", idn11->count, idn11->user1);
		}
		else {
			break;
		}
	}
	printf(type_color);
	return;
}
int chatupdater(FILE* fmass,massagedef* chat) {
	FILE* fcopym= fopen(copymassagefile, "rb+");
	massagedef* copy= (massagedef*)calloc(1, sizeof(massagedef));
	fseek(fmass, 0, SEEK_SET);
	fseek(fcopym, 0, SEEK_SET);
	while (fread(copy, sizeof(massagedef), 1, fmass)>0) {
		if (chat->id1 == copy->id1 && chat->id2 == copy->id2) {
			fseek(fcopym, sizeof(massagedef), SEEK_CUR);
			break;
		}
		fseek(fcopym, sizeof(massagedef), SEEK_CUR);
	}
	fseek(fmass, sizeof(massagedef)*-1, SEEK_CUR);
	fwrite(chat, sizeof(massagedef), 1, fmass);
	while (fread(copy, sizeof(massagedef), 1, fcopym) > 0) {
		fwrite(copy, sizeof(massagedef), 1, fmass);
	}
	fseek(fcopym,0, SEEK_SET);
	fseek(fmass,0, SEEK_SET);
	while (fread(copy, sizeof(massagedef), 1, fmass) > 0) {
		fwrite(copy, sizeof(massagedef), 1, fcopym);
	}
	fclose(fcopym);
	return;
}
int chatprinter(massagedef* chat,int who,userdef* secuser) {
	static char c;
	printf("\n\t\t\033[38;2;200;20;20m");
	for (int i = 0; 1; i++) {
		c = chat->mass[i];
		if (c == who) {
			printf("\033[38;2;20;200;20m");
			printf("\n\t\tYou: ");
		}
		else if (c == '^') {
			printf("\033[38;2;20;20;200m");
			printf("\n\t\t%s: ", secuser->name);
		}
		else if (c == '>') {
			printf("\033[38;2;20;20;200m");
			printf("\n\t\t%s: ", secuser->name);
		}
		else if (c == '\0') {
			printf("\033[38;2;255;255;255m");
			break;
		}
		else {
			printf("%c", c);
		}
	}
}
int getpass(char arr[]) {
	char c;
	for (int i = 0; i < LEN; i++) {
		c = getch();
		if (c == 8) {
			printf("\n\t\tyou earased that one, try again.\n\t\t");
			i= -1;
			continue;
		}
		if (c == '\n'||c=='\r') {
			arr[i] = '\0';
			break;
		}
		else {
			arr[i] = c;
			printf("*");
		}
	}
}
int coinbuy(FILE* file, userdef* user) {
	while (1) {
		system(clear);
		printf("\n\t\tcurrent coins: %d\n\t\tenter the code.\n\t\t'exit' for exiting.\n\t\t", user->coin);
		scanf("%s", temname);
		spacef();
		if (strcmp(temname, buyingcode) == 0) {
			user->coin += 100;
			fileupdater(file, user);
			printf("\n\t\tcoins increased by 100.");
			_sleep(2 * second);
			return;
		}
		else if (strcmp(temname, "exit") == 0) {
			return;
		}
		else {
			printf("\n\t\twrong code!!!");
			_sleep(5 * second);
			continue;
		}
	}
}
int spacef() {
    char a = 0;
	while (1) {
		scanf("%c", &a);
		//a = getch();
		if (a == '\n')break;
		//if (a == 13)break;
	}
	return;
}
int fileupdater(FILE* file, userdef* user) {
	FILE* fcopy = fopen(copyuserfile, "rb+");
	userdef* usercop = (userdef*)calloc(1, sizeof(userdef));
	if (user != NULL) {
		static int flag = 0;
		fseek(file, 0, SEEK_SET);
		fseek(fcopy, 0, SEEK_SET);
		while (fread(usercop, sizeof(userdef), 1, file) > 0) {
			if (strcmp(user->name, usercop->name) == 0||strcmp(user->num,usercop->num)==0) {
				fseek(fcopy, sizeof(userdef), SEEK_CUR);
				flag = 1;
				break;
			}
			fseek(fcopy, sizeof(userdef), SEEK_CUR);
		}
		if (flag == 1) {
			fseek(file, sizeof(userdef) * -1, SEEK_CUR);
			fwrite(user, sizeof(userdef), 1, file);
			while (fread(usercop, sizeof(userdef), 1, fcopy) > 0) {
				fwrite(usercop, sizeof(userdef), 1, file);
			}
		}
	}
	fseek(file, 0, SEEK_SET);
	fseek(fcopy, 0, SEEK_SET);
	while (fread(usercop, sizeof(userdef), 1, file) > 0) {
		fwrite(usercop, sizeof(userdef), 1, fcopy);
	}
	fclose(fcopy);
	return;
}
int home_page() {
	FILE* file = fopen(usersfile, "rb+");
	fileupdater(file, NULL);
	userdef* user = (userdef*)calloc(1, sizeof(userdef));
	static int entered = 0;
	static int flag = 0;
	char change;
	while (1) {
		entered = 1;
		while (1) {
			system(clear);
			printf("\n\t\tUSE w AND s TO MOVE AND esc FOR EXIT.");
			printf("\n\t\t");
			if (entered == 1) {
				printf(chosing_color);
			}
			printf("sign in");
			printf(console_color);
			printf("\n\t\t");
			if (entered == 2) {
				printf(chosing_color);
			}
			printf("sing up");
			printf(console_color);
			printf("\n\t\t");
			if (entered == 3) {
				printf(chosing_color);
			}
			printf("forgot password");
			printf(console_color);
			printf("\n\t\t");
			change = getch();
			if (change == 'w' && entered > 1) {
				entered -= 1;
			}
			else if (change == 's' && entered < 3) {
				entered += 1;
			}
			else if (change == 's' && entered == 3) {
				entered = 1;
			}
			else if (change == 'w' && entered == 1) {
				entered = 3;
			}
			else if (change == '@') {
				entered = 5;
				break;
			}
			else if (change == 27) {
				entered = 4;
				break;
			}
			else if (change == 13) {
				break;
			}
		}
		if (entered == 1) {
			flag = 0;
			fseek(file, 0, SEEK_SET);
			system(clear);
			printf("\n\t\tenter your username:\n\t\t");
			scanf("%s", temname);
			spacef();
			//temname[strcspn(temname, "\n")] = '\0';
			while (fread(user, sizeof(userdef), 1, file) > 0) {
				if (strcmp(temname, user->name) == 0) {
					printf("\n\t\tpassword:\n\t\t");
					getpass(temname);
					hasher(temname);
					//spacef();
					//temname[strcspn(temname, "\n")] = '\0';
					if (strcmp(user->pass, temname) == 0) {
						flag = 1;
						break;
					}
					else { 
						flag = 2;
						break;
					}

				}
				else if (flag != 2) {
					flag = 3;
				}
			}
			if (flag == 1) {
				afterhome(file,user);
				continue;
			}
			else if (flag == 2) {
				printf("\n\t\twrong password");
				_sleep(second * 2);
				continue;
			}
			else if (flag == 3||flag==0) {
				printf("\n\t\tusername not found");
				_sleep(second * 2);
				continue;
			}
		}
		else if (entered == 2) {
			flag = 0;
			fseek(file, 0, SEEK_SET);
			system(clear);
			printf("\n\t\tenter your username(less than %d charecters):\n\t\t",LEN-2);
			scanf("%s", temname);
			spacef();
			//temname[strcspn(temname, "\n")] = '\0';
			while (fread(user, sizeof(userdef), 1, file) > 0) {
				if (strcmp(temname, user->name) == 0) {
					flag = -1;
					break;
				}
			}
			if (flag != -1) {
				strcpy(user->name, temname);
				printf("\n\t\tpassword(less than %d charecters):\n\t\t",LEN-2);
				getpass(temname);
				hasher(temname);
			//	temname[strcspn(temname, "\n")] = '\0';
				strcpy(user->pass, temname);
				printf("\n\t\temail(less than %d charecters):\n\t\t",LEN-2);
				scanf("%s", user->mail);
				spacef();
				//temname[strcspn(temname, "\n")] = '\0';
				//strcpy(user->mail, temname);
				printf("\n\t\tphone number:\n\t\t");
				scanf("%s", temname);
				spacef();
				strcpy(user->num, temname);
				fseek(file, 0, SEEK_SET);
				userdef* cpy = (userdef*)calloc(1, sizeof(userdef));
				user->id = 1;
				while (fread(cpy, sizeof(userdef), 1, file) > 0) {
					user->id += 1;
				}
				user->multipyer = 2;
				user->timelapser = 1;
				user->coin = 0;
				gamesave* non = (gamesave*)calloc(1,sizeof(gamesave));
				user->game[0] = *non;
				user->game[1] = *non;
				user->game[2] = *non;
				free(non);
				fseek(file, 0,SEEK_END);
				fwrite(user, sizeof(userdef), 1, file);
				afterhome(file, user);
				continue;
			}
			else if (flag == -1) {
				printf("\n\t\tusername already exist");
				_sleep(second * 2);
				continue;
			}

		}
		else if (entered == 3) {
			flag = 0;
			static char copy[LEN];
			fseek(file, 0, SEEK_SET);
			system(clear);
			printf("\n\t\tenter your username:\n\t\t");
			scanf("%s", temname);
			spacef();
			//temname[strcspn(temname, "\n")] = '\0';
			while (fread(user, sizeof(userdef), 1, file) > 0) {
				if (strcmp(temname, user->name) == 0) {
					flag = -1;
					break;
				}
			}
			if (flag == -1) {
				printf("\n\t\temail:\n\t\t");
				scanf("%s", temname);
				spacef();
				//temname[strcspn(temname, "\n")] = '\0';
				printf("\n\t\tnumber:\n\t\t");
				scanf("%s", copy);
				spacef();
				if (strcmp(user->mail, temname) == 0&&strcmp(user->num,copy)==0) {
					printf("\n\t\tnew password(less than %d charecters):\n\t\t",LEN-2);
					scanf("%s", temname);
					spacef();
					hasher(temname);
					//temname[strcspn(temname, "\n")] = '\0';
					strcpy(user->pass, temname);
					fileupdater(file, user);
					afterhome(file, user);
					continue;
				}
				else {
					printf("\n\t\twrong number or email.");
					_sleep(2 * second);
					continue;
				}
			}
			else {
				printf("\n\t\tusername not found...");
				_sleep(second * 2);
				continue;
			}
		}
		else if (entered == 4) {
			free(user);
			fclose(file);
			return 0;
		}
		else if (entered == 5) {
			fseek(file, 0, SEEK_SET);
			while (fread(user, sizeof(userdef), 1, file) > 0) {
				strcpy(temname, user->pass);
				unhash(temname);
				printf("\n\t\tuser: %d: %s\n\t\tpass: %s\n\t\tmail: %s\n\t\tnum: %s",user->id, user->name,temname, user->mail, user->num);
			}
			getchar();
		}
		else{
		}
	}
}
int hasher(char c[]) {
	for (int i = 0; 1; i++) {
		if (c[i] == '\0')break;
		else {
			c[i] += 15;
		}
	}
	return;
}
int unhash(char c[]) {
	for (int i = 0; 1; i++) {
		if (c[i] == '\0')break;
		else {
			c[i] -= 15;
		}
	}
	return;
}
int getmap(int chosen) {
	FILE* fmap = fopen(mapsfile, "r");
	char c=0;
	if (chosen > 0) {
		while (fread(&c, sizeof(char), 1, fmap) > 0) {
			if (c == 'E'&&chosen==1) {
				for (int i = 0; i < MAPCOL * MAPCOUNT; i++) {
					for (int v = 0; v < MAPLINE; v++) {
						fread(&c, sizeof(char), 1, fmap);
						if (c == 'D') {
							map[i][v] = c;
							fread(&c, sizeof(char), 1, fmap);
							for (int i = 0; i < MAPCOL * MAPCOUNT; i++) {
								for (int v = 0; v < MAPLINE; v++) {
									fread(&c, sizeof(char), 1, fmap);
									if (c == 'L') {
										map2[i][v] = c;
										fclose(fmap);
										return;
									}
									else if (c == '\n') {
										break;
									}
									else {
										map2[i][v] = c;
									}
								}
							}
						}
						else if (c == 'P') {
							I = v;
							J = i;
							map[i][v] = 32;
						}
						else if (c == '\n') {
							break;
						}
						else {
							map[i][v] = c;
						}
					}
				}
			}
			else if (c == 'H'&&chosen==3) {
				for (int i = 0; i < MAPCOL * MAPCOUNT; i++) {
					for (int v = 0; v < MAPLINE; v++) {
						fread(&c, sizeof(char), 1, fmap);
						if (c == 'D') {
							map[i][v] = c;
							fread(&c, sizeof(char), 1, fmap);
							for (int i = 0; i < MAPCOL * MAPCOUNT; i++) {
								for (int v = 0; v < MAPLINE; v++) {
									fread(&c, sizeof(char), 1, fmap);
									if (c == 'L') {
										map2[i][v] = c;
										fclose(fmap);
										return;
									}
									else if (c == '\n') {
										break;
									}
									else {
										map2[i][v] = c;
									}
								}
							}
						}
						else if (c == 'P') {
							I = v;
							J = i;
							map[i][v] = 32;
						}
						else if (c == '\n') {
							break;
						}
						else {
							map[i][v] = c;
						}
					}
				}
			}
			else if (c == 'M' && chosen == 2) {
				for (int i = 0; i < MAPCOL * MAPCOUNT; i++) {
					for (int v = 0; v < MAPLINE; v++) {
						fread(&c, sizeof(char), 1, fmap);
						if (c == 'D') {
							map[i][v] = c;
							fread(&c, sizeof(char), 1, fmap);
							for (int i = 0; i < MAPCOL * MAPCOUNT; i++) {
								for (int v = 0; v < MAPLINE; v++) {
									fread(&c, sizeof(char), 1, fmap);
									if (c == 'L') {
										map2[i][v] = c;
										fclose(fmap);
										return;
									}
									else if (c == '\n') {
										break;
									}
									else {
										map2[i][v] = c;
									}
								}
							}
						}
						else if (c == 'P') {
							I = v;
							J = i;
							map[i][v] = 32;
						}
						else if (c == '\n') {
							break;
						}
						else {
							map[i][v] = c;
						}
					}
				}
			}
		}
	}
}
int printmap(int which) {
	printf("\n\t\t");
	if (which == 1) {
		for (int i = 0; i < MAPCOL; i++) {
			for (int v = 0; v < MAPLINE; v++) {
				if ((I > v && I - v > scope) || (v > I && v - I > scope) || (i > J && i - J > scope) || (J > i && J - i > scope)) {
					if (map[i][v] != 'n' && map[i][v] != 'D') {
						printf(" ");
						continue;
					}
				}
				if (v == I && i == J) {
					printf("%c", player_icon);
				}
				else if (map[i][v] == 'D') {
					return;
				}
				else if (map[i][v] == 'n') {
					printf("\n\t\t");
					break;
				}
				else if (map[i][v] == '>') {
					printf("   ");
				}
				else if(map[i][v] == '|'|| map[i][v] == '+'|| map[i][v] == '-'){
					printf("\033[48;2;250;20;20m");
					printf("\033[38;2;0;0;0m");
					printf("%c", map[i][v]);
					printf("\033[48;2;0;0;0m");
					printf(type_color);
				}
				else if (map[i][v] == '#') {
					printf("\033[48;2;235;130;26m");
					printf("\033[38;2;0;0;0m");
					printf("%c", map[i][v]);
					printf("\033[48;2;0;0;0m");
					printf(type_color);
				}
				else if (map[i][v] == '0') {
					printf("\033[38;2;235;95;36m");
					printf("%c", map[i][v]);
					printf(type_color);
				}
				else if (map[i][v] == '*') {
					printf("\033[38;2;37;232;115m");
					printf("%c", map[i][v]);
					printf(type_color);
				}
				else if (map[i][v] == '1') {
					printf("\033[38;2;37;50;232m");
					printf("%c", map[i][v]);
					printf(type_color);
				}
				else if (map[i][v] == '2') {
					printf("\033[38;2;232;37;177m");
					printf("%c", map[i][v]);
					printf(type_color);
				}
				else if (map[i][v]>50&&map[i][v]<58) {
					printf("\033[38;2;241;252;30m");
					printf("%c", map[i][v]);
					printf(type_color);
				}
				else if (map[i][v] == '&') {
					printf("\033[38;2;30;171;252m");
					printf("%c", map[i][v]);
					printf(type_color);
				}
				else {
					printf("%c", map[i][v]);
				}
			}
		}
	}
	else if (which == -1) {
		for (int i = 0; i < MAPCOL; i++) {
			for (int v = 0; v < MAPLINE; v++) {
				if ((I > v && I - v > scope) || (v > I && v - I > scope) || (i > J && i - J > scope) || (J > i && J - i > scope)) {
					if (map2[i][v] != 'n' && map2[i][v] != 'L') {
						printf(" ");
						continue;
					}
				}
				if (v == I && i == J) {
					printf("%c", player_icon);
				}
				else if (map2[i][v] == 'L') {
					return;
				}
				else if (map2[i][v] == 'n') {
					printf("\n\t\t");
					break;
				}
				else if (map2[i][v] == '>') {
					printf("   ");
				}
				else if (map2[i][v] == '|' || map2[i][v] == '+' || map2[i][v] == '-') {
					printf("\033[48;2;250;20;250m");
					printf("\033[38;2;0;0;0m");
					printf("%c", map2[i][v]);
					printf("\033[48;2;0;0;0m");
					printf(type_color);
				}
				else if (map2[i][v] == '#') {
					printf("\033[48;2;235;130;26m");
					printf("\033[38;2;0;0;0m");
					printf("%c", map2[i][v]);
					printf("\033[48;2;0;0;0m");
					printf(type_color);
				}
				else if (map2[i][v] == '0') {
					printf("\033[38;2;235;95;36m");
					printf("%c", map2[i][v]);
					printf(type_color);
				}
				else if (map2[i][v] == '*') {
					printf("\033[38;2;37;232;115m");
					printf("%c", map2[i][v]);
					printf(type_color);
				}
				else if (map2[i][v] == '1') {
					printf("\033[38;2;37;50;232m");
					printf("%c", map2[i][v]);
					printf(type_color);
				}
				else if (map2[i][v] == '2') {
					printf("\033[38;2;232;37;177m");
					printf("%c", map2[i][v]);
					printf(type_color);
				}
				else if (map2[i][v] > 50 && map2[i][v] < 58) {
					printf("\033[38;2;241;252;30m");
					printf("%c", map2[i][v]);
					printf(type_color);
				}
				else if (map2[i][v] == '&') {
					printf("\033[38;2;30;171;252m");
					printf("%c", map2[i][v]);
					printf(type_color);
				}
				else {
					printf("%c", map2[i][v]);
				}
			}
		}
	}
}
int printmap_full(int which) {
	printf("\n\t\t");
	if (which == 1) {
		for (int i = 0; i < MAPCOL; i++) {
			for (int v = 0; v < MAPLINE; v++) {
				if (v == I && i == J) {
					printf("%c", player_icon);
				}
				else if (map[i][v] == 'D') {
					return;
				}
				else if (map[i][v] == 'n') {
					printf("\n\t\t");
					break;
				}
				else if (map[i][v] == '>') {
					printf("   ");
				}
				else if (map[i][v] == '|' || map[i][v] == '+' || map[i][v] == '-') {
					printf("\033[48;2;250;20;20m");
					printf("\033[38;2;0;0;0m");
					printf("%c", map[i][v]);
					printf("\033[48;2;0;0;0m");
					printf(type_color);
				}
				else if (map[i][v] == '#') {
					printf("\033[48;2;235;130;26m");
					printf("\033[38;2;0;0;0m");
					printf("%c", map[i][v]);
					printf("\033[48;2;0;0;0m");
					printf(type_color);
				}
				else if (map[i][v] == '0') {
					printf("\033[38;2;235;95;36m");
					printf("%c", map[i][v]);
					printf(type_color);
				}
				else if (map[i][v] == '*') {
					printf("\033[38;2;37;232;115m");
					printf("%c", map[i][v]);
					printf(type_color);
				}
				else if (map[i][v] == '1') {
					printf("\033[38;2;37;50;232m");
					printf("%c", map[i][v]);
					printf(type_color);
				}
				else if (map[i][v] == '2') {
					printf("\033[38;2;232;37;177m");
					printf("%c", map[i][v]);
					printf(type_color);
				}
				else if (map[i][v] > 50 && map[i][v] < 58) {
					printf("\033[38;2;241;252;30m");
					printf("%c", map[i][v]);
					printf(type_color);
				}
				else if (map[i][v] == '&') {
					printf("\033[38;2;30;171;252m");
					printf("%c", map[i][v]);
					printf(type_color);
				}
				else {
					printf("%c", map[i][v]);
				}
			}
		}
	}
	else if (which == -1) {
		for (int i = 0; i < MAPCOL; i++) {
			for (int v = 0; v < MAPLINE; v++) {
				if (v == I && i == J) {
					printf("%c", player_icon);
				}
				else if (map2[i][v] == 'L') {
					return;
				}
				else if (map2[i][v] == 'n') {
					printf("\n\t\t");
					break;
				}
				else if (map2[i][v] == '>') {
					printf("   ");
				}
				else if (map2[i][v] == '|' || map2[i][v] == '+' || map2[i][v] == '-') {
					printf("\033[48;2;250;20;250m");
					printf("\033[38;2;0;0;0m");
					printf("%c", map2[i][v]);
					printf("\033[48;2;0;0;0m");
					printf(type_color);
				}
				else if (map2[i][v] == '#') {
					printf("\033[48;2;235;130;26m");
					printf("\033[38;2;0;0;0m");
					printf("%c", map2[i][v]);
					printf("\033[48;2;0;0;0m");
					printf(type_color);
				}
				else if (map2[i][v] == '0') {
					printf("\033[38;2;235;95;36m");
					printf("%c", map2[i][v]);
					printf(type_color);
				}
				else if (map2[i][v] == '*') {
					printf("\033[38;2;37;232;115m");
					printf("%c", map2[i][v]);
					printf(type_color);
				}
				else if (map2[i][v] == '1') {
					printf("\033[38;2;37;50;232m");
					printf("%c", map2[i][v]);
					printf(type_color);
				}
				else if (map2[i][v] == '2') {
					printf("\033[38;2;232;37;177m");
					printf("%c", map2[i][v]);
					printf(type_color);
				}
				else if (map2[i][v] > 50 && map2[i][v] < 58) {
					printf("\033[38;2;241;252;30m");
					printf("%c", map2[i][v]);
					printf(type_color);
				}
				else if (map2[i][v] == '&') {
					printf("\033[38;2;30;171;252m");
					printf("%c", map2[i][v]);
					printf(type_color);
				}
				else {
					printf("%c", map2[i][v]);
				}
			}
		}
	}
}
int intro() {
	char welcome[100] = "\n\t\tWELCOME TO MAZE.\n\t\tGOOD LUCK ESCAPING :)\n\t\tMADE BY HOSSEIN.GH";
	for (int i = 0; 1; i++) {
		if (welcome[i] == '\0')return;
		else if (welcome[i] == '\n' || welcome[i] == '\t') {
			printf("%c", welcome[i]);
		}
		else {
			printf("%c", welcome[i]);
			_sleep(100);
		}
	}
}
int main() {
	FILE* file1;
	file1 = fopen(copyuserfile, "rb+");
	if (file1 == NULL) {
		file1=fopen(copyuserfile, "wb+");
	}
	fclose(file1);
	file1 = fopen(usersfile, "rb+");
	if (file1==NULL) {
		file1 = fopen(usersfile, "wb+");
	}
	fclose(file1);
	file1 = fopen(massagefile, "rb+");
	if ( file1== NULL) {
		file1 = fopen(massagefile, "wb+");
	}
	fclose(file1);
	file1 = fopen(copymassagefile, "rb+");
	if (file1 == NULL) {
		file1 = fopen(copymassagefile, "wb+");
	}
	fclose(file1);
	srand(time(NULL));
	printf(type_color);
	intro();
	_sleep(second * 1);
	system(clear);
	home_page();
	return 0;
}