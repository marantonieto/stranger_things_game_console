#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define ELEVEN 'E'
#define WILL 'W'
#define CHROLLO 'C'
#define EMPTY '_'
#define PORTAL '0'
#define ROCK '@'
#define TREE '#'

typedef struct{

    int pos_x;
    int pos_y;
    int life;
    int rage;
    int portal_power;
    int upside_down_power;

}Eleven;

typedef struct{

    int pos_x;
    int pos_y;

}Will;

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

    char** upside_down;
    char** empty_room;
    Will* will;
    Chrollo* chrollo;
    Eleven* eleven;

}Game;

void empty_room_generator(Game* game){
    int i, j;
    game->empty_room = (char**)malloc(10 * sizeof(char*));
    for(i = 0; i < 10; i++){
        game->empty_room[i] = (char*)malloc(10 * sizeof(char));
    }

    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            game->empty_room[i][j] = EMPTY;
        }
    }
}

void show_empty_room(Game* game){

    system("cls");

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(game->eleven->pos_x == i && game->eleven->pos_y == j){
                game->empty_room[i][j] = ELEVEN;
                printf(" %c", game->empty_room[i][j]);
            }
            else{
                printf(" %c", game->empty_room[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n\nLIFE: %d\nRAGE: %d\n", game->eleven->life, game->eleven->rage);
}

//UPSIDE FUNCTIONS
void upside_down_generator(Game* game){
    int i, j;

    game->upside_down = (char**) malloc(20 * sizeof(char*));

    for(i = 0; i < 20; i++){
        game->upside_down[i] = (char*) malloc(20 * sizeof(char));
    }

    for(i = 0; i < 20; i++){
        for(j = 0; j < 20; j++){
            game->upside_down[i][j] = EMPTY;
        }
    }
}

void show_upside_down(Game* game){

    system("cls");

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            if(game->eleven->pos_x == i && game->eleven->pos_y == j){
                game->upside_down[i][j] = ELEVEN;
                printf("\033[1;33m");
                printf(" %c", game->upside_down[i][j]);
                printf("\033[0m");
            }
            else if(game->will->pos_x == i && game->will->pos_y == j){
                game->upside_down[i][j] = WILL;
                printf("\033[1;36m");
                printf(" %c", game->upside_down[i][j]);
                printf("\033[0m");
            }
            else if(game->chrollo->pos_x == i && game->chrollo->pos_y == j){
                game->upside_down[i][j] = CHROLLO;
                printf("\033[1;31m");
                printf(" %c", game->upside_down[i][j]);
                printf("\033[0m");
            }
            else if(game->upside_down[i][j] == TREE){
                printf("\033[0;32m");
                printf(" %c", game->upside_down[i][j]);
                printf("\033[0m");
            }
            else if(game->upside_down[i][j] == ROCK){
                printf("\033[0;30m");
                printf(" %c", game->upside_down[i][j]);
                printf("\033[0m");   
            }
            else{
                printf(" %c", game->upside_down[i][j]);
            }
        }
        printf("\n");
    }
}



//CHARACTERS CREATION

Will* create_will(Will* will){

    do{
        will->pos_x = rand() % 15;
        will->pos_y = rand() % 15;

    }while(will->pos_x == 5 && will->pos_y == 5);

    return will;

}

Chrollo* create_chrollo(Chrollo* chrollo, Will* will){

    do{
        chrollo->pos_x = rand() % 15;
        chrollo->pos_y = rand() % 15;

    }while((chrollo->pos_x == will->pos_x) && (chrollo->pos_y == will->pos_y));

    return chrollo;

}


Eleven* create_eleven(Eleven* eleven){

    eleven->pos_x = 5;
    eleven->pos_y = 5;
    eleven->life = 100;
    eleven->rage = 0;
    eleven->portal_power = 0;
    eleven->upside_down_power = 0;

    return eleven;
}

//CHARACTERS MOVEMENT

int eleven_mechanic(Game* game){
    game->empty_room[game->eleven->pos_x][game->eleven->pos_y] = EMPTY;
    int button;
    int check_movement = 0;


    button = getch();

    //UP
    if(button == 'W' || button == 'w'){
        if(game->eleven->pos_x - 1 >= 0 && game->empty_room[game->eleven->pos_x - 1][game->eleven->pos_y] == EMPTY){
            game->eleven->pos_x--;
            check_movement = 1;
        }
        else if(game->eleven->pos_x - 1 >= 0 && game->empty_room[game->eleven->pos_x - 1][game->eleven->pos_y] == PORTAL){
            game->eleven->pos_x--;
            check_movement = 1;
            game->eleven->upside_down_power = 1;
        }
    }
    //DOWN
    else if(button == 'S' || button == 's'){
        if(game->eleven->pos_x + 1 < 10 && game->empty_room[game->eleven->pos_x + 1][game->eleven->pos_y] == EMPTY){
            game->eleven->pos_x++;
            check_movement = 1;
        }
        else if(game->eleven->pos_x + 1 < 10 && game->empty_room[game->eleven->pos_x + 1][game->eleven->pos_y] == PORTAL){
            game->eleven->pos_x++;
            check_movement = 1;
            game->eleven->upside_down_power = 1;
        }
    }
    //LEFT
    else if(button == 'A' || button == 'a'){
        if(game->eleven->pos_y - 1 >= 0 && game->empty_room[game->eleven->pos_x][game->eleven->pos_y - 1] == EMPTY){
            game->eleven->pos_y--;
            check_movement = 1;
        }
        else if(game->eleven->pos_y - 1 >= 0 && game->empty_room[game->eleven->pos_x][game->eleven->pos_y - 1] == PORTAL){
            game->eleven->pos_y--;
            check_movement = 1;
            game->eleven->upside_down_power = 1;
        }
    }
    //RIGHT
    else if(button == 'D' || button == 'd'){
        if(game->eleven->pos_y + 1 < 10 && game->empty_room[game->eleven->pos_x][game->eleven->pos_y + 1] == EMPTY){
            game->eleven->pos_y++;
            check_movement = 1;
        }
        else if(game->eleven->pos_y + 1 < 10 && game->empty_room[game->eleven->pos_x][game->eleven->pos_y + 1] == PORTAL){
            game->eleven->pos_y++;
            check_movement = 1;
            game->eleven->upside_down_power = 1;
        }
    }
    else if(button == 'K' || button == 'k'){
        if(game->eleven->rage < 60){
            game->eleven->life -= 20;
        }
        else if(game->eleven->rage >= 60 && game->eleven->portal_power == 0){
            int random_portal_line = rand() % 10;
            int random_portal_column = rand() % 10;

            do{
                random_portal_line = rand() % 10;
                random_portal_column = rand() % 10;
                game->empty_room[random_portal_line][random_portal_column] = PORTAL;
            }while(game->eleven->pos_x == random_portal_line && game->eleven->pos_y == random_portal_column);

            game->eleven->portal_power = 1;
        }
    }

    if(check_movement == 1){
        if(game->eleven->rage <= 96){
            game->eleven->rage += 4;
        }
    }

    if(game->eleven->life < 1){
        return 1;
    }
    else if (game->eleven->life >= 0){
        game->empty_room[game->eleven->pos_x][game->eleven->pos_y] = ELEVEN;
        return 0;
    }
}

int eleven_mechanic2(Game* game){
    game->upside_down[game->eleven->pos_x][game->eleven->pos_y] = EMPTY;
    int button;
    int check_movement = 0;


    button = getch();

    //UP
    if(button == 'W' || button == 'w'){
        if(game->eleven->pos_x - 1 >= 0 && game->upside_down[game->eleven->pos_x - 1][game->eleven->pos_y] == EMPTY){
            game->eleven->pos_x--;
            check_movement = 1;
        }
        else if(game->eleven->pos_x - 1 >= 0 && game->upside_down[game->eleven->pos_x - 1][game->eleven->pos_y] == PORTAL){
            game->eleven->pos_x--;
            check_movement = 1;
            game->eleven->upside_down_power = 1;
        }
    }
    //DOWN
    else if(button == 'S' || button == 's'){
        if(game->eleven->pos_x + 1 < 20 && game->upside_down[game->eleven->pos_x + 1][game->eleven->pos_y] == EMPTY){
            game->eleven->pos_x++;
            check_movement = 1;
        }
    }
    //LEFT
    else if(button == 'A' || button == 'a'){
        if(game->eleven->pos_y - 1 >= 0 && game->upside_down[game->eleven->pos_x][game->eleven->pos_y - 1] == EMPTY){
            game->eleven->pos_y--;
            check_movement = 1;
        }
    }
    //RIGHT
    else if(button == 'D' || button == 'd'){
        if(game->eleven->pos_y + 1 < 20 && game->upside_down[game->eleven->pos_x][game->eleven->pos_y + 1] == EMPTY){
            game->eleven->pos_y++;
            check_movement = 1;
        }
    }
    else if(button == 'K' || button == 'k'){
        if(game->eleven->rage < 60){
            game->eleven->life -= 20;
        }
        else if(game->eleven->rage >= 60 && game->eleven->portal_power == 0){
            int random_portal_line = rand() % 20;
            int random_portal_column = rand() % 20;

            do{
                random_portal_line = rand() % 20;
                random_portal_column = rand() % 20;
                game->empty_room[random_portal_line][random_portal_column] = PORTAL;
            }while(game->eleven->pos_x == random_portal_line && game->eleven->pos_y == random_portal_column);

            game->eleven->portal_power = 1;
        }
    }

    if(check_movement == 1){
        if(game->eleven->rage <= 96){
            game->eleven->rage += 4;
        }
    }

    if(game->eleven->life < 1){
        return 1;
    }
    else if (game->eleven->life > 0){
        game->upside_down[game->eleven->pos_x][game->eleven->pos_y] = ELEVEN;
        return 0;
    }

    
}


/*
void will_movement(Game* game){
    game->map[game->will->pos_x][game->will->pos_y] = EMPTY;

        int dash_run = rand() % 11;
        int next_movement = rand() % 4;

        if(dash_run == 0){
            //UP DASH
            if(next_movement == 0){
                if(game->will->pos_x - 2 >= 0 && game->map[game->will->pos_x - 2][game->will->pos_y] == EMPTY){
                    game->will->pos_x = game->will->pos_x - 2;
                }
            }
            //DOWN DASH
            else if(next_movement == 1){
                if(game->will->pos_x + 2 < 15 && game->map[game->will->pos_x + 2][game->will->pos_y] == EMPTY){
                    game->will->pos_x = game->will->pos_x + 2;
                }
            }
            //LEFT DASH
            else if(next_movement == 2){
                if(game->will->pos_y - 2 >= 0 && game->map[game->will->pos_x][game->will->pos_y - 2] == EMPTY){
                    game->will->pos_y = game->will->pos_y - 2;
                }
            }
            //RIGHT DASH
            else if(next_movement == 3){
                if(game->will->pos_y + 2 < 15 && game->map[game->will->pos_x][game->will->pos_y + 2] == EMPTY){
                    game->will->pos_y = game->will->pos_y + 2;
                }
            }
        }
        else{
            //NORMAL UP MOVEMENT
            if(next_movement == 0){
                if(game->will->pos_x - 1 >= 0 && game->map[game->will->pos_x - 1][game->will->pos_y] == EMPTY){
                    game->will->pos_x--;
                }
            }
            //NORMAL DOWN MOVEMENT
            else if(next_movement == 1){
                if(game->will->pos_x + 1 < 15 && game->map[game->will->pos_x + 1][game->will->pos_y] == EMPTY){
                    game->will->pos_x++;
                }
            }
            //NORMAL LEF MOVEMENT
            else if(next_movement == 2){
                if(game->will->pos_y - 1 >= 0 && game->map[game->will->pos_x][game->will->pos_y - 1] == EMPTY){
                    game->will->pos_y--;
                }
            }
            //NORMAL RIGHT MOVEMENT
            else if(next_movement == 3){
                if(game->will->pos_y + 1 < 15 && game->map[game->will->pos_x][game->will->pos_y + 1] == EMPTY){
                    game->will->pos_y++;
                }
            }
        }

    game->map[game->will->pos_x][game->will->pos_y] = WILL;
}

void chrollo_movement(Game* game){
    game->map[game->chrollo->pos_x][game->chrollo->pos_y] = EMPTY;
    int random_precision = 1 + rand() % 2;
    int random_move = rand() % 4;

    //IF R_P == 1 OR 2 CHROLLO WILL MOVE PERFECTLY IN PLAYER DIRECTION ... CHROLLO HAVE 66.6% OF PRECISION IN HIS MOVEMENT
    //IF CHROLLO MISSES HIS MOVEMENT, HIS MOVE WILL BE RANDOMIC! THIS IS APPLIED IN ELSE STATEMENT


    if(random_precision == 1){
        if(game->chrollo->pos_x < game->eleven->pos_x && game->eleven->pos_y < game->eleven->pos_y && game->map[game->chrollo->pos_x + 1][game->chrollo->pos_y + 1] == EMPTY){
            game->chrollo->pos_x++;
            game->chrollo->pos_y++;
        }
        else if(game->chrollo->pos_x < game->eleven->pos_x && game->chrollo->pos_y > game->eleven->pos_y && game->map[game->chrollo->pos_x + 1][game->chrollo->pos_y - 1] == EMPTY){
            game->chrollo->pos_x++;
            game->chrollo->pos_y--;
        }
        else if(game->chrollo->pos_x > game->eleven->pos_x && game->chrollo->pos_y > game->eleven->pos_y && game->map[game->chrollo->pos_x - 1][game->chrollo->pos_y - 1] == EMPTY){
            game->chrollo->pos_x--;
            game->chrollo->pos_y--;
        }
        else if(game->chrollo->pos_x > game->eleven->pos_x && game->chrollo->pos_y <  game->eleven->pos_y && game->map[game->chrollo->pos_x - 1][game->chrollo->pos_y + 1] == EMPTY){
            game->chrollo->pos_x--;
            game->chrollo->pos_y++;
        }
        else if(game->chrollo->pos_x == game->eleven->pos_x && game->chrollo->pos_y > game->eleven->pos_y && game->map[game->chrollo->pos_x][game->chrollo->pos_y - 1] == EMPTY){
            game->chrollo->pos_y--;
        }
        else if(game->chrollo->pos_x == game->eleven->pos_x && game->chrollo->pos_y < game->eleven->pos_y && game->map[game->chrollo->pos_x][game->chrollo->pos_y + 1] == EMPTY){
            game->chrollo->pos_y++;
        }
        else if(game->chrollo->pos_x < game->eleven->pos_x && game->chrollo->pos_y == game->chrollo->pos_y && game->map[game->chrollo->pos_x + 1][game->chrollo->pos_y] == EMPTY){
            game->chrollo->pos_x++;
        }
        else if(game->chrollo->pos_x > game->eleven->pos_x && game->chrollo->pos_y == game->chrollo->pos_y && game->map[game->chrollo->pos_x - 1][game->chrollo->pos_y] == EMPTY){
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
*/

Game* starting_game(Game* game, Eleven* eleven, Will* will, Chrollo* chrollo){
    game->eleven = eleven;
    game->will = will;
    game->chrollo = chrollo;
}


int main(){

    srand(time(NULL));

    //important variables
    char** upside_down;
    char** empty_room;
    Eleven *eleven;
    Will *will;
    Chrollo *chrollo;
    Game *game;

    //GAME VARIABLES
    int EOG = 1;
    int isElevenDead = 0;
    int ChangeMap = 0;

    will = (Will*) malloc(1 * sizeof(Will));
    will = create_will(will);

    eleven = (Eleven*) malloc(1 * sizeof(Eleven));
    eleven = create_eleven(eleven);

    chrollo = (Chrollo*) malloc(1 * sizeof(Chrollo));
    chrollo = create_chrollo(chrollo, will);
    

    game = (Game*) malloc(1 * sizeof(Game));
    game = starting_game(game, eleven, will, chrollo);

    //upside_down_generator(game);
    //show_upside_down(game);
    empty_room_generator(game);
    show_empty_room(game);
    upside_down_generator(game);
    
    //map_generator(game);
    //show_map(game);

    while(EOG == 1 && isElevenDead == 0 && game->eleven->upside_down_power == 0){
        //will_movement(game);
        isElevenDead = eleven_mechanic(game);
        //chrollo_movement(game);
        //show_map(game);
        //show_upside_down(game);
        show_empty_room(game);
    }

    show_upside_down(game);


    if(isElevenDead == 0){
        while(isElevenDead == 0){
            isElevenDead = eleven_mechanic2(game);
            show_upside_down(game);
        }
    }


    return 0;
}
