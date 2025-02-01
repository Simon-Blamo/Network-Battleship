/*
    Battleship test client application
    
    This code creates a client socket and connects to the server using the
    IP address and port number of the server. The client then enters a loop
    where it waits for user input and sends any messages to the server.
    The client also waits for incoming messages from the server and prints
    them to the console.

    How to compile:
        g++ test_client.cpp -o test_client -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>
#include <unistd.h>
#include "grid.h"

#define LOCALHOST "127.0.0.1"
#define SERVER_PORT 8888
#define BUFFER_SIZE 100


pthread_mutex_t socket_mutex = PTHREAD_MUTEX_INITIALIZER;
int client_socket = -1;
int player_number = -1;
bool connected = false;
int shipsSunk = 0;
int shipsRemaining = 5;
oceanGrid* theOceanGrid;
targetGrid* theTargetGrid;
int totalNumOfPlayers = 0;
int turn = 0;




// network send thread
void *tx(void *arg) {
    pthread_detach(pthread_self());
    int ret;
    char buffer[BUFFER_SIZE];
    network_packet pkt;

    // delay to allow recv of connect opcode
    sleep(1);

    // loop forever

    pkt.player_num = player_number;
    pkt.opcode = 0;
    send(client_socket, &pkt, sizeof(network_packet), 0);
    sleep(2);
    while (1) {
        if(turn == player_number){
            printf("Enter X, Y coordinates (Enter 0, 0 to quit):\n");
            fflush(stdout);
            fgets(buffer, BUFFER_SIZE, stdin);
            sscanf(buffer, "%hhd %hhd", &pkt.x, &pkt.y);
            if(pkt.x == 0 && pkt.y == 0){
                pkt.opcode = 6;
            } else {
                pkt.opcode = 1;
            }
            pthread_mutex_lock(&socket_mutex);
            ++turn;
            pkt.turn = turn;
            if ((ret = send(client_socket, &pkt, sizeof(network_packet), 0) != sizeof(network_packet))) {
                perror("send error");
            } else {
                // printf("Sent: %hhd %hhd %hhd %hhd %hhd\n", pkt.player_num, pkt.opcode, pkt.x, pkt.y, pkt.ship_type);
            }
            if(totalNumOfPlayers != 2){
                if(turn == totalNumOfPlayers-1){
                turn = 0;
                }
            }
            pthread_mutex_unlock(&socket_mutex);
            if(pkt.x == 0 && pkt.y == 0){
                exit(0);
            }
        } else {
            while (turn != player_number);
        }
        
    }
}

// network recv thread
void *rx(void *arg) {
    pthread_detach(pthread_self());
    int ret;
    char buffer[BUFFER_SIZE];
    network_packet pkt;
    network_packet sendBackPkt;

    // loop forever
    while (1) {
        // block on read
        if ((ret = recv(client_socket, buffer, BUFFER_SIZE, 0)) == 0) {
            perror("recv failed");
            exit(EXIT_FAILURE);
        }        else {
            // check for valid packet length
            if (ret != sizeof(network_packet)) {
                printf("WARNING: packet size %d from client_socket ignored\n", ret);
            } else {
                // copy the receive buffer into the pkt struct
                pthread_mutex_lock(&socket_mutex);
                memcpy(&pkt, buffer, sizeof(network_packet));

                // is this the player_num response sent after connect?
                if (pkt.opcode == OPCODE_CONNECT) {
                    if(!connected) {
                        player_number = pkt.player_num;
                        printf("You're player %d!\n", player_number);
                        connected = true;
                    } else {
                        printf("Player %d connected!\n", pkt.player_num);
                    }
                    if(totalNumOfPlayers < pkt.numOfPlayers){
                        totalNumOfPlayers = pkt.numOfPlayers;
                    }
                    // printf("Total players = %d\n", totalNumOfPlayers);
                } else {
                    if(pkt.opcode == OPCODE_SHOT){
                        sendBackPkt = theOceanGrid->handleShot(&pkt, &shipsRemaining);

                        printf("OCEAN GRID\n");
                        theOceanGrid->printGrid();
                        if(shipsRemaining == 0){
                            printf("ALL PLAYER SHIPS HAVE SUNK!\n");
                            printf("\033[31mYOU LOSE!\n");
                            sleep(1);
                            printf("YOU LOSE!\n");
                            sleep(1);
                            printf("YOU LOSE!\n");
                            sleep(3);
                            printf("YOU LOSE!\n");
                            printf("\033[0m");
                            exit(0);
                            
                        }
                        turn = pkt.turn;
                        sendBackPkt.turn = pkt.turn;
                        if(totalNumOfPlayers == 2){
                            if (player_number == 1) {
                                turn = 1;
                                sendBackPkt.turn = 1;
                            } else {
                                turn = 0;
                                sendBackPkt.turn = 0;
                            }
                        }
                        send(client_socket, &sendBackPkt, sizeof(network_packet), 0);
                        if(turn != player_number) {
                            sleep(6);
                            printf("Waiting for turn...\n");
                        }
                    } else if(pkt.opcode == 6){
                        printf("\nOpposing player has quit! You win!\n\n");
                        exit(0);
                    } else {
                        if(pkt.turn - 1 == player_number || ((pkt.turn == 0 &&  player_number == 1) && totalNumOfPlayers)) {
                            theTargetGrid->handleResponse(&pkt, &shipsSunk);

                            printf("TARGET GRID\n");
                            theTargetGrid->printGrid();
                            if(shipsSunk == 5){
                                printf("ALL OPPONENTS SHIPS HAVE SUNK!\n");
                                printf("\033[32mYOU WIN!\n");
                                printf("\033[0m");
                                exit(0);
                            }
                            printf("Waiting for turn...\n");
                            fflush(stdout);
                        }
                    }
                    // display received packet fields
                    // printf("\nReceived: %hhd %hhd %hhd %hhd %hhd\n", pkt.player_num, pkt.opcode, pkt.x, pkt.y, pkt.ship_type);

                    // repeat prompt
                }
                pthread_mutex_unlock(&socket_mutex);
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    printf("Start Game or Exit Program\n");
    printf("1. Start Game\n");
    printf("2. Exit\n");
    printf("Selection: ");
    
    int opt = 0;
    while (opt != 1 || opt != 2)
    {
        scanf("%d", &opt);
        if(opt == 1 || opt == 2){
            break;
        }
        printf("\n1. Start Game\n");
        printf("2. Exit\n");
        printf("Selection: ");
    }
    if(opt == 2){
        exit(0);
    }
    
    struct sockaddr_in serv_addr;
    char const *server_address;
    theOceanGrid = new oceanGrid();
    theTargetGrid = new targetGrid();
    theOceanGrid->configGrid();
    pthread_mutex_init(&socket_mutex, NULL);

    // use server addr if specified on command line, otherwise use localhost
    if (argc > 1) {
        server_address = argv[1];
    }
    else {
        server_address = LOCALHOST;
    }

    // create client socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // initialize sockaddr_in fields
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, server_address, &serv_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    // connect to server
    if (connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    // Create two threads
    pthread_t thread0, thread1;
    pthread_create(&thread0, NULL, tx, NULL);
    pthread_create(&thread1, NULL, rx, NULL);

    // Wait for threads to finish
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);

    return 0;
}
