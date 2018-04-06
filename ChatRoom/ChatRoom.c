#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5999

char *progName;
void printUsageAndExit();
void connectToServer(char *serverAddr);
void startServer();

void main(int argc, char **argv)
{
    progName = argv[0];
    if (argc == 1){
        printUsageAndExit();
    } else if (strcmp(argv[1], "-s") == 0) {
        printf("Starting the server...\n");
        startServer();
    } else if (strcmp(argv[1], "-c") == 0) {
        if (argc < 3) {
            printUsageAndExit();
        }
        printf("Connecting to server %s...\n", argv[2]);
        connectToServer(argv[2]);
    } else {
        printUsageAndExit();
    }
}

void printUsageAndExit() {
        printf("Usage: \n\tServer : %s -s\n\tClient : %s -c <serverIP>\n", progName,
               progName);
        exit(EXIT_FAILURE);
}

void startServer() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hi! What is your name? ";

	// Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the PORT
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    char name[1024];
    send(new_socket , hello, strlen(hello) , 0 );
    valread = read(new_socket , name, 1024);
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    if (setsockopt (new_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0)
        error("setsockopt failed\n");

    if (setsockopt (new_socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0)
        error("setsockopt failed\n");

    pid_t pid = fork();
    if (pid == 0) {
        while (1) {
            char buffer[1024];
            memset(buffer, 0, 1024);
            valread = read(new_socket , buffer, 1024);
            if (strlen(buffer))
                printf("%s: %s\n", name, buffer);
        }
    } else {
        while (1) {
            char msg[1024];
            gets(msg);
            send(new_socket , msg, strlen(msg) , 0 );
            if (strlen(msg))
                printf("Server: %s\n", msg);
        }
    }
}

void connectToServer(char *serverAddr) {
	struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, serverAddr, &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return;
    }
    read(sock , buffer, 1024);
    printf("%s", buffer);


    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    if (setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0)
        error("setsockopt failed\n");

    if (setsockopt (sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0)
        error("setsockopt failed\n");

    pid_t pid = fork();
    if (pid == 0) {
        while (1) {
            char buf[1024];
            gets(buf);
            send(sock , buf, strlen(buf) , 0 );
            if (strlen(buf))
                printf("Myself : %s\n", buf);
        }
    } else {
        while(1) {
            char buf[1024];
            memset(buf, 0, 1024);
            read(sock, buf, 1024);
            if (strlen(buf))
                printf("Server : %s\n", buf);
        }
    }
}
