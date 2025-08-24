#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define HOSTNAME "127.0.0.1"
#define PORT 12345

int main(int argc, char *argv[]) {
    // Print startup message
    printf("UDP Message Sender\n");

    // Message to be sent
    const char *message = "Hello, UDP!";

    // Create a UDP socket
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Print the socket file descriptor
    printf("Socket created with file descriptor: %d\n", sockfd);

    // Define the destination address structure
    struct sockaddr_in destaddr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = inet_addr(HOSTNAME)
    };

    // Print the destination address
    printf("Sending to %s:%d\n", HOSTNAME, PORT);

    // Print the header for sent messages
    printf("\ni\tbytes\tmessage\n");

    // Create and send multiple messages
    char sockmessage[1024];
    for (int i = 0; i < 10; i ++) {
        
        // Format the message to include the iteration number
        int n = snprintf(sockmessage, sizeof(sockmessage), "%s %d", message, i + 1);

        // Send the message to the receiver
        int bytes = sendto(
            sockfd, 
            sockmessage,
            (size_t) n,
            0, 
            (const struct sockaddr *) &destaddr,
            sizeof(destaddr)
        );
        // Print confirmation of sent message
        printf("%d\t%d\t%s\n", i, bytes, sockmessage);
    }

    // Close the socket
    close(sockfd);

    return 0;
} // int main(int, char**) {