/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:07:41 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/21 01:15:51 by sfernand         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
//# define PATH_MAX 4096

typedef struct s_token
{
	char					*token;
	struct s_token			*next;
}							t_token;

// Node types
typedef enum e_node_type
{
	ND_CMD,
	ND_ARG,
	ND_PIPE
}							t_node_type;

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
	int						cmd_pid;
	int						cmd_termination_code;
	t_ast_node				*pipe_lhs;
	t_ast_node				*pipe_rhs;

}							t_ast_node;

typedef struct s_env
{
	char					*key;
	char					*value;
	int						is_secret;
	struct s_env			*next;
	struct s_env			*prev;
}							t_env;

t_token						*lexer(char *line);
t_ast_node					*parser(t_token *tokens);
char						**ft_split_lexer(char const *s, char c);
char						*ft_epur_str(char *str);
void						executor(t_ast_node *node, t_env *env);
char						*get_node_arg(t_ast_node *node, int index);
int							get_node_arg_count(t_ast_node *node);
t_env						*env_from_parent(char **envp);
void						env_add(t_env *env, char *env_var);
void						env_set(t_env *env, char *key, char *value);
void						env_add_back(t_env *env, char *key, char *value);
char						*env_get(t_env *env, char *key);
void						env_remove(t_env *env, char *key);
int							sh_echo(t_ast_node *node);
int							sh_env(t_env *env);
int							sh_pwd(void);
int							sh_unset(t_ast_node *node, t_env *env);
char						**env_to_envp_format(t_env *env);
char						*get_exec_path_from_env(char *program, t_env *env);
void						free_all_nodes(t_ast_node *nodes);
void						free_all_tokens(t_token *token);
char						*ft_strtrim_lexer(char *str);
int							sh_cd(t_ast_node *node, t_env *env);
int							sh_export(t_ast_node *node, t_env *env);
int							sh_exit(t_ast_node *node);
int							is_valid_identifier(char *str);
void						expander(t_ast_node *node, t_env *env);
void						quote(char *str, int i, int j, char *result);
void						print_ast_node(t_ast_node *node, int depth);
void						execute_command(t_ast_node *node, t_env *env);
void						execute_pipe(t_ast_node *node, t_env *env);
void						setup_redirections(t_ast_node *node);
void						env_set_secret(t_env *env, char *key);
void						launch_process(t_ast_node *node, t_env *env);
char						**build_argv(t_ast_node *node);
void						setup_signals(void);
void						test_signal(int sig);
char						*ft_strndup(char *str, int n);
void						free_split(char **split);
int							ft_random(void);
void						shell_sigint(int sig);
void						shell_sigquit(int sig);
void						shell_sigterm(int sig);
char						*add_spaces(char *str);
char						*check_redir(char *str, int i, int j, char *result);
#endif