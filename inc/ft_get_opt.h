
#ifndef FT_GET_OPT_H
#define FT_GET_OPT_H

// info
#define NO_PARAM        (1 << 0)  // 000001 (1)
#define WITH_PARAM      (1 << 1)  // 000010 (2)
#define ACTIVE          (1 << 2)  // 000100 (4)
#define END_PARAM       (1 << 3)  // 001000 (8)

typedef struct opt_data     opt_data;
typedef struct opt_flag     opt_flag;

struct opt_data
{
    opt_flag    *opt_flags;
    char        **data;
    int         max_data_idx;
};


/*
    struct opt_flag opt_flags[] = 
        { "-v", "--verbose",    0 },
        { "-h", "--help",       0 },
        { "-f", "--file",       WITH_PARAM },

*/
struct opt_flag
{
    char info;        // WITH_PARAM
    char short_flag;  // SHORT_FLAG <-v>
    char *long_flag;  // LONG_FLAG  <--verbose>
    char *content;
};
 
int		ft_get_flags(int argc, char **argv, opt_data *data);
void ft_get_flags_result(opt_flag *opt_flags, char **single_param);

#endif

