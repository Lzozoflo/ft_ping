

#include <stdio.h>          // dprintf
#include <string.h>         // 
#include "ft_get_opt.h"


static int	ft_get_short_flag(opt_flag *opt_flags, char c, char **argv)
{
	size_t		i;

	i = -1;
	while (opt_flags[++i].info != END_PARAM) {

		if (opt_flags[i].short_flag == c) {

			opt_flags[i].info += ACTIVE;

			if (opt_flags[i].info == WITH_PARAM) {
				// printf("short_flag: -%c <argv: %s>\n", opt_flags[i].short_flag, argv[1]);
				opt_flags[i].content = argv[1];
				return (1);
			}
			// printf("short_flag: -%c\n", opt_flags[i].short_flag);
			return (0);
		}
		printf("-%c cmp to -%c\n", c, opt_flags[i].short_flag);
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
	size_t	i;

	i = -1;

	while (opt_flags[++i].info != END_PARAM) {

		if (!ft_strcmp(opt, opt_flags[i].long_flag)) {
			
			opt_flags[i].info += ACTIVE;

			if (opt_flags[i].info == WITH_PARAM) {
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

int		ft_get_flags(int argc, char **argv, opt_flag *opt_flags, char **data)
{
	int		i;

	i = 0;
	if (!opt_flags || !argv)
		return 1;
	while (++i < argc) {

		if (!ft_strncmp(argv[i], "--", 2)){

			i += ft_get_long_flag(opt_flags, &argv[i][2], &argv[i]);
		
		} else if (argv[i][0] == '-') {

			if (strlen(argv[i]) != 2) { return -1; }

			i += ft_get_short_flag(opt_flags, argv[i][1], &argv[i]);
		} 
		// else if (){ // le reste

		// 	data = argv[i];
		// }
	}
	return 0;
}

int main(int argc, char **argv){

	opt_flag opt_flags[] = {
	 // { info, 	  short, long,		   content },
        { NO_PARAM, 	'v', "verbose",    NULL },
        { NO_PARAM, 	'h', "help",       NULL },
        { WITH_PARAM, 	'f', "file",       NULL },
        { END_PARAM, 	0, NULL,        NULL },
    };
	char *data[4];


	if (ft_get_flags(argc, argv, opt_flags, data)){
		return 1;
	}

	return 0;
}