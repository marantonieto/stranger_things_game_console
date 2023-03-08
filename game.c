#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define HISOKA 'H'
#define GON 'G'
#define CHROLLO 'C'
#define EMPTY '_'
#define ROCK '@'
#define TREE '#'

typedef struct{

    int pos_x;
    int pos_y;

}Hisoka;

typedef struct{

    int pos_x;
    int pos_y;

}Gon;

typedef struct{

    int pos_x;
    int pos_y;
    
}Chrollo;

typedef struct{

    int pos_x;
    int pos_y;

}Tree;

typedef struct{

    int pos_x;
    int pos_y;

}Rock;

typedef struct{

    char** map;
    Gon* gon;
    Chrollo* chrollo;
    Hisoka* hisoka;

}Game;



//MAP FUNCTIONS
void map_generator(Game* game){
    int i, j;

    game->map = (char**) malloc(15 * sizeof(char*));

    for(i = 0; i < 15; i++){
        game->map[i] = (char*) malloc(15 * sizeof(char));
    }

    for(i = 0; i < 15; i++){
        for(j = 0; j < 15; j++){
            game->map[i][j] = EMPTY;
        }
    }

    for(int j = 0; j < 15; j++){
        game->map[rand()%15][rand()%15] = TREE; 
        game->map[rand()%15][rand()%15] = ROCK;
    }
}

void show_map(Game* game){

    system("cls");

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            if(game->hisoka->pos_x == i && game->hisoka->pos_y == j){
                game->map[i][j] = HISOKA;
                printf("\033[1;33m");
                printf(" %c", game->map[i][j]);
                printf("\033[0m");
            }
            else if(game->gon->pos_x == i && game->gon->pos_y == j){
                game->map[i][j] = GON;
                printf("\033[1;36m");
                printf(" %c", game->map[i][j]);
                printf("\033[0m");
            }
            else if(game->chrollo->pos_x == i && game->chrollo->pos_y == j){
                game->map[i][j] = CHROLLO;
                printf("\033[1;31m");
                printf(" %c", game->map[i][j]);
                printf("\033[0m");
            }
            else if(game->map[i][j] == TREE){
                printf("\033[0;32m");
                printf(" %c", game->map[i][j]);
                printf("\033[0m");
            }
            else if(game->map[i][j] == ROCK){
                printf("\033[0;30m");
                printf(" %c", game->map[i][j]);
                printf("\033[0m");   
            }
            else{
                printf(" %c", game->map[i][j]);
            }
        }
        printf("\n");
    }
}



//CHARACTERS CREATION

Gon* create_gon(Gon* gon){

    do{
        gon->pos_x = rand() % 15;
        gon->pos_y = rand() % 15;

    }while(gon->pos_x == 5 && gon->pos_y == 5);

    return gon;

}

Chrollo* create_chrollo(Chrollo* chrollo, Gon* gon){

    do{
        chrollo->pos_x = rand() % 15;
        chrollo->pos_y = rand() % 15;

    }while((chrollo->pos_x == gon->pos_x) && (chrollo->pos_y == gon->pos_y));

    return chrollo;

}


Hisoka* create_hisoka(Hisoka* hisoka){

    hisoka->pos_x = 5;
    hisoka->pos_y = 5;

    return hisoka;
}

//CHARACTERS MOVEMENT

void hisoka_movement(Game* game){
    game->map[game->hisoka->pos_x][game->hisoka->pos_y] = EMPTY;
    int button;

    button = getch();

    //UP
    if(button == 'W' || button == 'w'){
        if(game->hisoka->pos_x - 1 >= 0 && game->map[game->hisoka->pos_x - 1][game->hisoka->pos_y] == EMPTY){
            game->hisoka->pos_x--;
        }
    }
    //DOWN
    else if(button == 'S' || button == 's'){
        if(game->hisoka->pos_x + 1 < 15 && game->map[game->hisoka->pos_x + 1][game->hisoka->pos_y] == EMPTY){
            game->hisoka->pos_x++;
        }
    }
    //LEFT
    else if(button == 'A' || button == 'a'){
        if(game->hisoka->pos_y - 1 >= 0 && game->map[game->hisoka->pos_x][game->hisoka->pos_y - 1] == EMPTY){
            game->hisoka->pos_y--;
        }
    }
    //RIGHT
    else if(button == 'D' || button == 'd'){
        if(game->hisoka->pos_y + 1 < 15 && game->map[game->hisoka->pos_x][game->hisoka->pos_y + 1] == EMPTY){
            game->hisoka->pos_y++;
        }
    }

    game->map[game->hisoka->pos_x][game->hisoka->pos_y] = HISOKA;
    
}

