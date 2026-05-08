
#ifndef MAIN_CMD_BIN_H
#define MAIN_CMD_BIN_H

#define ERROR_USAGE "ft_ping: usage error: Adresse de destination requise"
// #define ERROR_USAGE "ft_ping:"
// #define ERROR_USAGE "ft_ping:"
// #define ERROR_USAGE "ft_ping:"


typedef struct main_cmd_bin main_cmd_bin;
typedef enum Level Level;

enum Level {
  HELP,
  ERROR,
  UNDEFINED,
};

struct main_cmd_bin
{
    Level   option;
    char *value;
    main_cmd_bin *next;
};

#endif
