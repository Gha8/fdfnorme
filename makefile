SRC_DIR=./src/
NAME=mlx_test
OBJ=$(SRC_DIR)0_main.o $(SRC_DIR)0_parsing.c $(SRC_DIR)0_house_keeping.o $(SRC_DIR)0_init.o $(SRC_DIR)1_input.o $(SRC_DIR)2_update_position.o $(SRC_DIR)3_draw.o
MLX=libmlx_Linux.a 
CFLAGS=-lXrandr -lXinerama -lXfixes -lXi -lbsd -lXrender -lXdmcp -lm -lz 
CPPFLAGS=-Wall -Wextra -Werror -g3 

all: $(NAME)
$(NAME) :$(MLX) $(OBJ)
	cc $(OBJ) -L. libmlx_Linux.a -lX11 -lXext $(CFLAGS) -o $(NAME)
clean:	
	rm -f $(SRC_DIR)*.o
fclean:
	rm $(NAME)
	rm *.a
re : clean all

$(MLX):
	git clone https://github.com/42Paris/minilibx-linux.git mlx_temp
	cp -r mlx_temp/* .
	rm -rf mlx_temp
	cp ./mlx.h ./src/mlx.h
	./configure

#############
## PATERNS ##
#############
#$@: Nom de la regle
#$<: Nom de la premiere dépendance
#$^: Nom de la toute les dependances
%.o: %.c
	cc $(CPPFLAGS) -c $< -o $@
.PHONY: all clean fclean re
