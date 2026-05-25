
#include <stdio.h>          // dprintf
#include <string.h>         // 
#include "ft_ping.h"
#include "ft_get_opt.h"


int main(int argc, const char **argv)
{
    opt_flag opt_flags[] = {
    // { info, 	  short, long,		   	content },
        { NO_PARAM, 	'v', "verbose",    	NULL },
        { NO_PARAM, 	'h', "help",       	NULL },
        { WITH_PARAM, 	'f', "file",       	NULL },
        { END_PARAM, 	0, NULL,       		NULL },
    };
    char *single_param[4] = {NULL};

    opt_data data = { opt_flags, single_param, 4 };

    if (ft_get_flags(argc, argv, &data)) {
        fprintf(stderr, "Erreur lors du parsing des arguments.\n");
        return 1;
    }


    return 0;
}