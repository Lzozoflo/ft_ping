
#ifndef FT_GET_OPT_H
#define FT_GET_OPT_H

#define LONG_FLAG       1<<1
#define SHORT_FLAG      1<<2

// info
#define NO_PARAM        0
#define WITH_PARAM      1<<1
#define ACTIVE          1<<2
#define END_PARAM       1<<3

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
 

#endif