void gon_movement(Game* game){
    game->map[game->gon->pos_x][game->gon->pos_y] = EMPTY;

        int dash_run = rand() % 11;
        int next_movement = rand() % 4;

        if(dash_run == 0){
            //UP DASH
            if(next_movement == 0){
                if(game->gon->pos_x - 2 >= 0 && game->map[game->gon->pos_x - 2][game->gon->pos_y] == EMPTY){
                    game->gon->pos_x = game->gon->pos_x - 2;
                }
            }
            //DOWN DASH
            else if(next_movement == 1){
                if(game->gon->pos_x + 2 < 15 && game->map[game->gon->pos_x + 2][game->gon->pos_y] == EMPTY){
                    game->gon->pos_x = game->gon->pos_x + 2;
                }
            }
            //LEFT DASH
            else if(next_movement == 2){
                if(game->gon->pos_y - 2 >= 0 && game->map[game->gon->pos_x][game->gon->pos_y - 2] == EMPTY){
                    game->gon->pos_y = game->gon->pos_y - 2;
                }
            }
            //RIGHT DASH
            else if(next_movement == 3){
                if(game->gon->pos_y + 2 < 15 && game->map[game->gon->pos_x][game->gon->pos_y + 2] == EMPTY){
                    game->gon->pos_y = game->gon->pos_y + 2;
                }
            }
        }
        else{
            //NORMAL UP MOVEMENT
            if(next_movement == 0){
                if(game->gon->pos_x - 1 >= 0 && game->map[game->gon->pos_x - 1][game->gon->pos_y] == EMPTY){
                    game->gon->pos_x--;
                }
            }
            //NORMAL DOWN MOVEMENT
            else if(next_movement == 1){
                if(game->gon->pos_x + 1 < 15 && game->map[game->gon->pos_x + 1][game->gon->pos_y] == EMPTY){
                    game->gon->pos_x++;
                }
            }
            //NORMAL LEF MOVEMENT
            else if(next_movement == 2){
                if(game->gon->pos_y - 1 >= 0 && game->map[game->gon->pos_x][game->gon->pos_y - 1] == EMPTY){
                    game->gon->pos_y--;
                }
            }
            //NORMAL RIGHT MOVEMENT
            else if(next_movement == 3){
                if(game->gon->pos_y + 1 < 15 && game->map[game->gon->pos_x][game->gon->pos_y + 1] == EMPTY){
                    game->gon->pos_y++;
                }
            }
        }

    game->map[game->gon->pos_x][game->gon->pos_y] = GON;
}

