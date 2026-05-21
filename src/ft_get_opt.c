#include <stdio.h>
#include "ft_get_opt.h"

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_get_short_flag(opt_flag *opt_flags, char c, char **argv)
{
	for (int i = 0; !(opt_flags[i].info & END_PARAM); i++) {

		if (opt_flags[i].short_flag == c) {

			opt_flags[i].info |= ACTIVE;

			if (opt_flags[i].info & WITH_PARAM) {

                if (!argv[1]) { return (-1); } // secu si pas d'argument apres -f

				// printf("short_flag: -%c <argv: %s>\n", opt_flags[i].short_flag, argv[1]);
				opt_flags[i].content = argv[1];
				return (1);
			}
			// printf("short_flag: -%c\n", opt_flags[i].short_flag);
			return (0);
		}
		// printf("-%c cmp to -%c\n", c, opt_flags[i].short_flag);
	}
	return (0);
}

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (!(s1[i] == s2[i]))
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

static int	ft_strncmp(const char *str1, const char *str2, size_t len)
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

static int	ft_get_long_flag(opt_flag *opt_flags, char *opt, char **argv)
{
	for (int i = 0; !(opt_flags[i].info & END_PARAM); i++) {

		if (opt_flags[i].long_flag && !ft_strcmp(opt, opt_flags[i].long_flag)) {
			
			opt_flags[i].info |= ACTIVE;

			if (opt_flags[i].info & WITH_PARAM) {

                if (!argv[1]) { return (-1); } // Sécurité si pas d'argument après -f

				// printf("short_flag: -%c <argv: %s>\n", opt_flags[i].short_flag, argv[1]);
				opt_flags[i].content = argv[1];
				return (1);
			}
			// printf("long_flag: --%s\n", opt_flags[i].long_flag);
			return (0);
		}
		// printf("--%s cmp to --%s\n", opt, opt_flags[i].long_flag);
	}
	return (0);
}

int		ft_get_flags(int argc, char **argv, opt_data *data)
{
	int     data_idx = 0;
    int     ret = 0;
	int		i = 0;
 
	if (!data || !data->opt_flags || !argv || !data->data)
        return 1;

	while (++i < argc) {

		if (!ft_strncmp(argv[i], "--", 2)){

			ret = ft_get_long_flag(data->opt_flags, &argv[i][2], &argv[i]);
			if (ret == -1) { return -1; }
			i += ret;
		
		} else if (argv[i][0] == '-') {

			if (ft_strlen(argv[i]) != 2) { return -1; }

			ret = ft_get_short_flag(data->opt_flags, argv[i][1], &argv[i]);
			if (ret == -1) { return -1; }
			i += ret;

		} else {
			// le reste (arguments libres)

			if (data_idx >= (data->max_data_idx - 1)) { return (-1); }

			data->data[data_idx++] = argv[i];
		}
	}
    data->data[data_idx] = NULL;
	return 0;
}

void ft_get_flags_result(opt_flag *opt_flags, char **single_param)
{

	// --- Zone de Test ---
    printf("--- RÉSULTAT DU PARSING ---\n");
    for (int i = 0; opt_flags[i].info != END_PARAM; i++) {
		if (opt_flags[i].info & ACTIVE) { // Si le flag est actif
            printf("Option [-%c / --%s] active", opt_flags[i].short_flag, opt_flags[i].long_flag);
            if (opt_flags[i].content)
				printf(" avec valeur: %s", opt_flags[i].content);
            printf("\n");
        }
    }
	
    printf("\nArguments restants (single_param) :\n");
    for (int i = 0; single_param[i] != NULL; i++) {
		printf("  single_param[%d] = %s\n", i, single_param[i]);
    }
	
}
 
int main(int argc, char **argv) {

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

	ft_get_flags_result(opt_flags, single_param);

	return 0;
}
