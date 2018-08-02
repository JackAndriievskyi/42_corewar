#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yandriie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/26 09:05:32 by yandriie          #+#    #+#              #
#    Updated: 2018/08/01 15:15:10 by yandriie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

GREEN = "\x1b[32m"
MAGENTA = "\x1b[35m"

VM = corewar
ASM = asm

CC = gcc
FLAGS = -Wall -Wextra -Werror

G_SRC_FILES = ops1.c
VM_SRC_FILES = main.c manage_arguments.c parsing.c \
    manage_bot_list.c manage_pc_list.c parse_bot.c \
	parse_bot_id.c display_map.c get_bot_info.c \
    parsing_commands.c ft_get_int.c corewar.c commands.c \
    manage_map.c end_game.c manage_pc_list2.c choose_winner.c \
    print_border.c print_right_window.c \
    ft_and.c ft_fork.c ft_ldi.c ft_lld.c \
    ft_lldi.c ft_load.c ft_or.c ft_st.c \
    ft_sti_dir.c ft_sti.c ft_xor.c \
    ft_xor_dir_ind.c ft_or_dir_ind.c ft_and_dir_ind.c \
    extra_flag.c
ASM_SRC_FILES = main_asm.c \
				utli_asm.c \
				asm_write_uti.c \
				asm_write_uti2.c \
				asm_write_uti3.c \
				buf_handel.c \
				write_this_out.c \
				addition.c \
				addition2.c \
				args_type.c \
				check_code.c \
				comment_check.c \
				ft_split_whitespaces.c \
				label.c \
				name_check.c \
				check_file.c \
				ulti_asm.c

G_HDR_FILES = corewar.h
VM_HDR_FILES = commands.h \
				op.h \
				parsing.h \
				visualization.h \
				vm.h
ASM_HDR_FILES = asm.h \
				asm_write.h \
				oleshche.h

G_SRC_PATH = sources/
VM_SRC_PATH = sources/vm/
ASM_SRC_PATH = sources/asm/
G_SRCS = $(addprefix $(G_SRC_PATH), $(G_SRC_FILES))
VM_SRCS = $(addprefix $(VM_SRC_PATH), $(VM_SRC_FILES))
ASM_SRCS = $(addprefix $(ASM_SRC_PATH), $(ASM_SRC_FILES))

G_OBJ_PATH = objectives/
VM_OBJ_PATH = objectives/vm/
ASM_OBJ_PATH = objectives/asm/
G_OBJS = $(addprefix $(G_OBJ_PATH), $(G_SRC_FILES:.c=.o))
VM_OBJS = $(addprefix $(VM_OBJ_PATH), $(VM_SRC_FILES:.c=.o))
ASM_OBJS = $(addprefix $(ASM_OBJ_PATH), $(ASM_SRC_FILES:.c=.o))

G_HDR_PATH = includes/
VM_HDR_PATH = includes/vm
ASM_HDR_PATH = includes/asm
INCLUDES = -I$(G_HDR_PATH) -I$(VM_HDR_PATH) -I$(ASM_HDR_PATH)
G_HDRS = $(addprefix $(G_HDR_PATH), $(G_HDR_FILES))
VM_HDRS = $(addprefix $(VM_HDR_PATH), $(VM_HDR_FILES))
ASM_HDRS = $(addprefix $(ASM_HDR_PATH), $(ASM_HDR_FILES))

LIB_NAME = libft.a
LIB_PATH = libft/
LIB = $(addprefix $(LIB_PATH), $(LIB_NAME))

all: $(LIB) $(ASM) $(VM)

$(LIB):
	make -C $(LIB_PATH)

lib:
	make -C $(LIB_PATH)

$(G_OBJ_PATH):
	@mkdir -p $(G_OBJ_PATH)

$(VM_OBJ_PATH):
	@mkdir -p $(VM_OBJ_PATH)

$(ASM_OBJ_PATH):
	@mkdir -p $(ASM_OBJ_PATH)

$(ASM): $(LIB) $(G_OBJ_PATH) $(G_OBJS) $(ASM_OBJ_PATH) $(ASM_OBJS)
	@echo $(GREEN)
	$(CC) $(FLAGS) $(LIB) $(ASM_OBJS) $(G_OBJS) -o $@

$(VM): $(LIB) $(G_OBJ_PATH) $(G_OBJS) $(VM_OBJ_PATH) $(VM_OBJS)
	@echo $(GREEN)
	$(CC) $(FLAGS) $(LIB) $(VM_OBJS) $(G_OBJS) -o $@ -lncurses

$(ASM_OBJ_PATH)%.o: $(ASM_SRC_PATH)%.c $(LIB) $(G_HDRS) $(ASM_HDRS)
	@echo $(MAGENTA)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(VM_OBJ_PATH)%.o: $(VM_SRC_PATH)%.c $(LIB) $(G_HDRS) $(VM_HDRS)
	@echo $(MAGENTA)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(G_OBJ_PATH)%.o: $(G_SRC_PATH)%.c $(G_HDRS)
	@echo $(MAGENTA)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIB_PATH) clean
	rm -fdR $(G_OBJ_PATH)

fclean: clean
	rm -f $(ASM) $(VM) $(LIB)

re: fclean all