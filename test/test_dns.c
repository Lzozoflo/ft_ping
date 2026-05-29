#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>      // Obligatoire pour getaddrinfo
#include <arpa/inet.h>

int resolve_host(const char *target, struct sockaddr_in *addr) {
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // ipv4
    hints.ai_socktype = SOCK_RAW; 
    hints.ai_protocol = IPPROTO_ICMP;

    int ret = getaddrinfo(target, NULL, &hints, &res);
    if (ret != 0) {
        printf("./ft_ping: %s: unknown host\n", target);
        return (-1);
    }

    *addr = *(struct sockaddr_in *)res->ai_addr;
    freeaddrinfo(res);
    return (0);
}


int main(int argc, char **argv) {


    if (argc != 2) {
        printf("Usage: %s <hostname>\n", argv[0]);
        return 1;
    }

    char *hostname = argv[1];

    struct sockaddr_in addr;
    
    resolve_host(hostname, &addr);
    
    char ip_str[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(addr.sin_addr), ip_str, INET_ADDRSTRLEN);
    
    printf("PING %s (%s)\n", hostname, ip_str);


    return 0;
}