/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:55:09 by evmorvan          #+#    #+#             */
/*   Updated: 2023/07/22 12:43:29 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Librairies
# include "../libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

// Defines
# define TRUE 1
# define FALSE 0
# define PROMPT "❯ "
# define DEBUG_PANGRAM "The quick brown fox jumps over the lazy dog\n"

// Colors
# define C_RESET "\033[0m"
# define C_RED "\033[0;31m"
# define C_GREEN "\033[0;32m"
# define C_YELLOW "\033[0;33m"
# define C_BLUE "\033[0;34m"
# define C_PURPLE "\033[0;35m"
# define C_CYAN "\033[0;36m"

// Structures
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef enum e_redirtype
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_PIPE,
	REDIR_NONE
}					t_redirtype;

typedef struct s_redir
{
	t_redirtype		type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_minishell
{
	t_env			*env;
	t_cmd			*cmd;
	int				last_exit_status;
}					t_minishell;

typedef struct s_token
{
	char			*token;
	struct s_token	*next;
}				t_token;

// Prototypes
char				*ft_strndup(char *str, int n);
t_env				*ft_env(char **envp);
void				print_env(t_env *env);
void				debug(char *line, t_env *env);
char				*get_pretty_cwd(void);
void				executor(t_cmd *cmd_list);
t_token				*lexer(char *line);
void				parser(t_token *token);
char				**ft_split_lexer(char const *s, char c);
void				free_token(t_token *token);
void				expander(t_cmd *cmd_list);
char				*epur_str(char *str);
t_cmd				*add_args(t_token *token);
void				add_redir(char	*str, t_cmd *new_args, t_token *token);

#endif
