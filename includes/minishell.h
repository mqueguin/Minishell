/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:36:04 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 15:19:26 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"

# define SUCCESS 0
# define FAILURE 1
# define ERROR -1
# define ENDOFCOMMAND '\n'
# define PIPE '|'
# define SPACE ' '
# define ZERO '\0'
# define DASH '-'
# define BACKSLASH '\\'
# define SEMICOLON ';'
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'
# define RIGHT_ARROW '>'
# define DOUBLE_RIGHT_ARROW ">>"
# define LEFT_ARROW '<'
# define DOUBLE_LEFT_ARROW "<<"
# define DOLLAR '$'
# define SPE_QUOTE '`'
# define BGRN "\e[1;32m"
# define BRED "\e[1;31m"
# define BYEL "\e[1;33m"
# define BLK "\x1b[0m"
# define REDIR 39
# define SGL_Q 40
# define DBL_Q 41
# define PIPE_ID 42
# define LEFT_ARR 43
# define DBL_LEFT_ARR 44
# define RIGHT_ARR 45
# define DBL_RIGHT_ARR 46
# define CMD 47
# define OPTION 48
# define ARG 49

typedef struct s_data
{
	char			*sep_tab;
	char			buf[1000];
	int				i;
	int				j;
	int				is_quote;
	int				sep_id;
}	t_data;

typedef struct s_file
{
	char			*path;
	int				type;
	int				fd;
	int				quote;
	int				pipes[2];
	char			*heredoc_filename;
	struct s_file	*next;
}				t_file;

typedef struct s_node
{
	char			*cmd;
	char			*option;
	char			**arg;
	int				pipe;
	int				fd[2];
	int				fdhere;
	int				pid;
	int				question_mark;
	struct s_file	*file;
	int				nb_redirections;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

/* Liste qui contient la variable d'environnement */
typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}				t_env;

typedef struct s_quotes
{
	char			*str;
	struct s_quotes	*next;
}				t_quotes;

