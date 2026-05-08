
.PHONY: all 


###############################################
#               CONFIGURATION                 #
###############################################

NAME        := ft_ping
BINARY_NAME := ft_ping

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -I ./inc
# CFLAGS      := -Weverything -I ./inc

# ── Source .c .h ────────────────────────────────────────────────────────
-include ./mk/source.mk

# Génération de la liste des objets à partir de SRC (défini dans source.mk)
OBJS        := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


# ── Rule ────────────────────────────────────────────────────────────────

# Règle catch-all : capture les arguments pour qu'ils ne soient pas traités comme des cibles
%:
	@:

all: $(NAME)

# Linkage final
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Compilation terminée."

# Compilation des objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ── Test ────────────────────────────────────────────────────────────────
# Récupère tous les arguments après "prog"
ARGS = $(filter-out prog,$(MAKECMDGOALS))

prog: all 
	@./ft_ping $(ARGS)

# ── CLEANING ────────────────────────────────────────────────────────────


.PHONY: clean clear c

clean:
	rm -rf $(OBJ_DIR)
	@echo "✔ objets supprimés"
clear				:	clean
c					:	clean


.PHONY: fclean fclear f
fclean: clean
	rm -f $(NAME) $(BINARY_NAME)
	@echo "✔ tout nettoyé"
fclear				:	fclean
f					:	fclean

.PHONY: re
re: fclean all