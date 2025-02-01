#ifndef GRID
#define GRID

#include "network_packet.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <utility>

class grid {
    public:
        // char 2D found in both subclasses.
        char theGrid_ [10][10];
};

class oceanGrid : public grid {
    public:
        //vectors that hold all the coordinates of the pieces placed on the grid.
        std::vector<std::pair<int, int>> carrierPos;
        std::vector<std::pair<int, int>> battleshipPos;
        std::vector<std::pair<int, int>> destroyerPos;
        std::vector<std::pair<int, int>> submarinePos;
        std::vector<std::pair<int, int>> patrolPos;

        //constructor fills ocean grid with default value "-"
        oceanGrid(){
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                    this->theGrid_[i][j] = '-';
                }
            }
        }

        //functions print the current state of grid
        void printGrid(){
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                    if(this->theGrid_ [i][j] == 'X'){
                        printf("\033[0;31m%c ", this->theGrid_[i][j]);
                        printf("\033[0m");
                    } else if(this->theGrid_ [i][j] != '-' && this->theGrid_ [i][j] != 'X' ) {
                        printf("\033[0;32m%c ", this->theGrid_[i][j]);
                        printf("\033[0m");
                    } else {
                        printf("%c ", this->theGrid_[i][j]);
                    }
                    
                }
                printf("\n");
            }
            printf("\n");
        }

        // when the player attempts to place a piece, function is used to validate if the player's move is legal.
        bool canUpdate(int x, int y, int shipType, char place){
                if( x < 0 || x >= 10 ) {
                    printf("Invalid X coordinate!\n\n");
                    return false;
                }
                if( y < 0 || y >= 10 ) {
                    printf("Invalid Y coordinate!\n\n");
                    return false;
                }
                if (!((place == 'H' || place == 'h') || (place == 'V' || place == 'v'))){
                    printf("Invalid placement input! Please try again!\n\n");
                    return false;
                }

                if(shipType == 1){
                    if(place == 'H' || place == 'h'){
                        if((x) + 5 > 9 ){
                            printf("Ship placement would be out of bounds! Please try again!\n\n");
                            return false;
                        }
                    } else if(place == 'V' || place == 'v'){
                        if((y) + 5 > 9 ){
                            printf("Ship placement would be out of bounds! Please try again!\n\n");
                            return false;
                        } 
                    }
                } else if(shipType == 2){
                    if(place == 'H' || place == 'h'){
                        if((x) + 4 > 9 ){
                            printf("Ship placement would be out of bounds! Please try again!\n");
                            return false;
                        }
                        for(int i = x; i < (x) + 4; i++){

                            if(this->theGrid_[y][i] != '-') {
                                printf("A ship is present at this location! Please try again\n\n");
                                return false;
                            }
                        }
                        printf("\n");
                    } else if(place == 'V' || place == 'v'){
                        if((y) + 4 > 9 ){
                            printf("Ship placement would be out of bounds! Please try again!\n");
                            return false;
                        }
                        for(int i = y; i < (y) + 4; i++){
                            if(this->theGrid_ [i][x] != '-') {
                                printf("A ship is present at this location! Please try again\n\n");
                                return false;
                            }
                        }
                    }
                    
                } else if(shipType == 3){
                    if(place == 'H' || place == 'h'){
                        if((x) + 3 > 9 ){
                            printf("Ship placement would be out of bounds! Please try again!\n\n");
                            return false;
                        }
                        for(int i = x; i < (x) + 3; i++){
                            if(this->theGrid_ [y][i] != '-') {
                                printf("A ship is present at this location! Please try again\n\n");
                                return false;
                            }
                        }
                    } else if(place == 'V' || place == 'v'){
                        if((y) + 3 > 9 ){
                            printf("Ship placement would be out of bounds! Please try again!\n\n");
                            return false;
                        }
                        for(int i = y; i < (y) + 3; i++){
                            if(this->theGrid_ [i][x] != '-') {
                                printf("A ship is present at this location! Please try again\n\n");
                                return false;
                            }
                        }
                    }
                    
                    // for(int i = x; i < x + 3; i++){
                    //     if(theGrid_ [i][y] != '-') return false;
                    // }

                } else if(shipType == 4){
                    if(place == 'H' || place == 'h'){
                        if((x) + 3 > 9 ){
                            printf("Ship placement would be out of bounds! Please try again!\n\n");
                            return false;
                        }
                        for(int i = x; i < (x) + 3; i++){
                            if(this->theGrid_ [y][i] != '-') {
                                printf("A ship is present at this location! Please try again\n\n");
                                return false;
                            }
                        }
                    } else if(place == 'V' || place == 'v'){
                        if((y) + 3 > 9 ){
                            printf("Ship placement would be out of bounds! Please try again!\n\n");
                            return false;
                        }
                        for(int i = y; i < (y) + 3; i++){
                            if(this->theGrid_ [i][x] != '-') {
                                printf("A ship is present at this location! Please try again\n\n");
                                return false;
                            }
                        }
                    }
                    
                    // for(int i = x; i < x + 3; i++){
                    //     if(theGrid_ [i][y] != '-') return false;
                    // }
                } else {
                    if(place == 'H' || place == 'h'){
                        if((x) + 2 > 9 ){
                            printf("Ship placement would be out of bounds! Please try again!\n\n");
                            return false;
                        }
                        for(int i = x; i < (x) + 2; i++){
                            if(this->theGrid_ [y][i] != '-') {
                                printf("A ship is present at this location! Please try again\n\n");
                                return false;
                            }
                        }
                    } else if(place == 'V' || place == 'v'){
                        if((y) + 2 > 9 ){
                            printf("Ship placement would be out of bounds! Please try again!\n\n");
                            return false;
                        }
                        for(int i = y; i < (y) + 2; i++){
                            if(this->theGrid_ [i][x] != '-') {
                                printf("A ship is present at this location! Please try again\\nn");
                                return false;
                            }
                        }
                    }
                    
                }
                return true;
            }

        // if the player's suggest move is legal, this function actually updates the function
        void updateGrid(int x, int y, int shipType, char place){
            std::pair<int, int> temp;
            if(shipType == 1){
                
                if(place == 'H' || place == 'h'){
                    for(int i = x; i < (x) + 5; i++){
                        this->theGrid_ [y][i] = 'C';
                        temp.first = i; 
                        temp.second = y; 
                        this->carrierPos.push_back(temp);
                    }
                    
                } else {
                    for(int i = y; i < (y) + 5; i++){
                        this->theGrid_ [i][x] = 'C';
                        temp.first = x; 
                        temp.second = i; 
                        this->carrierPos.push_back(temp);
                    }
                }
            } else if(shipType == 2){
                if(place == 'H' || place == 'h'){
                    for(int i = x; i < (x) + 4; i++){
                        this->theGrid_ [y][i] = 'B';
                        temp.first = i; 
                        temp.second = y; 
                        this->battleshipPos.push_back(temp);
                    }
                } else {
                    for(int i = y; i < (y) + 4; i++){
                        this->theGrid_ [i][x] = 'B';
                        temp.first = x; 
                        temp.second = i; 
                        this->battleshipPos.push_back(temp);
                    }
                }
            } else if(shipType == 3){
                if(place == 'H' || place == 'h'){
                    for(int i = x; i < (x) + 3; i++){
                        this->theGrid_ [y][i] = 'D';
                        temp.first = i; 
                        temp.second = y; 
                        this->destroyerPos.push_back(temp);
                    }
                } else {
                    for(int i = y; i < (y) + 3; i++){
                        this->theGrid_ [i][x] = 'D';
                        temp.first = x; 
                        temp.second = i; 
                        this->destroyerPos.push_back(temp);
                        
                    }
                }
            } else if(shipType == 4){
                if(place == 'H' || place == 'h'){
                    for(int i = x; i < (x) + 3; i++){
                        this->theGrid_ [y][i] = 'S';
                        temp.first = i; 
                        temp.second = y; 
                        this->submarinePos.push_back(temp);
                    }
                } else {
                    for(int i = y; i < (y) + 3; i++){
                        this->theGrid_ [i][x] = 'S';
                        temp.first = x; 
                        temp.second = i; 
                        this->submarinePos.push_back(temp);
                    }
                }
            } else {
                if(place == 'H' || place == 'h'){
                    for(int i = x; i < (x) + 2; i++){
                        this->theGrid_ [y][i] = 'P';
                        temp.first = i; 
                        temp.second = y; 
                        patrolPos.push_back(temp);
                    }
                } else {
                    for(int i = y; i < (y) + 2; i++){
                        this->theGrid_ [i][x] = 'P';
                        temp.first = x; 
                        temp.second = i; 
                        this->patrolPos.push_back(temp);
                    }
                }
            }
        }

        // function in charge of prompting the player to input coordinates, and calling other functions
        void configGrid(){
            int posX;
            int posY;
            char buffer[100];
            char placement;
            bool wasValid;
            printf("\n\nWelcome to Battleship! Let's place your pieces to start the game!\n");

            printf("Place your Carrier!\n\n");

            fgets(buffer, 100, stdin);
            sscanf(buffer, "%d %d %c", &posX, &posY, &placement);
            
            while(true){
                printf("Enter the ship's X, Y coordinates, along with it's placement! Use H to place the piece horizontally, and user V to place the ship vertically! (e. g. 1 2 H): ");
                fgets(buffer, 100, stdin);
                sscanf(buffer, "%d %d %c", &posX, &posY, &placement);
                posX--;
                posY--;
                wasValid = canUpdate(posX, posY, 1, placement);
                if(wasValid){
                    this->updateGrid(posX, posY, 1, placement);
                    this->printGrid();
                    break;
                }
            }

            memset(buffer, '\0', sizeof(buffer));
            printf("Place your Battleship!\n\n");

            while(true){
                printf("Enter the ship's X, Y coordinates, along with it's placement!: ");
                fgets(buffer, 100, stdin);
                sscanf(buffer, "%d %d %c", &posX, &posY, &placement);
                posX--;
                posY--;
                wasValid = canUpdate(posX, posY, 2, placement);
                if(wasValid){
                    this->updateGrid(posX, posY, 2, placement);
                    this->printGrid();
                    break;
                }
            }

            memset(buffer, '\0', sizeof(buffer));
            printf("Place your Destroyer!\n\n");

            while(true){
                printf("Enter the ship's X, Y coordinates, along with it's placement!: ");
                fgets(buffer, 100, stdin);
                sscanf(buffer, "%d %d %c", &posX, &posY, &placement);
                posX--;
                posY--;
                wasValid = canUpdate(posX, posY, 3, placement);
                if(wasValid){
                    this->updateGrid(posX, posY, 3, placement);
                    this->printGrid();
                    break;
                }
            }

            memset(buffer, '\0', sizeof(buffer));
            printf("Place your Submarine!\n\n");

            while(true){
                printf("Enter the ship's X, Y coordinates, along with it's placement!: ");
                fgets(buffer, 100, stdin);
                sscanf(buffer, "%d %d %c", &posX, &posY, &placement);
                posX--;
                posY--;
                wasValid = canUpdate(posX, posY, 4, placement);
                if(wasValid){
                    this->updateGrid(posX, posY, 4, placement);
                    this->printGrid();
                    break;
                }
            }
            
            memset(buffer, '\0', sizeof(buffer));
            printf("Place your Patrol Boat!\n\n");

            while(true){
                printf("Enter the ship's X, Y coordinates, along with it's placement!: ");
                fgets(buffer, 100, stdin);
                sscanf(buffer, "%d %d %c", &posX, &posY, &placement);
                posX--;
                posY--;
                wasValid = canUpdate(posX, posY, 5, placement);
                if(wasValid){
                    this->updateGrid(posX, posY, 5, placement);
                    system("clear");
                    printf("OCEAN GRID\n");
                    this->printGrid();
                    break;
                }
            }
            printf("\n\n");
            // printf("C: %d, B: %d, D: %d, S: %d, P: %d\n", (int)this->carrierPos.size(), (int)this->battleshipPos.size(), (int)this->destroyerPos.size(), (int)this->submarinePos.size(), (int)this->patrolPos.size());
        }

        // function figures out if the ship that has been hit, is sunk
        bool shipSunk(char ship){
            if(ship == 'C'){
                // printf("Hi %d\n", (int)carrierPos.size());
                if ((int)this->carrierPos.size() == 0){
                    // printf("Nah %d\n", (int)carrierPos.size());
                    return true;
                }
                return false;
            } else if(ship == 'B'){
                if ((int)this->battleshipPos.size() == 0){
                    return true;
                }
                return false;
            } else if(ship == 'D'){
                if ((int)this->destroyerPos.size() == 0){
                    return true;
                }
                return false;
            } else if(ship == 'S'){
                if ((int)this->submarinePos.size() == 0){
                    return true;
                }
                return false;
            } else if(ship == 'C') {
                if ((int)this->patrolPos.size() == 0){
                    return true;
                }
                return false;
            }
        }

        // function to figure out if the shot from the opponent has hit a ship on ocean grid
        int isHit(int x, int y, network_packet* packet){
            if (this->theGrid_ [y][x] == '-' || this->theGrid_ [y][x] == 'X'){
                return 0;
            } else {
                if(this->theGrid_ [y][x] == 'C'){
                    for(int i = 0; i < (int)this->carrierPos.size(); i++){
                        if(this->carrierPos[i].first == x && this->carrierPos[i].second == y){
                            this->carrierPos.erase(this->carrierPos.begin()+ i);
                            break;
                        }
                    }

                    if(shipSunk('C')){
                        this->theGrid_ [y][x] = 'X';
                        packet->ship_type = 1;
                        return 2;
                    }
                } else if(this->theGrid_ [y][x] == 'B'){
                    for(int i = 0; i < (int)this->battleshipPos.size(); i++){
                        if(this->battleshipPos[i].first == x && this->battleshipPos[i].second == y){
                            this->battleshipPos.erase(this->battleshipPos.begin()+ i);
                            break;
                        }
                    }

                    if(shipSunk('B')){
                        theGrid_ [y][x] = 'X';
                        packet->ship_type = 2;
                        return 2;
                    }
                } else if(this->theGrid_ [y][x] == 'D'){
                    for(int i = 0; i < (int)this->destroyerPos.size(); i++){
                        if(this->destroyerPos[i].first == x && this->destroyerPos[i].second == y){
                            destroyerPos.erase(this->destroyerPos.begin()+ i);
                            break;
                        }
                    }

                    if(shipSunk('D')){
                        this->theGrid_ [y][x] = 'X';
                        packet->ship_type = 3;
                        return 2;
                    }
                } else if(this->theGrid_ [y][x] == 'S'){
                    for(int i = 0; i < (int)this->submarinePos.size(); i++){
                        if(this->submarinePos[i].first == x && this->submarinePos[i].second == y){
                            this->submarinePos.erase(this->submarinePos.begin()+ i);
                            break;
                        }
                    }

                    if(shipSunk('S')){
                        this->theGrid_ [y][x] = 'X';
                        packet->ship_type = 4;
                        return 2;
                    }
                } else if(this->theGrid_ [y][x] == 'P'){
                    for(int i = 0; i < (int)this->patrolPos.size(); i++){
                        if(this->patrolPos[i].first == x && this->patrolPos[i].second == y){
                            this->patrolPos.erase(this->patrolPos.begin()+ i);
                            break;
                        }
                    }
                    if(shipSunk('P')){
                        this->theGrid_ [y][x] = 'X';
                        packet->ship_type = 5;
                        return 2;
                    }
                }
                this->theGrid_ [y][x] = 'X';
                return 1;
            }
        }

        // function to handle the shot given by opponent. Reports to player if the shot is a miss, hit, or hit & sunk
        network_packet handleShot(network_packet* pkt, int* SR){
            network_packet* returnPkt = new network_packet();
            int x = (pkt->x)-1;
            int y = (pkt->y)-1;
            // returnPkt->player_num = 0;
            returnPkt->x = pkt->x;
            returnPkt->y = pkt->y;
            returnPkt->ship_type = 0;
            // printf(" Packet received: %hhd %hhd %hhd %hhd %hhd\n", pkt->opcode, pkt->player_num, pkt->ship_type, pkt->x, pkt->y);
            // printf("X, Y: %d, %d\n", x, y);
            printf("Shot received!\n");
            printf("Shot has...");
            fflush(stdout);
            sleep(1);
            printf(".");
            fflush(stdout);
            sleep(1);
            printf(".");
            fflush(stdout);
            sleep(1);
            printf(".");
            fflush(stdout);
            sleep(2);
            int hit = isHit(x, y, pkt);
            if(hit == 0){
                *SR--;
                printf(" \033[0;32m MISSED!\n");
                returnPkt->opcode = 2;
            } else if(hit == 1){
                printf(" \033[0;31m HIT!\n");
                returnPkt->opcode = 3;
            } else if(hit == 2){
                printf(" \033[0;91m HIT! SHIP SUNK!\n");
                returnPkt->opcode = 4;
            }
            printf("\033[0m");
            printf("\n");
            fflush(stdout);
            return *returnPkt;
        }
};

