#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define ELEVEN 'E'
#define WILL 'W'
#define EMPTY '_'
#define PORTAL '0'
#define CAR '@'
#define TREE '#'
#define ABANDONED_HOUSES '!'
#define PANCAKE '*'
#define DEMODOGS 'D'

typedef struct{

    int pos_x;
    int pos_y;
    int life;
    int rage;
    int portal_power;
    int clairvoyance_power;
    int clairvoyance_power_qtd;
    int upside_down_power;
    int take_will;

}Eleven;

typedef struct{

    int pos_x;
    int pos_y;
    int will_saved;

}Will;

typedef struct{

    char** upside_down;
    char** empty_room;
    Will* will;
    Eleven* eleven;

}Game;

void controls_box(){

    int press_key;
    printf("\033[1;37m");
    printf("\n\nMOVIMENTACAO: W A S D\n\n");
    printf("\033[0m");

    printf("\033[1;33m");
    printf("PODER DE ABRIR O PORTAL: K\n");
    printf("PODER DE CLARIVIDENCIA (ENXERGAR INIMIGOS POR UMA RODADA): J\n");
    printf("\033[0m");
    
    printf("\033[1;32m");
    printf("\nEleven perde 20 de vida e 10 de furia a cada tentativa falha de abrir o portal!\n");
    printf("Eleven perdera 15 de vida e 10 de furia a cada tentativa falha de utilizar a clarividencia!\n");
    printf("\n\nSoh eh possivel abrir o portal com ao menos 60 de furia, e soh eh possivel utilizar o poder da clarividencia com ao menos 30 de furia!\n");
    printf("\033[0m");

    printf("\033[1;35m");
    printf("\nRESGATE O WILL\n");
    printf("\033[0m");

    printf("\033[1;37m");
    printf("\nPressione qualquer tecla para iniciar o jogo\n");
    printf("\033[0m");
    press_key = getch();
}

void add_new_demodogs(Game* game){
    int new_demodog_posx = rand() % 20;
    int new_demodog_posy = rand() % 20;
    int delta_x;
    int delta_y;
    if(game->will->pos_x >= game->eleven->pos_x){
        delta_x = game->will->pos_x - game->eleven->pos_x;
    }
    else if(game->will->pos_x < game->eleven->pos_x){
        delta_x = game->eleven->pos_x - game->will->pos_x;
    }

    if(game->will->pos_y >= game->eleven->pos_y){
        delta_y = game->will->pos_y - game->eleven->pos_y;
    }
    else if(game->will->pos_y < game->eleven->pos_y){
        delta_y = game->eleven->pos_y - game->will->pos_y;
    }

    if(game->eleven->take_will == 0){
        if((delta_x <= 5 && delta_y <= 5)){
            for(int i = 0; i < 6;i++){
                do{
                    new_demodog_posx = rand() % 20;
                    new_demodog_posy = rand() % 20;
                }while(game->upside_down[new_demodog_posx][new_demodog_posy] != EMPTY);
                game->upside_down[new_demodog_posx][new_demodog_posy] = DEMODOGS;
            }
	    }
    }
}

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
                printf("\033[1;33m");
                printf(" %c", game->empty_room[i][j]);
                printf("\033[0m");
            }
            else if(game->empty_room[i][j] == PORTAL){
                printf("\033[1;31m");
                printf(" %c", game->empty_room[i][j]);
                printf("\033[0m");
            }
            else{
                printf(" %c", game->empty_room[i][j]);
            }
        }
        printf("\n");
    }
    printf("\033[1;31m");
    printf("\n\nLIFE: %d\nRAGE: %d\n\n", game->eleven->life, game->eleven->rage);
    printf("\033[0m");

    if(game->eleven->portal_power == 0){
        printf("\033[1;32m");
        printf("WILL ESTA NO MUNDO INVERTIDO, ABRA O PORTAL (K) PARA TENTAR ENCONTRA-LO\n");
        printf("\033[0m");
    }
    else{
        printf("\033[1;32m");
        printf("ENTRE NO PORTAL PARA TENTAR SALVAR O WILL!");
        printf("\033[0m");
    }
}

