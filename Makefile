# Name of the executable
NAME = cub3D

# Compiler
CC = gcc 
# gcc -g -o so_long so_long.c
# Compiler flags
#CFLAGS = -Wall -Wextra -Werror -Wno-unused-but-set-variable -Wno-unused-const-variable -Wno-unused-parameter -Wno-unused-variable -Wno-sign-compare
CFLAGS := -Wall -Wextra -Werror -g -MMD -MP
# Include paths for header files
H_PATH := -I.

# Library paths
LIB_PATH := -L./libft -L./minilibx

# Libraries to link against, including the math library if needed
LDLIBS := -lft -lmlx -framework OpenGL -framework AppKit -lm

LFT = libft/libft.a
MFT = minilibx/libmlx.a
# Source files
SRC = main.c \
	  src/utils/checks.c \
	  src/utils/init.c \
	  src/utils/utils.c \
	  src/parsing/set_specs.c \
	  src/parsing/set_map.c \
	  src/utils/printing_checks.c \
	  src/utils/clean_exit.c \
	  src/utils/check_map.c \
	  src/render/render.c \
	  src/utils/rgb_to_hex.c \
	  src/render/move.c

DODIR = dofile

# Define object files (define, not generate)
OBJ = $(patsubst %.c,$(DODIR)/%.o,$(SRC))
# Define dependency files (define, not generate)
DEP = $(patsubst %.o,%.d,$(OBJ))


# Default target
all: $(NAME)

#include dependency files: SHOULD BE PLACED AFTER DEFAULT TARGET!
-include $(DEP)

# Rule to link the program
$(NAME): $(OBJ) $(LFT) $(MFT)
	$(CC) $(OBJ) $(LIB_PATH) $(LDLIBS) -o $(NAME)

# Rule to compile source files into object files, d files are generated as well at the same time when -MMD is included
$(OBJ): $(DODIR)/%.o: %.c | $(DODIR)
	@mkdir -p $(dir $@)	
	$(CC) $(CFLAGS) $(H_PATH) -c $< -o $@ -MF $(DODIR)/$*.d

# rule to create the diretories. -p makes sure that if they exist already, nothing will be done
$(DODIR):
	mkdir -p $@

$(LFT):
	make -C libft all
	make -C minilibx all

# Rule to clean object files and other temporary files
clean:
	rm -f $(OBJ) $(DEP)
	make -C libft clean
	make -C minilibx clean

# Rule to fully clean the project, including the executable
fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	make -C minilibx fclean

# Rule to re-make the project
re: fclean all

# Phony targets for make commands
.PHONY: all clean fclean re