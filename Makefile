
.PHONY: all 


###############################################
#               CONFIGURATION                 #
###############################################

NAME        := ft_ping
BINARY_NAME := ft_ping

CC          := cc
# CFLAGS      := -Wall -Wextra -Werror -I ./inc
# CFLAGS      := -Weverything -I ./inc

# ── Source .c .h ────────────────────────────────────────────────────────
-include ./mk/source.mk

# Génération de la liste des objets à partir de SRC (défini dans source.mk)
OBJS        := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


# ── Rule ────────────────────────────────────────────────────────────────


all: $(NAME)

# Linkage final
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compilation des objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ── Test ────────────────────────────────────────────────────────────────

vtest: all
	$(CC) $(CFLAGS) -g3 $(MAIN) $(NAME) -o $(BINARY_NAME)

	@if [ -z "$(ARG0)" ]; then \
		echo "❌ ARG est vide, veuillez fournir un argument."; \
		exit 42; \
	else \
		echo "-----------------------------------------------------------------------------";\
		echo "✔ exécutable créé et lancé avec : ./$(BINARY_NAME) [$(ARG0)] [$(ARG1)] [$(ARG2)] [$(ARG3)] [$(ARG4)] [$(ARG5)]"; \
		valgrind --leak-check=full --show-leak-kinds=all --show-mismatched-frees=yes --track-fds=yes --trace-children=yes ./$(BINARY_NAME) $(ARG0) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5); \
	fi

	@rm -rf $(OBJ_DIR)
	@rm $(BINARY_NAME)


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