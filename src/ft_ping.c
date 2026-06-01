
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "ft_ping.h"
#include <arpa/inet.h>
#include "ft_get_opt.h"
#include <linux/icmp.h>
#include <sys/socket.h>
 
#include <stdlib.h>
#include <linux/ip.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void print_help(void);

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

// L'algorithme standard du Checksum
unsigned short calculate_checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    
    return result;
}

int main(int argc, char **argv)
{
    opt_flag opt_flags[] = {
    // { info, 	  short, long,		   	content },
        { NO_PARAM, 	'v', "verbose",    	NULL },
        { NO_PARAM, 	'?', "help",       	NULL },
        { WITH_PARAM, 	'f', "file",       	NULL },
        { END_PARAM, 	0, NULL,       		NULL },
    };


    char *single_param[2] = {NULL};

    opt_data data = { opt_flags, single_param, 2 };

    if (ft_get_flags(argc, argv, &data)) {
        fprintf(stderr, "Erreur lors du parsing des arguments.\n");
        return 1;
    }
    // print_help();
    
    char ip_str[INET_ADDRSTRLEN];
    struct sockaddr_in addr;
    if (resolve_host(single_param[0], &addr))
        return (1);
    inet_ntop(AF_INET, &(addr.sin_addr), ip_str, INET_ADDRSTRLEN); // ask dns ip
    printf("PING %s (%s)\n", single_param[0], ip_str);


    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        fprintf(stderr, "Erreur lors de la création du socket: %s\n", strerror(errno));
        // problème de permissions
        if (errno == EPERM) {
            fprintf(stderr, "-> Indice : As-tu lancé le programme en tant que root (avec sudo) ?\n");
        }
        return (1);
    }

    printf("Succès ! Le socket RAW ICMP est ouvert. (File descriptor : %d)\n", sockfd);


    int sequence = 1;

    while (1) {

        struct icmphdr icmp_packet;
        memset(&icmp_packet, 0, sizeof(icmp_packet));

        icmp_packet.type = ICMP_ECHO;
        icmp_packet.code = 0;
        icmp_packet.un.echo.id = htons(getpid());
        icmp_packet.un.echo.sequence = htons(sequence);
        
        icmp_packet.checksum = 0;
        icmp_packet.checksum = calculate_checksum(&icmp_packet, sizeof(icmp_packet));

        int bytes_sent = sendto(sockfd, &icmp_packet, sizeof(icmp_packet), 0, (struct sockaddr *)&addr, sizeof(addr));
        if (bytes_sent <= 0) {
            perror("Erreur lors de l'envoi");
        } else {
            printf("Paquet seq=%d envoyé avec succès ! (%d octets)\n", sequence, bytes_sent);
        }

        sequence++;

        char recv_buffer[1024];
        struct sockaddr_in sender_addr;
        socklen_t sender_len = sizeof(sender_addr);

        ssize_t bytes_received = recvfrom(sockfd, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr *)&sender_addr, &sender_len);

        if (bytes_received < 0) {
            perror("Erreur lors de la réception");
            continue;
        }

        char sender_ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(sender_addr.sin_addr), sender_ip_str, INET_ADDRSTRLEN);

        struct iphdr *ip_reply = (struct iphdr *)recv_buffer;
        
        unsigned int ip_header_size = ip_reply->ihl * 4;

        struct icmphdr *icmp_reply = (struct icmphdr *)(recv_buffer + ip_header_size);


        if (icmp_reply->type == ICMP_ECHOREPLY) { // Type 0 = Réponse au Ping
            printf("%zd bytes from %s: icmp_seq=%d ttl=%d\n",
                bytes_received, sender_ip_str,ntohs(icmp_reply->un.echo.sequence), ip_reply->ttl);
        } else {
            printf("Paquet reçu, mais type ignoré : %d\n", icmp_reply->type);
        }
        
        sleep(1);
    }







    close(sockfd);
    return 0;
}