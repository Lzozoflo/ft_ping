#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <errno.h>

int main(void) {
    
    int sockfd;

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (sockfd < 0) {

        fprintf(stderr, "Erreur lors de la création du socket: %s\n", strerror(errno));
        
        // problème de permissions
        if (errno == EPERM) {
            fprintf(stderr, "-> Indice : As-tu lancé le programme en tant que root (avec sudo) ?\n");
        }
        return (EXIT_FAILURE);
    }

    printf("Succès ! Le socket RAW ICMP est ouvert. (File descriptor : %d)\n", sockfd);

    close(sockfd);
    
    return (EXIT_SUCCESS);
}