#libft
LIBFTDIR = ./Libft/
LIBFTLIB = ft
LIBFTFLAGS = -L$(LIBFTDIR) -l$(LIBFTLIB)

#readline
LIBRDLINE = -lreadline

#common
COMMONDIR = ./common
COMMON_SRC = $(COMMONDIR)/common.c\
			$(COMMONDIR)/env_lst_util.c\
			$(COMMONDIR)/cleaning.c

#history
HISTORY_FILE = ".minishell_history"
HISTORY_CREAT_FILE = touch $(HISTORY_FILE)
HISTORY_CLEAN = rm -f $(HISTORY_FILE)
HISTORYDIR = ./history
HISTORY_SRC = $(HISTORYDIR)/ft_history.c

#parsing
PARSERDIR = ./parsing
PARSER_SRC = $(PARSERDIR)/splite_tokens_util.c\
			$(PARSERDIR)/split_pipes_util.c\
			$(PARSERDIR)/split_pipes.c\
			$(PARSERDIR)/splite_tokens.c\
			$(PARSERDIR)/parsing_utils.c\
			$(PARSERDIR)/parsing.c\
			$(PARSERDIR)/free_parsing.c\
			$(PARSERDIR)/dollar_pars.c\
			$(PARSERDIR)/dollar_pars_util.c\
			$(PARSERDIR)/pars_redirects.c\
			$(PARSERDIR)/heredoc.c\
			$(PARSERDIR)/dollar_pars_herdoc.c\
			$(PARSERDIR)/removing_quot.c			

#executor
EXECUTORDIR = ./executor
EXECUTOR_SRC = $(EXECUTORDIR)/executor.c\
			$(EXECUTORDIR)/process_manage.c\
			$(EXECUTORDIR)/redirect_manage.c\
			$(EXECUTORDIR)/cmd_path_param.c

#singnals
SIGNALSDIR = ./signals
SIGNALS_SRC = $(SIGNALSDIR)/ft_handle_signals.c\
			$(SIGNALSDIR)/signal_def_proc.c

#builtins
BUILTINSDIR = ./builtins
BUILTINS_SRC = $(BUILTINSDIR)/builtins.c\
			$(BUILTINSDIR)/builtins_error.c\
			$(BUILTINSDIR)/builtins_tools1.c\
			$(BUILTINSDIR)/builtins_env.c\
			$(BUILTINSDIR)/builtins_tools.c\
			$(BUILTINSDIR)/builtins_exit.c\
			$(BUILTINSDIR)/builtins_export.c\
			$(BUILTINSDIR)/builtins_cd.c\
			$(BUILTINSDIR)/builtins_cmd.c

#minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0 -gdwarf-4
SRC = $(HISTORY_SRC) $(COMMON_SRC) $(PARSER_SRC) $(EXECUTOR_SRC) $(BUILTINS_SRC) $(SIGNALS_SRC) minishell.c

OBJ = $(SRC:.c=.o)
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ)
	$(HISTORY_CREAT_FILE)
	make bonus -C $(LIBFTDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBRDLINE) $(LIBFTFLAGS)

%.o : %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean :
	make clean -C $(LIBFTDIR)
	rm -f $(OBJ)

fclean : clean
	$(HISTORY_CLEAN)
	make fclean -C $(LIBFTDIR)
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
