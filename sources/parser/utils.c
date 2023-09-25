/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:00:02 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/25 09:49:28 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_args(t_ast_node *cmd_node, t_token *tokens)
{
	int			num_args;
	t_ast_node	**new_args;
	int			i;

	i = 0;
	num_args = cmd_node->cmd_arg_count + 1;
	new_args = malloc(sizeof(t_ast_node *) * num_args);
	while (i < cmd_node->cmd_arg_count)
	{
		new_args[i] = cmd_node->cmd_args[i];
		i++;
	}
	new_args[i] = make_arg_node(tokens->token);
	free(cmd_node->cmd_args);
	cmd_node->cmd_args = new_args;
	cmd_node->cmd_arg_count = num_args;
}

t_ast_node	*make_pipe_node(t_ast_node *cmd_node, t_token *tokens, t_env *env)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->type = ND_PIPE;
	node->pipe_lhs = cmd_node;
	tokens = tokens->next;
	if (tokens == NULL)
	{
		free(node);
		ft_printf_fd(2, "minishell: Expected command after pipe\n");
		env_set(env, "?", "2");
		return (NULL);
	}
	node->pipe_rhs = parser(tokens, env);
	return (node);
}

t_ast_node	*make_arg_node(char *arg_value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->type = ND_ARG;
	node->arg_value = ft_strdup(arg_value);
	return (node);
}

t_ast_node	*make_cmd_node(void)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->type = ND_CMD;
	node->cmd_name = NULL;
	node->cmd_args = ft_calloc(1, sizeof(t_ast_node *));
	node->cmd_arg_count = 0;
	node->cmd_stdin_source = 0;
	node->cmd_stdout_dest = 0;
	node->cmd_stdin_file = NULL;
	node->cmd_stdout_file = NULL;
	return (node);
}

void	handle_redirections(t_ast_node *cmd_node, t_token *tokens,
		t_token *prev_token, t_env *env)
{
	char	*tmp_heredoc;

	if (ft_strcmp(prev_token->token, "<") == 0)
	{
		cmd_node->cmd_stdin_source = 0;
		cmd_node->cmd_stdin_file = ft_strdup(tokens->token);
	}
	else if (ft_strcmp(prev_token->token, ">") == 0)
	{
		cmd_node->cmd_stdout_dest = 1;
		cmd_node->cmd_stdout_file = ft_strdup(tokens->token);
	}
	else if (ft_strcmp(prev_token->token, ">>") == 0)
	{
		cmd_node->cmd_stdout_dest = 2;
		cmd_node->cmd_stdout_file = ft_strdup(tokens->token);
	}
	else if (ft_strcmp(prev_token->token, "<<") == 0)
	{
		cmd_node->cmd_stdin_source = 0;
		tmp_heredoc = handle_heredoc(env, tokens);
		cmd_node->cmd_stdin_file = ft_strdup(tmp_heredoc);
		free(tmp_heredoc);
	}
}
