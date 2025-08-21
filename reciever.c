#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define HOSTNAME "127.0.0.1"
#define PORT 12345

int main(int argc, char *argv[]) {
    // Print startup message
    printf("UDP Message Reciever\n");

    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Print the socket file descriptor
    printf("Socket created with file descriptor: %d\n", sockfd);

    // Define the source address structure
    struct sockaddr_in srcaddr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = inet_addr(HOSTNAME)
    };

    // Print the source address
    printf("Listening on %s:%d\n", HOSTNAME, PORT);
    char buffer[1024];

    // Bind the socket to the address and port (127.0.0.1/12345)
    bind(sockfd, (const struct sockaddr *)&srcaddr, sizeof(srcaddr));

    printf("\ni\tbytes\tmessage\n");

    for (int i = 0; 1; i ++) {
        // Receive and print the message from the sender
        int res = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        printf("%d\t%d\t%s\n", i, res, buffer);
    }

    // Close the socket
    close(sockfd);

    return 0;
} // int main(int, char**) {