//UPSIDE FUNCTIONS
void upside_down_generator(Game* game){
    int i, j, tree_posx, tree_posy, car_posx, car_posy, abandoned_houses_posx, abandoned_houses_posy, pancake_posx, pancake_posy, demodogs_posx, demodogs_posy;

    game->upside_down = (char**) malloc(20 * sizeof(char*));

    for(i = 0; i < 20; i++){
        game->upside_down[i] = (char*) malloc(20 * sizeof(char));
    }

    for(i = 0; i < 20; i++){
        for(j = 0; j < 20; j++){
            game->upside_down[i][j] = EMPTY;
        }
    }

    for(int k = 0; k < 20; k++){
        tree_posx = rand() % 20;
        tree_posy = rand() % 20;
        if(game->upside_down[tree_posx][tree_posy] == EMPTY){
            game->upside_down[tree_posx][tree_posy] = TREE;
        }
        else{
            do{
                tree_posx = rand() % 20;
                tree_posy = rand() % 20;
            }while(game->upside_down[tree_posx][tree_posy] != EMPTY);
            game->upside_down[tree_posx][tree_posy] = TREE;
        }
    }

    for(int k = 0; k < 10; k++){
        car_posx = rand() % 20;
        car_posy = rand() % 20;
        if(game->upside_down[car_posx][car_posy] == EMPTY){
            game->upside_down[car_posx][car_posy] = CAR;
        }
        else{
            do{
                car_posx = rand() % 20;
                car_posy = rand() % 20;
            }while(game->upside_down[car_posx][car_posy] != EMPTY);

            game->upside_down[car_posx][car_posy] = TREE;
        }
    }

    for(int k = 0 ; k < 10; k++){
        abandoned_houses_posx = rand() % 20;
        abandoned_houses_posy = rand() % 20;
        if(game->upside_down[abandoned_houses_posx][abandoned_houses_posy] == EMPTY){
            game->upside_down[abandoned_houses_posx][abandoned_houses_posy] = ABANDONED_HOUSES;
        }
        else{
            do{
                abandoned_houses_posx = rand() % 20;
                abandoned_houses_posy = rand () % 20;
            }while(game->upside_down[abandoned_houses_posx][abandoned_houses_posy] != EMPTY);

            game->upside_down[abandoned_houses_posx][abandoned_houses_posy] = ABANDONED_HOUSES;
        }
    }

    for(int k = 0; k < 10; k++){
        pancake_posx = rand() % 20;
        pancake_posy = rand() % 20;
        if(game->upside_down[pancake_posx][pancake_posy] == EMPTY){
            game->upside_down[pancake_posx][pancake_posy] = PANCAKE;
        }
        else{
            do{
                pancake_posx = rand() % 20;
                pancake_posy = rand() % 20;
            }while(game->upside_down[pancake_posx][pancake_posy] != EMPTY);

            game->upside_down[pancake_posx][pancake_posy] = PANCAKE;
        }
    }

    for(int k = 0; k < 15; k++){
        demodogs_posx = rand() % 20;
        demodogs_posy = rand() % 20;
        if(game->upside_down[demodogs_posx][demodogs_posy] == EMPTY){
            game->upside_down[demodogs_posx][demodogs_posy] = DEMODOGS;
        }
        else{
            do{
                demodogs_posx = rand() % 20;
                demodogs_posy = rand() % 20;
            }while(game->upside_down[demodogs_posx][demodogs_posy] != EMPTY);

            game->upside_down[demodogs_posx][demodogs_posy] = DEMODOGS;
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
            else if((game->will->pos_x == i && game->will->pos_y == j)){
                game->upside_down[i][j] = WILL;
                if(game->eleven->take_will == 0){
                printf("\033[1;36m");
                printf(" %c", game->upside_down[i][j]);
                printf("\033[0m");
                }
                else{
                    printf(" _");
                }
            }
            else if(game->upside_down[i][j] == PANCAKE){
                printf("\033[1;31m");
                printf(" %c", game->upside_down[i][j]);
                printf("\033[0m");
            }
            else if(game->upside_down[i][j] == TREE){
                printf("\033[0;32m");
                printf(" %c", game->upside_down[i][j]);
                printf("\033[0m");
            }
            else if(game->upside_down[i][j] == CAR){
                printf("\033[0;30m");
                printf(" %c", game->upside_down[i][j]);
                printf("\033[0m");   
            }
            else if(game->upside_down[i][j] == ABANDONED_HOUSES){
                printf("\033[0;35m");
                printf(" %c", game->upside_down[i][j]);
                printf("\033[0m");   
            }
            else if(game->upside_down[i][j] == PORTAL){
                printf("\033[1;34m");
                printf(" %c", game->upside_down[i][j]);
                printf("\033[0m");
            }
            else if(game->upside_down[i][j] == DEMODOGS){
                //printf(" X");
                if(game->eleven->clairvoyance_power == 1){
                    printf(" X");
                }
                else{
                    printf(" _");
                }
            }
            else{
                printf(" %c", game->upside_down[i][j]);
            }
        }
        printf("\n");
    }
    printf("\033[1;32m");
    printf("\n\nLIFE: %d\nRAGE: %d\n\n", game->eleven->life, game->eleven->rage);
    printf("\033[0m");

    if(game->eleven->take_will == 0 && game->eleven->portal_power == 0){
        printf("\033[1;31m");
        printf("ENCONTRE O WILL E ABRA O PORTAL (K) PARA VOLTAR AO MUNDO REAL!\n");
        printf("DEMODOGS SURGIRAO QUANDO VOCE SE APROXIMAR DE WILL, CUIDADO!");
        printf("\033[0m");
    }
    else if(game->eleven->take_will == 0 && game->eleven->portal_power == 1){
        printf("\033[1;31m");
        printf("ENCONTRE O WILL E O LEVE PARA O PORTAL!\n");
        printf("DEMODOGS SURGIRAO QUANDO VOCE SE APROXIMAR DE WILL, CUIDADO!");
        printf("\033[0m");
    }
    else if(game->eleven->take_will == 1 && game->eleven->portal_power == 0){
        printf("\033[1;31m");
        printf("VOCE ESTA COM O WILL, ABRA O PORTAL (K) E O LEVE PARA O MUNDO REAL!");
        printf("\033[0m");
    }
    else{
        printf("\033[1;31m");
        printf("LEVE O WILL PARA O PORTAL!");
        printf("\033[0m");
    }

    printf("\033[0;33m");
    printf("\n\nQUANTIDADE DE CLARIVIDENCIAS (J) DISPONIVEIS: %d\n", game->eleven->clairvoyance_power_qtd);
    printf("\033[0m");

}


