# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 11:51:45 by emimenza          #+#    #+#              #
#    Updated: 2024/02/25 17:46:39 by emimenza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Definir colores
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m # No color (reiniciar)

#Comandos
DEL			=	rm -f
CC			=	gcc
CCFLAGS		=	-Wall -Wextra -Werror  #-03 -pthread  #-g3 -fsanitize=address

# SANITIZER = --tool=helgring

#Nombre ejecutable
NAME		=	philo

#Ficheros
SRC_FILES	=	00_main 01_utils 02_philo 03_free
SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

#Directorios
SRC_DIR = srcs/
OBJ_DIR = objs/
OBJF = objs
INC = incs

# REGLAS # 
all: $(NAME)

#Compilar 
$(NAME):$(OBJ)
		@$(CC) $(OBJ) -o $(NAME) $(SANITIZER)
		@echo "$(GREEN)PHILOSOPHERS HAS BEEN COMPILED!$(NC)"

# Compilar objetos individualmente y crear carpeta objs
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $<$(NC)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADER)
	@echo "$(YELLOW)Compiled!$(NC)"


# $@ : The file name of the target of the rule. If the target is an archive member, then ‘$@’ is the name of the archive file.
# $< : The name of the first prerequisite.

# Eliminar temporales
clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)OBJS AND DIRECTORY CLEANED!$(NC)"

# Eliminar temporales y ejecutable fclean_mlx
fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)EXECUTABLE CLEANED!$(NC)"

re: fclean all