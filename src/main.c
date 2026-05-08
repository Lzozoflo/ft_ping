
#include <stdio.h>          // dprintf
#include <string.h>
#include "main_cmd_bin.h"   // define


int  ft_isWhiteSpace(const char c){
    return ((c > 8 && c < 14) || c == 32);
}

size_t  lenTrim(const char *str){

    for (size_t i = 0; str[i]; i++)
    {
        if (!ft_isWhiteSpace(str[i])){
            return (i);
        }
    }
    return 0;
}

int	ft_strncmp(const char *str1, const char *str2, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

// -v, -h, -f, -l, -n, -w, -W, -p, -r, -s, -T, --ttl, --ip-timestamp
int  checkParameter(int argc, const char **arg, main_cmd_bin **optionStructPtr){

    if (argc < 2) {
        dprintf(2, "%s", ERROR_USAGE);
        return 1;
    }

    // Level   option = UNDEFINED;
    size_t lenArg = argc - 1;

    for (size_t i = 1; i <= lenArg; i++){
        int lenArgTrim = lenTrim(arg[i]);
        if (arg[i][lenArgTrim++] == '-') {
            const char *toCmp = arg[i] + lenArgTrim;

            if (strncmp(toCmp, "v", 2) == 0) {

            } else if (strncmp(toCmp, "h", 2) == 0) {
                printf("h");
                // option = HELP; 
            } else if (strncmp(toCmp, "f", 2) == 0) {
                printf("f");
                // option = HELP; 
            } else if (strncmp(toCmp, "l", 2) == 0) {
                printf("l");
                // option = HELP; 
            } else if (strncmp(toCmp, "n", 2) == 0) {
                printf("n");
                // option = HELP; 
            } else if (strncmp(toCmp, "w", 2) == 0) {
                printf("w");
                // option = HELP; 
            } else if (strncmp(toCmp, "W", 2) == 0) {
                printf("W");
                // option = HELP; 
            } else if (strncmp(toCmp, "p", 2) == 0) {
                printf("p");
                // option = HELP; 
            } else if (strncmp(toCmp, "r", 2) == 0) {
                printf("r");
                // option = HELP; 
            } else if (strncmp(toCmp, "s", 2) == 0) {
                printf("s");
                // option = HELP; 
            } else if (strncmp(toCmp, "T", 2) == 0) {
                printf("T");
                // option = HELP; 
            }
        }
    }
    
    (void)optionStructPtr;

    return 0;
}

int main(int argc, const char **argv)
{
    main_cmd_bin *optionStruct = NULL;

    if (checkParameter(argc, argv, &optionStruct)) {
        return 1;
    }


    return 0;
}