typedef struct s_token
{
	char			*content;
	int				id;
	int				pipe_in_quote;
	int				space;
	int				question_mark;
	int				quote;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_list_token
{
	size_t	len2;
	t_token	*front;
	t_token	*back;
}	t_list_token;

typedef struct s_list
{
	size_t	len;
	t_node	*head;
	t_node	*tail;
}	t_list;

/* ------------- VARIABLE GLOBALE === Statut de retour ---------------*/

char	*g_status;

/* ------------------------------------------------------------------ */

int				return_status_success(void);

/* Fonctions a trier */
int				read_from_stdin(char *prompt, t_env *env);

/* Prompt functions */
char			*set_prompt(t_env *env);
char			*display_prompt(char *prompt, t_env *env);

/* Error management */
int				error(int id);
int				bad_command_return(char	*str);
t_env			*error_malloc_t_env(t_env *env, int i);
char			*error_malloc_char(void);

/* List utility functions s_node */
t_list			*add_head(t_list *t_list_node);
t_list			*add_tail(t_list *t_list_node);
t_list			*init_list(t_node *node, t_list *t_list_node);
t_node			*init_node(t_node *node);
t_list			*list_del_head(t_list *t_list_node);
t_list			*list_del_tail(t_list *t_list_node);
t_list			*clear_list(t_list *t_list_node);
int				is_empty_list(t_list *t_list_node);
int				list_length(t_list *t_list_node);
void			create_redirection_node(t_node *node, char *file_name,
					int type, int is_quote);
void			free_token(t_token *to_free);

/* List utility functions s_token */
t_list_token	*add_front(t_list_token *ls_token);
t_list_token	*add_back(t_list_token *ls_token);
t_list_token	*init_list_token(t_token *node, t_list_token *ls_token);
t_token			*init_node_token(t_token *node);
t_list_token	*list_del_front(t_list_token *ls_token);
t_list_token	*list_del_back(t_list_token *ls_token);
t_list_token	*clear_list_token(t_list_token *ls_token);
int				is_empty_list_token(t_list_token *ls_token);	
int				list_length_token(t_list_token *ls_token);
t_token			*del_token(t_list_token *ls_token, t_token *tmp);
int				is_empty_and_single_token(t_list_token *ls_token);

/* Signals */
int				handle_signal(void);
void			rl_replace_line(const char *line, int r);
int				disable_signal(int pid);
void			interrupt_heredoc(int sig);
void			interruption_signal(int sig);
void			set_sig(void (*sig_handler)(int), int sig);
void			ignore_sig(int sig);
void			handle_signals_heredoc(int sig);

/* Pre parsing (cloning) */
char			*cloning(char *line);
int				parse_pipes(char *str, int i, int len, int *len_pipes);
int				*check_number_of_pipe_into_quotes(char *str,
					int number_pipes, int i);
int				check_if_there_are_any_quotes(char *str, int i, int b_is_quote);
int				search_for_quotes(char *line);

/* Tokenizer */
t_list_token	*init_read_through_str(char *str, t_list_token *ls_token);
int				reading_loop(char *str, t_token *token, t_list_token *ls_token);
void			init_reading_variables(int *is_quote, int *d_quote);
int				is_sep(char *sep, char c, int *is_quote);
void			assign_is_quotes(int *quote);
int				fill_content(char *buf, t_token *tok, char *str,
					t_list_token *l);
void			fill_id(t_token *token);
int				ft_bzero(void *s, size_t n);
char			*check_quotes_in_token(char *content, int b_single_or_double,
					int i, int j);
int				fill_buffer_and_check_multiple_dollar(t_data *data, char *str);
char			*free_dup_content(char *buf, char **content);
int				ft_assign_value_for_var_is_quote(t_data data, char *str);
int				ft_tokenizer_error(int err);
int				token_handler(t_list_token *ls_token);
t_token			*create_token_with_quote(char **str, int state);
t_token			*create_token_without_quote(char **str, int state);
void			connect_by_state(t_list_token *ls_token, t_token *new,
					t_token *token, int state);
void			connect_last_token(t_list_token *ls_token, t_token *new,
					t_token *next);
int				good_argums(char *new_token_address);
int				good_arguments(char *new_token_address);
int				content_null_or_not(t_token *token, t_data *data,
					t_list_token *ls_token, char *str);

/* Parsing */
int				parsing(char *line, t_env **env);
char			*cut_line(char *str);
int				gnl(char **line, int fd);
int				skip_spaces(char *line);
char			**ft_split(char const *str, char c);
char			*break_tab(char **tab);
int				is_envp_empty(t_env *env);
int				find_unspecified_special_char(char *line);
void			ft_init_data(t_data *data);
int				ft_check_is_sep(char *str, t_data *data);
int				ft_fill_sep_next_part(t_data *data, t_token *token,
					char *str, t_list_token *ls_token);
void			ft_loop_for_search_quotes(char *str, int *copy_i,
					int b_is_quote);

/* Quotes */
char			*manage_quotes(char *str);
t_quotes		*verif_quotes_in_token(t_quotes *node, char *str, int i, int j);
t_quotes		*create_node_quote(void);
int				stop_writing(char c, char *stop);
char			*define_stop(int state);
int				define_state(char c, int state);
int				which_quote(char c, int state);
char			*remove_single_quotes(char *str, int i, int j);
char			*remove_double_quotes(char *str, int i, int j);
char			*need_to_remove_quotes(char *content);
int				get_len(t_quotes *node);
char			*join_nodes_in_tab(t_quotes *node);
char			*join_tab_in_ret(char **tab);
char			**dup_quotes_nodes_into_tab(t_quotes *node, int len);
size_t			get_total_len(t_quotes *node);
int				is_quote_inside(char *str);
int				ft_fill_sep(t_data *data, t_token *token,
					char *str, t_list_token *ls_token);
int				check_and_return(int *index, int *i, char *str, int b_is_quote);
int				ft_is_quote_token(char quote);

t_list_token	*manage_redirect(t_list_token *ls_token, t_list *t_list_node);

/* Nodes */
void			display_list(t_list_token *ls_token);
void			dis_list(t_list *t_list_node);
t_node			*assign_token_to_node(t_node *nd, t_token **tk, int *j);
char			*filler(char *src);
t_token			*option_filler(t_token *token, char **ret, int **i);
t_token			*cmd_filler(t_token *token, char **ret, int **i);
t_token			*arg_filler(t_token *token, char ***arg);
char			*ft_strcat_quote(char *s1, char *s2, int quote);
char			**malloc_arg_and_return(int len);
char			*malloc_and_return(int len);
t_list			*manage_nodes(t_list_token *ls_token, t_list *t_list_node);
int				check_content(t_token *token);
t_node			*error_check(void);
char			*filler(char *src);
char			*ft_strdup_without_quotes(char *str);
int				ft_strlen_without_quotes(char *s);
int				count_quotes(char *str);
t_token			*ft_check_redirection(t_token *token, t_node **node,
					int *ret, t_list *ls);

/* Execution */
/* Creation of token */
int				analyse_entry_line(char *line);

/* Dollar management */
t_list_token	*manage_dollar(t_env *env, t_list_token *ls_tk);
char			*split_and_send_to_replace(t_env *env, char *str,
					int count);
char			*lets_go_for_an_other_split(t_env *env,
					char *str, int count);
int				are_there_multiple_dollar_sign(char *str);
char			*join_tab_and_return(char **tab, int count);
char			*replace_dol(t_env *env, char *tab, int j, int k);
int				fill_buffer_with_env_var(char *buf, char c, int *k, int *j);
char			*find_equivalent_with_name(t_env *env, char *str);
int				is_separator(char c);
int				check_dollar(char *str);
int				strncmp_for_dollar(char *s1, char *s2, int len1);
t_env			*find_index_in_env(t_env *env, int *j, char *str);
void			find_index_unset(t_env **env, char *str);
char			**ft_split_not_erase_sep(char *str, int i, int j);
char			**check_for_empty_arg(char **args, int len, int j, int count);
t_token			*find_empty_token(t_list_token *ls_tk);
int				is_there_dollar_question_mark(char *str);
char			*transform_question_mark(char *str);
void			change_status(char *status);
t_list_token	*lonely_token(t_list_token *ls_tk, t_token *token, t_env *env);
char			*handle_dollar(char *str, t_env *env);
char			*if_single_quote(t_token *token);
t_token			*multiple_tokens(t_token *token, t_env *env);
int				ft_check_dollar(char *content);

/* Execution */
int				ft_start_execution(t_env **env, t_list *t_list_node, int ret);
char			*ft_strcpy(char *dst, char *src);
int				is_not_builtin(t_node *node, int ret, char **path, t_env *env);
char			*loop_on_pathbin(char **pbin, t_node *node, char **str, int i);
char			*concat_path_with_cmd(char *pathbin, char *cmd);
char			*recover_pathbin(t_node *node, t_env *env, int j, char *str);
char			*ft_strdup_with_node(t_node *node);
int				ft_check_if_cmd_content_slash(char *cmd);
char			**create_envp(t_env *env, int i, int size_env);
int				cmd_env(t_env *env);
t_env			*body_env_function(char *arg, t_env *env,
					t_env *copy_env, t_env *tmp);
void			ft_display_env(t_env *env);
t_env			*add_new_var_to_copy_env(t_env *env, t_env *copy_env,
					t_env *tmp, char **tab);
char			*loop_and_join(int i, char **tab, char *str);
void			check_and_change_option(t_node **node);
int				ft_error_env(int err, char *msg);
char			**ft_mini_split(char *str, char c);
char			*ft_strjoin_free_str(char *s1, char *s2, int b_free, int i);
int				cmd_cd(t_env *env, int fork, t_node *node);
int				ft_error_cd(char *str, int b_err);
int				change_pwd_env(t_env *env, char *new_path, char *old_path);
int				exec_builtins_no_pipe(t_node *node, char **envp, int i, int j);
t_env			*recover_index_path(t_env *env, int *j, char *str);
char			*concat_cmd_opt_args(char *str, t_node *node);
char			*ft_strcat_exec(char *s1, char *s2);
char			*concatenation_builtins_for_execve(char *str, char *path,
					t_node *node);
int				cmd_compare(t_env **env, t_node *node, int fork, int select);
int				cmd_pwd(t_env *env);
int				cmd_echo(t_node *node);
char			*find_wrong_option(t_node *node, int *count);
int				contains_bad_char(char *str);
int				cmd_exit(t_env *env, t_node *node, int fork, int i);
int				cmd_unset(t_node *node, t_env **env, int i, int fork);
int				cmd_export(t_node *node, t_env **env, int fork, int i);
int				ft_search_equal_char(char *str);
int				ft_print_env_sorted(t_env *env, int fork);
char			*ft_strcpy2(char *s1, char *s2);
char			**ft_sort_env(t_env *copy);
int				suite(int fork, char *arg);
int				ft_check_is_alpha_or_num(char c, char *arg, int y, int fork);
int				ft_check_args_is_valid(char *arg, int fork);
int				ft_check_args(char *str, int fork, int i, int j);
void			with_good_args(char *str, t_env **env);
int				ft_strcmp(char *s1, char *s2);
int				is_builtin(char *cmd);
int				ft_error_exec(int ret, char *cmd, int fork);
int				ft_error_execve(int err, char *msg);
int				ft_dollar_interogation(t_node *node, char *ret_status, int i);
char			*ft_strcat_true(char *dst, char *src);
char			**ft_translate_in_tab2d(t_node *node, char *str,
					char **path, int index[2]);
char			**tab2d_return_null(void);
char			**ft_search_and_replace(char **option);
int				close_pipe(t_node *node);
char			*create_file_name_heredoc(char *name);
t_node			*ft_close_or_transfer_fd(t_node *node, int new_fd[2]);
int				ft_check_if_heredoc(t_node *node, t_env *env, int ret);
void			wait_function(int pid);
char			*ft_loop_expand(char *line, int count, char *ret, t_env *env);
int				ft_heredoc(t_file *file, t_env *env);
void			heredoc_loop(t_file *file, t_env *env);
char			*ft_strjoin_one_char(char *s1, char c);
char			*malloc_into_line(int size);
char			*fill_cmd(char *node_str, char *str, int *size, int i);
int				*ft_get_size_cmd(char *str, char *node_str, int i, int j);
char			*ft_fill_cmd_or_opt_or_args(char *node_str, char *str,
					int b_cmd_or_opt);

int				execution_cmd(t_node *node, char **envp, int *fd, char *path);
char			**strcpy_tab2d(char **tab);

int				start_fork_before_exec(t_node *node, char *path, t_env **env);
int				ft_redirection(t_node *node);
int				dup2_then_close(t_file *file);
int				dup2_then_close_the_sequel(t_file *file);
int				return_error_no_file(t_file *file);
int				return_error_eacces(t_file *file);

t_env			*create_node_env(char *str, int shlvl);
int				next_token_is_ok(t_token *token);
int				unexpected_quote_token(t_token *token, int **ret);
int				ft_redirection_filler(t_token *token, t_node **node,
					int type, int **ret);
t_list			*create_list(void);
t_env			*copy_env(char **envp, int i);
void			ft_free_env(t_env *env);
void			free_quote(t_quotes *node);
void			free_node(t_node *node);
t_token			*multiple_tokens(t_token *token, t_env *env);
t_token			*ft_check_redirection(t_token *token, t_node **node,
					int *ret, t_list *ls);
void			ft_free_node_list(t_node *node);
t_list			*clear_list(t_list *t_list_node);
void			create_redirection_node(t_node *node, char *file_name,
					int type, int is_quote);
t_token			*ft_erase_redirection_token(t_token *token, t_file *file);
int				ft_check_token(t_token *token,
					t_node **node, int *ret, t_list *ls);
int				check_which_quotes(t_token *token);
int				check_for_redirect_dollar(t_token *token);

#endif