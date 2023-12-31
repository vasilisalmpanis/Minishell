NAME = minishell
SRC =	mandatory/main.c \
		mandatory/prompt/prompt.c \
		mandatory/signals/signals.c\
		mandatory/utils/utils.c \
		mandatory/utils/free_utils1.c \
		mandatory/utils/free_utils2.c \
		mandatory/utils/env_dict.c \
		mandatory/utils/env_dict_helper.c \
		mandatory/utils/redir_spaces.c \
		mandatory/utils/redir_spaces_utils.c \
		mandatory/utils/cmd_lst_utils.c \
		mandatory/utils/cmd_lst_utils2.c \
		mandatory/utils/lex_lst_utils.c \
		mandatory/lexer/lexer.c \
		mandatory/lexer/expansion.c \
		mandatory/lexer/expansion_utils.c \
		mandatory/lexer/create_exp_var.c \
		mandatory/builtins/env.c \
		mandatory/builtins/export.c \
		mandatory/builtins/export_print.c \
		mandatory/builtins/pwd.c \
		mandatory/builtins/cd.c \
		mandatory/builtins/echo.c \
		mandatory/builtins/unset.c \
		mandatory/builtins/exit.c \
		mandatory/parser/parse.c \
		mandatory/parser/analyze_word.c \
		mandatory/parser/analyze_cmd_utils.c \
		mandatory/parser/analyze_redir.c \
		mandatory/executor/execute.c \
		mandatory/executor/executor_utils1.c \
		mandatory/executor/executor_utils2.c \
		mandatory/executor/open_files.c \
		mandatory/executor/open_heredoc.c \
		mandatory/executor/set_stdin_stdout.c \
		mandatory/executor/errors.c


LIBFT = ./libft
RM = rm -rf
CC = gcc
CFLAGS = -g -Wall -Wextra
OBJ = $(SRC:.c=.o)
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
PINK = \033[95m
END = \033[0m
MAKE = make

UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
    LIBREADLINE_FLAGS = -lreadline -lhistory
else ifeq ($(UNAME),Darwin)
    LIBREADLINE_FLAGS = -I${READLINE_PATH}/include -L${READLINE_PATH}/lib -lreadline -lhistory -ltermcap
endif

READLINE_PATH = ${PWD}/readline

all: ${LIBFT} ${NAME}

${NAME}: ${OBJ} ${LIBFT}
	@$(CC) ${CFLAGS} $(OBJ) -o $(NAME) libft.a $(LIBREADLINE_FLAGS)
	@${RM} libft.a
	@echo "${RED}${NAME} completed${END}"

${LIBFT}:
	@make -q -C libft || make -C libft
	@cp ${LIBFT}/libft.a .
	@echo "${GREEN}libft completed\n${END}"

%.o: %.c
	${CC} ${CFLAGS} -I./readline -I./libft -c $< -o $@

norm:
	@norminette mandatory > /tmp/norminette_output.txt 2>&1
	@norminette includes > /tmp/norminette_output.txt 2>&1
	@norminette libft > /tmp/norminette_output.txt 2>&1
	@rm -rf /tmp/norminette_output.txt
	@echo "${BLUE}\nnorminette completed\n${END}"

test:
	@if [ -e "minishell" ]; then \
		cd .minishell_tester; \
		./tester; \
	else \
		echo "${PINK}Make first${END}"; \
	fi

clean:
	@make clean -C libft
	@${RM} mandatory/libft.a
	@${RM} ${OBJ}
	@echo "${RED}Clean completed${END}"

fclean: clean
	@echo ""
	@${RM} ${NAME}
	@make fclean -C libft
	@echo "${RED}Fclean completed${END}"

space:
	@echo ""

re: fclean all

.PHONY: all clean fclean re ${LIBFT}
