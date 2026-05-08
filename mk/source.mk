

# ── Dicretories ──────────────────────────────────────────

# Sub Directories

SRC_DIR     := src
OBJ_DIR     := .obj

# for a new DIR add a new :
# NEW_DIR			:=		new/




# ── Source ──────────────────────────────────────────────


SRC		+= main.c
SRC		+= file.c
# SRC		+=


# for a new SRC add a new :
# SRC_NEW				:=



# Every now src_dir add a addprifix like that :
#	$(addprefix $(NEW_DIR), $(SRC_NEW))