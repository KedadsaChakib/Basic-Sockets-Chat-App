#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> // Added for inet_addr function

int main() {
    char phrase[255];

    struct sockaddr_in informations;
    informations.sin_family = AF_INET;
    informations.sin_port = htons(6666);
    informations.sin_addr.s_addr = inet_addr("127.0.0.1");
    int socketID = socket(AF_INET, SOCK_STREAM, 0);

    if (socketID == -1) {
        perror("socket");
        exit(-1);
    }

    if (connect(socketID, (struct sockaddr*) &informations, sizeof(struct sockaddr_in)) == -1) {
        perror("connect");
        exit(-1);
    }

    do {
        printf("Enter a phrase: ");
        scanf("%s", phrase); // Read phrase from user input

        if (strcmp(phrase, "EXIT") != 0) {
            if (send(socketID, phrase, strlen(phrase), 0) == -1) {
                perror("send");
                exit(-1);
            }

            memset(phrase, 0, sizeof(phrase)); // Clear phrase buffer

            if (recv(socketID, phrase, sizeof(phrase), 0) == -1) {
                perror("recv");
                exit(-1);
            }
            printf("Phrase received: %s\n", phrase);
        }
    } while (strcmp(phrase, "EXIT") != 0);

    shutdown(socketID, SHUT_RDWR);

    return 0;
}
