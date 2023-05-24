# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 15:12:37 by tale-fau          #+#    #+#              #
#    Updated: 2022/02/28 15:06:11 by tale-fau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[0;91m
GREEN = \033[0;92m
BLUE = \033[0;34m
WHITE = \x1b[0m
COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

BIN_STRING  = Binary
DEL_STRING = Deleted.
CREA_STRING = Created.
COM_STRING = Compiled.
BINARY = $(NAME)

NAME	        =		minishell

SRCS_DIR		=		./srcs

SRCS            =       ${SRCS_DIR}/main.c\
						${SRCS_DIR}/error/error.c\
						${SRCS_DIR}/functions/ft_split.c\
						${SRCS_DIR}/functions/ft_bzero.c\
						${SRCS_DIR}/functions/ft_strcat_or_strcpy.c\
						${SRCS_DIR}/functions/utils.c\
						${SRCS_DIR}/parsing/read_from_stdin.c\
						${SRCS_DIR}/parsing/parsing.c\
						${SRCS_DIR}/parsing/prompt.c\
						${SRCS_DIR}/parsing/parse_pipes.c\
						${SRCS_DIR}/parsing/parse_pipes_utils.c\
						${SRCS_DIR}/parsing/parse_pipes_utils2.c\
						${SRCS_DIR}/parsing/token/pre_tokenizer.c\
						${SRCS_DIR}/parsing/token/tokenizer.c\
						${SRCS_DIR}/parsing/token/post_tokenizer_utils.c\
						${SRCS_DIR}/parsing/token/post_tokenizer.c\
						${SRCS_DIR}/parsing/token/tokenizer_utils.c\
						${SRCS_DIR}/parsing/token/tokenizer_utils2.c\
						${SRCS_DIR}/parsing/token/tokenizer_utils3.c\
						${SRCS_DIR}/parsing/quotes/verif_quotes.c\
						${SRCS_DIR}/parsing/quotes/t_quotes_utils.c\
						${SRCS_DIR}/parsing/quotes/utils_quotes.c\
						${SRCS_DIR}/parsing/quotes/joins.c\
						${SRCS_DIR}/parsing/quotes/remove_quotes.c\
						${SRCS_DIR}/parsing/quotes/free_node.c\
						${SRCS_DIR}/lists_utils/list_utils.c \
						${SRCS_DIR}/lists_utils/list_utils2.c\
						${SRCS_DIR}/lists_utils/list_utils3.c\
						${SRCS_DIR}/environement/env.c\
						${SRCS_DIR}/environement/env_utils.c\
						${SRCS_DIR}/environement/env_utils2.c\
						${SRCS_DIR}/environement/copy_env.c\
						${SRCS_DIR}/execution/builtins.c\
						${SRCS_DIR}/execution/exec_builtins.c\
						${SRCS_DIR}/execution/builtins_utils.c\
						${SRCS_DIR}/execution/builtins_utils2.c\
						${SRCS_DIR}/execution/builtins_utils3.c\
						${SRCS_DIR}/execution/builtins_utils4.c\
						${SRCS_DIR}/execution/builtins_utils5.c\
						${SRCS_DIR}/execution/status_variable.c\
						${SRCS_DIR}/execution/cd.c\
						${SRCS_DIR}/execution/cd2.c\
						${SRCS_DIR}/execution/pwd.c\
						${SRCS_DIR}/execution/echo.c\
						${SRCS_DIR}/execution/echo_utils.c\
						${SRCS_DIR}/execution/exit.c\
						${SRCS_DIR}/execution/unset.c\
						${SRCS_DIR}/execution/unset_utils.c\
						${SRCS_DIR}/execution/export.c\
						${SRCS_DIR}/execution/export_utils.c\
						${SRCS_DIR}/execution/sort_env.c\
						${SRCS_DIR}/execution/redirections.c\
						${SRCS_DIR}/execution/redirections_utils.c\
						${SRCS_DIR}/execution/heredoc.c\
						${SRCS_DIR}/execution/heredoc_expand.c\
						${SRCS_DIR}/execution/heredoc_utils.c\
						${SRCS_DIR}/execution/close_or_transfer_fd.c\
						${SRCS_DIR}/parsing/cloning.c\
						${SRCS_DIR}/parsing/parsing_utils.c\
						${SRCS_DIR}/lists_utils/list_utils_token.c\
						${SRCS_DIR}/lists_utils/list_utils_token2.c\
						${SRCS_DIR}/nodes/nodes.c\
						${SRCS_DIR}/nodes/nodes_utils.c\
						${SRCS_DIR}/nodes/option_filler.c\
						${SRCS_DIR}/nodes/cmd_filler.c\
						${SRCS_DIR}/nodes/arg_filler.c\
						${SRCS_DIR}/nodes/filler_utils.c\
						${SRCS_DIR}/nodes/redirection_filler.c\
						${SRCS_DIR}/nodes/check_redir.c\
						${SRCS_DIR}/nodes/redirection_filler_utils.c\
						${SRCS_DIR}/dollar/dollar.c\
						${SRCS_DIR}/dollar/dollar2.c\
						${SRCS_DIR}/dollar/dollar3.c\
						${SRCS_DIR}/dollar/dollar_utils.c\
						${SRCS_DIR}/dollar/dollar_utils2.c\
						${SRCS_DIR}/dollar/utils.c\
						${SRCS_DIR}/dollar/split_keep_sep.c\
						${SRCS_DIR}/dollar/lonely_token.c\
						${SRCS_DIR}/signal/signals.c\
						${SRCS_DIR}/signal/signal_heredoc.c

INCLUDES_DIR     =       includes/

LIB_DIR         =       libft/

LIBFT           =       libft/libft.a

CC              =       gcc

OBJS            =       ${SRCS:.c=.o}

RM          =       	rm -rf

FLAGS       =      		-Wall -Wextra -Werror

READLINE	=			srcs/readline/libreadline.a
 
.c.o: 
					@${CC} ${FLAGS} -I${INCLUDES_DIR} -c $< -o ${<:.c=.o}
					@printf "%-20b%-60b%b" "$(BINARY):" "$(GREEN)$@" "$(CREA_STRING)$(RESET)\r"

all:			${NAME}
 
${NAME}:		${OBJS}
						@make -C ${LIB_DIR} 2>/dev/null
						@${CC} ${FLAGS} -I${INCLUDES_DIR} -lncurses -o ${NAME} ${OBJS} ${LIBFT} ${READLINE}
						@printf "%-20b%-60b%b" "$(BINARY):" "$(GREEN)$(BIN_STRING)" "$(COM_STRING)$(RESET)\n"

clean:
						@make -C ${LIB_DIR} clean
						@${RM} ${OBJS} ${OBJS_B}
						@printf "%-20b%-60b%b" "$(BINARY):" "$(RED)$(OBJS_PATH)" "$(DEL_STRING)$(RESET)\n"

fclean:		clean
						@make -C ${LIB_DIR} fclean
						@${RM} ${NAME} ${NAME_B}
						@printf "%-20b%-60b%b" "$(BINARY):" "$(RED)$(BIN_STRING)" "$(DEL_STRING)$(RESET)\n"

re:		fclean all

.PHONY:           all     clean   fclean  re