//CHARACTERS CREATION

Will* create_will(Will* will, Eleven* eleven){

    do{
        will->pos_x = rand() % 20;
        will->pos_y = rand() % 20;

    }while(will->pos_x == eleven->pos_x && will->pos_y == eleven->pos_y);

    return will;

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
            if(game->eleven->rage - 10 <= 0){
                game->eleven->rage = 0;
            }
            else if(game->eleven->rage - 10 > 0){
                game->eleven->rage -= 10;
            }
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

int eleven_mechanic_ud(Game* game){
    game->upside_down[game->eleven->pos_x][game->eleven->pos_y] = EMPTY;
    game->eleven->clairvoyance_power = 0;
    int button;
    int check_movement = 0;


    button = getch();

    //UP
    if(button == 'W' || button == 'w'){
        if(game->eleven->pos_x - 1 >= 0 && game->upside_down[game->eleven->pos_x - 1][game->eleven->pos_y] == EMPTY){
            game->eleven->pos_x--;
            check_movement = 1;
        }
        else if(game->eleven->pos_x - 1 >= 0 && game->upside_down[game->eleven->pos_x - 1][game->eleven->pos_y] == PANCAKE){
            game->eleven->pos_x--;
            check_movement = 1;
            if(game->eleven->life < 100){
                game->eleven->life += 5;
            }
        }
        else if((game->eleven->pos_x - 1 >= 0) && (game->upside_down[game->eleven->pos_x - 1][game->eleven->pos_y] == WILL)){
            game->eleven->pos_x--;
            check_movement = 1;
            game->eleven->take_will = 1;
        }
        else if((game->eleven->pos_x - 1 >= 0) && (game->upside_down[game->eleven->pos_x - 1][game->eleven->pos_y] == PORTAL) && (game->eleven->take_will == 1)){
            game->eleven->pos_x--;
            game->will->will_saved = 1;
        }
        else if((game->eleven->pos_x - 1 >= 0) && (game->upside_down[game->eleven->pos_x - 1][game->eleven->pos_y] == DEMODOGS)){
            game->eleven->pos_x--;
            check_movement = 1;
            game->eleven->life-=10;
        }
    }
    //DOWN
    else if(button == 'S' || button == 's'){
        if(game->eleven->pos_x + 1 < 20 && game->upside_down[game->eleven->pos_x + 1][game->eleven->pos_y] == EMPTY){
            game->eleven->pos_x++;
            check_movement = 1;
        }
        else if(game->eleven->pos_x + 1 < 20 && game->upside_down[game->eleven->pos_x + 1][game->eleven->pos_y] == PANCAKE){
            game->eleven->pos_x++;
            check_movement = 1;
            if(game->eleven->life < 100){
                game->eleven->life += 5;
            }
        }
        else if(game->eleven->pos_x + 1 < 20 && game->upside_down[game->eleven->pos_x + 1][game->eleven->pos_y] == WILL){
            game->eleven->pos_x++;
            check_movement = 1;
            game->eleven->take_will = 1;
        }
        else if((game->eleven->pos_x + 1 < 20) && (game->upside_down[game->eleven->pos_x + 1][game->eleven->pos_y] == PORTAL) && (game->eleven->take_will == 1)){
            game->eleven->pos_x++;
            game->will->will_saved = 1;
        }
        else if((game->eleven->pos_x + 1 < 20) && (game->upside_down[game->eleven->pos_x + 1][game->eleven->pos_y] == DEMODOGS)){
            game->eleven->pos_x++;
            check_movement = 1;
            game->eleven->life-=10;
        }
    }
    //LEFT
    else if(button == 'A' || button == 'a'){
        if(game->eleven->pos_y - 1 >= 0 && game->upside_down[game->eleven->pos_x][game->eleven->pos_y - 1] == EMPTY){
            game->eleven->pos_y--;
            check_movement = 1;
        }
        else if(game->eleven->pos_y - 1 >= 0 && game->upside_down[game->eleven->pos_x][game->eleven->pos_y - 1] == PANCAKE){
            game->eleven->pos_y--;
            check_movement = 1;
            if(game->eleven->life < 100){
                game->eleven->life += 5;
            }
        }
        else if(game->eleven->pos_y - 1 >= 0 && game->upside_down[game->eleven->pos_x][game->eleven->pos_y - 1] == WILL){
            game->eleven->pos_y--;
            check_movement = 1;
            game->eleven->take_will = 1;
        }
        else if((game->eleven->pos_y - 1 >= 0) && (game->upside_down[game->eleven->pos_x][game->eleven->pos_y - 1] == PORTAL) && (game->eleven->take_will == 1)){
            game->eleven->pos_y--;
            game->will->will_saved = 1;
        }
        else if((game->eleven->pos_y - 1 >= 0) && (game->upside_down[game->eleven->pos_x][game->eleven->pos_y - 1] == DEMODOGS)){
            game->eleven->pos_y--;
            check_movement = 1;
            game->eleven->life-=10;
        }
        
    }
    //RIGHT
    else if(button == 'D' || button == 'd'){
        if(game->eleven->pos_y + 1 < 20 && game->upside_down[game->eleven->pos_x][game->eleven->pos_y + 1] == EMPTY){
            game->eleven->pos_y++;
            check_movement = 1;
        }
        else if(game->eleven->pos_y + 1 < 20 && game->upside_down[game->eleven->pos_x][game->eleven->pos_y + 1] == PANCAKE){
            game->eleven->pos_y++;
            check_movement = 1;
            if(game->eleven->life < 100){
                game->eleven->life += 5;
            }
        }
        else if(game->eleven->pos_y + 1 < 20 && game->upside_down[game->eleven->pos_x][game->eleven->pos_y + 1] == WILL){
            game->eleven->pos_y++;
            check_movement = 1;
            game->eleven->take_will = 1;
        }
        else if((game->eleven->pos_y + 1 < 20) && (game->upside_down[game->eleven->pos_x][game->eleven->pos_y + 1] == PORTAL) && (game->eleven->take_will == 1)){
            game->eleven->pos_y++;
            game->will->will_saved = 1;
        }
        else if((game->eleven->pos_y + 1 < 20) && (game->upside_down[game->eleven->pos_x][game->eleven->pos_y + 1] == DEMODOGS)){
            game->eleven->pos_y++;
            check_movement = 1;
            game->eleven->life-=10;
        }
    }
    else if(button == 'K' || button == 'k'){
        if(game->eleven->rage < 60){
            game->eleven->life -= 20;
            if(game->eleven->rage - 10 <= 0){
                game->eleven->rage = 0;
            }
            else if(game->eleven->rage - 10 > 0){
                game->eleven->rage -= 10;
            }
        }
        else if(game->eleven->rage >= 60 && game->eleven->portal_power == 0){
            int random_portal_line = rand() % 20;
            int random_portal_column = rand() % 20;

            do{
                random_portal_line = rand() % 20;
                random_portal_column = rand() % 20;
            }while(game->upside_down[random_portal_line][random_portal_column] != EMPTY);
            game->upside_down[random_portal_line][random_portal_column] = PORTAL;
            game->eleven->portal_power = 1;
        }
    }
    else if(button == 'J' || button == 'j'){
        if(game->eleven->rage >= 40 && game->eleven->clairvoyance_power_qtd > 0){
            game->eleven->clairvoyance_power = 1;
            game->eleven->clairvoyance_power_qtd--;
        }
        else if(game->eleven->rage < 40){
            game->eleven->life -= 15;
            if(game->eleven->rage - 10 <= 0){
                game->eleven->rage = 0;
            }
            else if(game->eleven->rage - 10 > 0){
                game->eleven->rage -= 10;
            }
        }
    }

    if(check_movement == 1){
        if(game->eleven->rage <= 96){
            game->eleven->rage += 2;
        }
    }

    if(game->eleven->life <= 0){
        return 1;
    }
    else if (game->eleven->life > 0){
        game->upside_down[game->eleven->pos_x][game->eleven->pos_y] = ELEVEN;
        return 0;
    }

    
}



void will_movement(Game* game){
    game->upside_down[game->will->pos_x][game->will->pos_y] = EMPTY;

        int dash_run = rand() % 11;
        int next_movement = rand() % 4;

        if(dash_run == 0){
            //UP DASH
            if(next_movement == 0){
                if(game->will->pos_x - 2 >= 0 && game->upside_down[game->will->pos_x - 2][game->will->pos_y] == EMPTY){
                    game->will->pos_x = game->will->pos_x - 2;
                }
            }
            //DOWN DASH
            else if(next_movement == 1){
                if(game->will->pos_x + 2 < 15 && game->upside_down[game->will->pos_x + 2][game->will->pos_y] == EMPTY){
                    game->will->pos_x = game->will->pos_x + 2;
                }
            }
            //LEFT DASH
            else if(next_movement == 2){
                if(game->will->pos_y - 2 >= 0 && game->upside_down[game->will->pos_x][game->will->pos_y - 2] == EMPTY){
                    game->will->pos_y = game->will->pos_y - 2;
                }
            }
            //RIGHT DASH
            else if(next_movement == 3){
                if(game->will->pos_y + 2 < 15 && game->upside_down[game->will->pos_x][game->will->pos_y + 2] == EMPTY){
                    game->will->pos_y = game->will->pos_y + 2;
                }
            }
        }
        else{
            //NORMAL UP MOVEMENT
            if(next_movement == 0){
                if(game->will->pos_x - 1 >= 0 && game->upside_down[game->will->pos_x - 1][game->will->pos_y] == EMPTY){
                    game->will->pos_x--;
                }
            }
            //NORMAL DOWN MOVEMENT
            else if(next_movement == 1){
                if(game->will->pos_x + 1 < 20 && game->upside_down[game->will->pos_x + 1][game->will->pos_y] == EMPTY){
                    game->will->pos_x++;
                }
            }
            //NORMAL LEF MOVEMENT
            else if(next_movement == 2){
                if(game->will->pos_y - 1 >= 0 && game->upside_down[game->will->pos_x][game->will->pos_y - 1] == EMPTY){
                    game->will->pos_y--;
                }
            }
            //NORMAL RIGHT MOVEMENT
            else if(next_movement == 3){
                if(game->will->pos_y + 1 < 20 && game->upside_down[game->will->pos_x][game->will->pos_y + 1] == EMPTY){
                    game->will->pos_y++;
                }
            }
        }
    
    game->upside_down[game->will->pos_x][game->will->pos_y] = WILL;
}


Game* starting_game(Game* game, Eleven* eleven, Will* will){
    game->eleven = eleven;
    game->will = will;
}


int main(){

    srand(time(NULL));

    //important variables
    char** upside_down;
    char** empty_room;
    Eleven *eleven;
    Will *will;
    Game *game;

    //GAME VARIABLES
    int EOG = 1;
    int isElevenDead = 0;

    will = (Will*) malloc(1 * sizeof(Will));
    will = create_will(will, eleven);

    eleven = (Eleven*) malloc(1 * sizeof(Eleven));
    eleven = create_eleven(eleven);
    
    game = (Game*) malloc(1 * sizeof(Game));
    game = starting_game(game, eleven, will);

    controls_box();

    empty_room_generator(game);
    show_empty_room(game);
    upside_down_generator(game);

    while(EOG == 1 && isElevenDead == 0 && game->eleven->upside_down_power == 0){
        isElevenDead = eleven_mechanic(game);
        show_empty_room(game);
    }

    //AFTER ENTER IN UPSIDE DOWN, ELEVEN TAKES 60 OF YOUR RAGE TO SUMMON THE PORTAL

    //IN UPSIDE DOWN, ELEVEN RECEIVE LESS RAGE


    if(isElevenDead == 0){
        game->eleven->rage-=60;
        game->eleven->portal_power = 0;
        game->eleven->upside_down_power = 0;
        game->will->will_saved = 0;
        game->eleven->take_will = 0;
        game->eleven->clairvoyance_power_qtd = 3;

        show_upside_down(game);

        while(isElevenDead == 0 && game->will->will_saved == 0){
            will_movement(game);
            isElevenDead = eleven_mechanic_ud(game);
            add_new_demodogs(game);
            show_upside_down(game);
        }

        if(isElevenDead == 1){
            printf("\033[1;32m");
            printf("\n\nELEVEN MORREU, VOCE PERDEU! :(\n");
            printf("\033[0m");
        }
        else{
            printf("\033[1;32m");
            printf("\n\nWILL FOI SALVO, VOCE VENCEU!\n\nVida restante da eleven: %d", game->eleven->life);
            printf("\033[0m");
        }
    }
    else{
        printf("\033[1;32m");
        printf("\n\nELEVEN MORREU, VOCE PERDEU! :(\n");
        printf("\033[0m");
    }


    return 0;
}