void chrollo_movement(Game* game){
    game->map[game->chrollo->pos_x][game->chrollo->pos_y] = EMPTY;
    int random_precision = 1 + rand() % 2;
    int random_move = rand() % 4;

    //IF R_P == 1 OR 2 CHROLLO WILL MOVE PERFECTLY IN PLAYER DIRECTION ... CHROLLO HAVE 66.6% OF PRECISION IN HIS MOVEMENT
    //IF CHROLLO MISSES HIS MOVEMENT, HIS MOVE WILL BE RANDOMIC! THIS IS APPLIED IN ELSE STATEMENT


    if(random_precision == 1){
        if(game->chrollo->pos_x < game->hisoka->pos_x && game->chrollo->pos_y < game->hisoka->pos_y && game->map[game->chrollo->pos_x + 1][game->chrollo->pos_y + 1] == EMPTY){
            game->chrollo->pos_x++;
            game->chrollo->pos_y++;
        }
        else if(game->chrollo->pos_x < game->hisoka->pos_x && game->chrollo->pos_y > game->hisoka->pos_y && game->map[game->chrollo->pos_x + 1][game->chrollo->pos_y - 1] == EMPTY){
            game->chrollo->pos_x++;
            game->chrollo->pos_y--;
        }
        else if(game->chrollo->pos_x > game->hisoka->pos_x && game->chrollo->pos_y > game->hisoka->pos_y && game->map[game->chrollo->pos_x - 1][game->chrollo->pos_y - 1] == EMPTY){
            game->chrollo->pos_x--;
            game->chrollo->pos_y--;
        }
        else if(game->chrollo->pos_x > game->hisoka->pos_x && game->chrollo->pos_y <  game->hisoka->pos_y && game->map[game->chrollo->pos_x - 1][game->chrollo->pos_y + 1] == EMPTY){
            game->chrollo->pos_x--;
            game->chrollo->pos_y++;
        }
        else if(game->chrollo->pos_x == game->hisoka->pos_x && game->chrollo->pos_y > game->hisoka->pos_y && game->map[game->chrollo->pos_x][game->chrollo->pos_y - 1] == EMPTY){
            game->chrollo->pos_y--;
        }
        else if(game->chrollo->pos_x == game->hisoka->pos_x && game->chrollo->pos_y < game->hisoka->pos_y && game->map[game->chrollo->pos_x][game->chrollo->pos_y + 1] == EMPTY){
            game->chrollo->pos_y++;
        }
        else if(game->chrollo->pos_x < game->hisoka->pos_x && game->chrollo->pos_y == game->chrollo->pos_y && game->map[game->chrollo->pos_x + 1][game->chrollo->pos_y] == EMPTY){
            game->chrollo->pos_x++;
        }
        else if(game->chrollo->pos_x > game->hisoka->pos_x && game->chrollo->pos_y == game->chrollo->pos_y && game->map[game->chrollo->pos_x - 1][game->chrollo->pos_y] == EMPTY){
            game->chrollo->pos_x--;
        }
    }
    else{
        //LEFT MOVE
        if(random_move == 1){
            if(game->chrollo->pos_y - 1 >= 0 && game->map[game->chrollo->pos_x][game->chrollo->pos_y - 1] == EMPTY){
                game->chrollo->pos_y--;
            }
            else if(game->chrollo->pos_y + 1 < 15 && game->map[game->chrollo->pos_x][game->chrollo->pos_y + 1] == EMPTY){
                game->chrollo->pos_y++;
            }
            else if(game->chrollo->pos_x - 1 >= 0 && game->map[game->chrollo->pos_x - 1][game->chrollo->pos_y] == EMPTY){
                game->chrollo->pos_x--;
            }
            else if(game->chrollo->pos_x + 1 < 15 && game->map[game->chrollo->pos_x + 1][game->chrollo->pos_y] == EMPTY){
                game->chrollo->pos_x++;
            }
        }
    }
    game->map[game->chrollo->pos_x][game->chrollo->pos_y] = CHROLLO;

}

Game* starting_game(Game* game, Hisoka* hisoka, Gon* gon, Chrollo* chrollo){
    game->hisoka = hisoka;
    game->gon = gon;
    game->chrollo = chrollo;
}


int main(){

    srand(time(NULL));

    //important variables
    char** map;
    Hisoka *hisoka;
    Gon *gon;
    Chrollo *chrollo;
    Game *game;
    int EOG = 1;

    gon = (Gon*) malloc(1 * sizeof(Gon));
    gon = create_gon(gon);

    hisoka = (Hisoka*) malloc(1 * sizeof(Hisoka));
    hisoka = create_hisoka(hisoka);

    chrollo = (Chrollo*) malloc(1 * sizeof(Chrollo));
    chrollo = create_chrollo(chrollo, gon);
    

    game = (Game*) malloc(1 * sizeof(Game));
    game = starting_game(game, hisoka, gon, chrollo);

    map_generator(game);
    show_map(game);

    while(EOG == 1){
        gon_movement(game);
        hisoka_movement(game);
        chrollo_movement(game);
        show_map(game);
    }


    return 0;
}