class targetGrid : public grid {
    public:
        // string array to store the color of "W" in grid
        std::string targetGridColor[100];

        // constructor configure the targetGrid, along with associating a color with each "W". Colors generated selected randomly.
        targetGrid(){
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                    this->theGrid_[i][j] = 'W';
                }
            }

            for(int i = 0; i < 100; i++){
                if(((rand() % (1 - 0 + 1)) + 0) == 0){
                    targetGridColor[i] = "\033[34m";
                } else {
                    targetGridColor[i] = "\033[36m";
                }
            }
            
        }

        //functions print the current state of grid
        void printGrid(){
            int count = 0;
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                    if(this->theGrid_ [i][j] == 'W') {
                        printf("%s%c ", targetGridColor[count].c_str(), this->theGrid_ [i][j]) ;
                        printf("\033[0m");
                    } else if(this->theGrid_ [i][j] == 'X'){
                        printf("\033[31m%c ", this->theGrid_[i][j]);
                        printf("\033[0m");
                    } else {
                        printf("\033[32m%c ", this->theGrid_[i][j]);
                        printf("\033[0m");
                    }
                    count++;
                }
                printf("\n");
            }
            printf("\n");
        }

        // after shooting a shot, this function is called to report the status of the shot (miss, hit, hit & sunk)
        void handleResponse(network_packet* pkt, int* SS){
            int x = (pkt->x) - 1;
            int y = (pkt->y) - 1;
            printf("Attack delivered!\n");
            printf("Your shot has...");
            fflush(stdout);
            sleep(1);
            printf(".");
            fflush(stdout);
            sleep(1);
            printf(".");
            fflush(stdout);
            sleep(1);
            printf(".");
            fflush(stdout);
            sleep(2);
            if(pkt->opcode == OPCODE_MISS){
                this->theGrid_[y][x] = 'X';
                printf("\033[31m MISSED!\n\n");
                printf("\033[0m");
            }  else {
                this->theGrid_[y][x] = 'H';
                printf("\033[32m HIT!\n");
                printf("\033[0m");
                sleep(1);
                if(pkt->opcode == OPCODE_HIT_SUNK) {
                    *SS++;
                    if(pkt->ship_type == 1){
                        printf("You've sunk their Carrier!\n\n");
                    } else if(pkt->ship_type == 2){
                        printf("You've sunk their Battleship!\n\n");
                    } else if(pkt->ship_type == 3){
                        printf("You've sunk their Destroyer!\n\n");
                    } else if(pkt->ship_type == 4){
                        printf("You've sunk their Submarine!\n\n");
                    } else {
                        printf("You've sunk their Patrol!\n\n");
                    }
                } else {
                    printf("\n");
                }
            }
            sleep(2);
        }
};

#endif