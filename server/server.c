#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> // Added for inet_addr function

int main() {
struct sockaddr_in information_server;
struct sockaddr_in information_client;

int socketID = socket(AF_INET,SOCK_STREAM,0);
int connexion =0;
char phrase[255];

socklen_t len= sizeof(struct sockaddr_in);

if(socketID ==-1){
    perror("socket");
    exit(-1);

}

memset(&information_server,0,sizeof(struct sockaddr_in));
information_server.sin_port = htons(6666);
information_server.sin_family = AF_INET;

if((bind(socketID,(struct sockaddr*)&information_server,sizeof(struct sockaddr)))==-1){
    perror("bind");
    exit(-1);
}


if ((listen(socketID,5))==-1){
    perror("listen");
    exit(-1);
}

memset(&information_client,0,sizeof(struct sockaddr_in));
connexion = accept(socketID,(struct sockaddr *) &information_client,&len);

if(connexion==-1){
    perror("accept");
    exit(-1);
}
 printf("Connexion acceptée de %s\n",inet_ntoa(information_client.sin_addr));

 do{
    memset(phrase,0,255);
    recv(connexion,phrase,255,0);
    printf("Phrase recue : %s \n",phrase);
 send(connexion,phrase,strlen(phrase),0);

 }while (strcmp(phrase,"EXIT")!=0);

 shutdown(socketID,SHUT_RDWR);

return 0;
}

