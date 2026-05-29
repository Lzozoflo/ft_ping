
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include "ft_ping.h"
#include <arpa/inet.h>
#include "ft_get_opt.h"
#include <sys/socket.h>


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

    {

        struct sockaddr_in addr;
        
        char ip_str[INET_ADDRSTRLEN];
        
        resolve_host(single_param[0], &addr);
        
        inet_ntop(AF_INET, &(addr.sin_addr), ip_str, INET_ADDRSTRLEN);
        
        printf("PING %s (%s)\n", single_param[0], ip_str);

    }









    // int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    // if (sockfd < 0) {

    //     fprintf(stderr, "Erreur lors de la création du socket: %s\n", strerror(errno));
        
    //     // problème de permissions
    //     if (errno == EPERM) {
    //         fprintf(stderr, "-> Indice : As-tu lancé le programme en tant que root (avec sudo) ?\n");
    //     }
    //     return (EXIT_FAILURE);
    // }

    // printf("Succès ! Le socket RAW ICMP est ouvert. (File descriptor : %d)\n", sockfd);

    // close(sockfd);
    

    return 0;
}