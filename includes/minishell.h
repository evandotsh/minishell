/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:07:41 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/26 16:12:21 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/termios.h>

// Defines
# define TRUE 1
# define FALSE 0
# define PROMPT "minishell$ "
# define DEBUG_PANGRAM "The quick brown fox jumps over the lazy dog\n"

// Colors
# define C_RESET "\033[0m"
# define C_RED "\033[0;31m"
# define C_GREEN "\033[0;32m"
# define C_YELLOW "\033[0;33m"
# define C_BLUE "\033[0;34m"
# define C_PURPLE "\033[0;35m"
# define C_CYAN "\033[0;36m"

// Misc
# define MAX_PIPE 200
# define SHN "minishell"

typedef struct s_token
{
	char					*token;
	struct s_token			*next;
	int						quote_type;
}							t_token;

// Node types
typedef enum e_node_type
{
	ND_CMD,
	ND_ARG,
	ND_PIPE
}							t_node_type;

typedef enum e_quote_type
{
	QT_NONE,
	QT_SINGLE,
	QT_DOUBLE
}							t_quote_type;

typedef struct s_ast_node	t_ast_node;

typedef struct s_ast_node
{
	int						type;
	char					*cmd_name;
	t_ast_node				**cmd_args;
	int						cmd_arg_count;
	int						cmd_stdin_source;
	char					*cmd_stdin_file;
	int						cmd_stdout_dest;
	char					*cmd_stdout_file;
	int						cmd_pipe_read;
	int						cmd_pipe_write;
	char					*arg_value;
	int						arg_quote_type;
	int						cmd_pid;
	int						cmd_termination_code;
	t_ast_node				*pipe_lhs;
	t_ast_node				*pipe_rhs;

}							t_ast_node;

extern int					g_signal;

typedef struct s_env
{
	char					*key;
	char					*value;
	int						is_secret;
	struct s_env			*next;
	struct s_env			*prev;
}							t_env;

// PARSER
void						handle_args(t_ast_node *cmd_node, t_token *tokens);
t_ast_node					*make_pipe_node(t_ast_node *cmd_node,
								t_token *tokens, t_env *env);
t_ast_node					*make_arg_node(char *arg_value);
t_ast_node					*make_cmd_node(void);
void						handle_redirections(t_ast_node *cmd_node,
								t_token *tokens, t_token *prev_token,
								t_env *env);
char						*handle_heredoc(t_env *env, t_token *tokens);
int							is_redir_token(t_token *token);
t_ast_node					*parser(t_token *tokens, t_env *env);
void						dequotter2000(t_token *tokens);

// EXECUTOR
void						execute_command(t_ast_node *node, t_env *env);
void						execute_pipe(t_ast_node *node, t_env *env);
char						**build_argv(t_ast_node *node);
void						setup_redirections(t_ast_node *node);
void						error(char *cmd_name, char *error);
void						pidis0(t_ast_node *node, t_env *env, int *pipefd,
								int fd);
void						closepipes(int *pipefd);
void						execute_builtins(t_ast_node *node, t_env *env,
								char **args);
void						executor(t_ast_node *node, t_env *env);
void						launch_process(t_ast_node *node, t_env *env);

// EXPANDER
char						*expand(t_env *env, char *string);
void						expand_tokens(t_token *token, t_env *env);

// QUOTES
char						*interpret_quotes(char *str, t_token *token);
void						interpret_quotes_tokens(t_token *token);

// LEXER
t_token						*lexer(char *line);
char						**ft_split_lexer(char const *s, char c);
char						*ft_epur_str(char *str);
char						*ft_strtrim_lexer(char *str);
void						quote(char *str, int i, int j, char *result);
char						*add_spaces(char *str);
char						*check_redir(char *str, int i, int j, char *result);

// AST helpers
char						*get_node_arg(t_ast_node *node, int index);
int							get_node_arg_count(t_ast_node *node);
void						free_all_nodes(t_ast_node *nodes);
void						free_all_tokens(t_token *token);

// ENV
t_env						*env_from_parent(char **envp);
void						env_set_secret(t_env *env, char *key);
void						env_add(t_env *env, char *env_var);
void						env_set(t_env *env, char *key, char *value);
void						env_add_back(t_env *env, char *key, char *value);
char						*env_get(t_env *env, char *key);
void						env_remove(t_env *env, char *key);
char						**env_to_envp_format(t_env *env);
char						*get_exec_path_from_env(char *program, t_env *env);
int							is_valid_identifier(char *str);
void						free_all_env(t_env *env);

// BUILTINS
int							sh_echo(t_ast_node *node, t_env *env);
int							sh_env(t_env *env);
int							sh_pwd(t_env *env);
int							sh_unset(t_ast_node *node, t_env *env);
int							sh_cd(t_ast_node *node, t_env *env);
int							sh_export(t_ast_node *node, t_env *env);
int							sh_exit(t_ast_node *node, t_env *env);
int							is_builtin(char *cmd_name);

// SIGNALS
void						shell_sigquit(int sig);
void						shell_sigterm(int sig);
void						shell_sigint(int sig);
void						echo_control_seq(int c);
void						initialize_signal(void);

// OTHERS
int							ft_random(void);
void						print_ast_node(t_ast_node *node, int depth);
char						*ft_strndup(char *str, int n);
void						free_split(char **split);
int							ft_random(void);
void						shell_sigint(int sig);
void						shell_sigquit(int sig);
void						shell_sigterm(int sig);
char						*ft_strcpy(char *dest, char *src);
void						*ft_realloc(void *ptr, size_t old_size,
								size_t new_size);
char						*ft_strcpy(char *dest, char *src);
int							ft_strcmp(const char *s1, const char *s2);
char						*ft_strncpy(char *dest, char *src, size_t n);
void						print_ast_node(t_ast_node *node, int depth);
char						*build_path(char *path, char *cmd_name);
void						handle_quotes(t_env *env, t_token *token);
void						bubble_sort_env(t_env *start, int listLength);
void						multi_free(int count, ...);
char						*ft_strcat(char *dest, const char *src);
void						empty_handler(int sig);
extern void					rl_replace_line(const char *str, int i);
#endif