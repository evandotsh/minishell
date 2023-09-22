/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:16:38 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/22 10:52:28 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir_token(t_token *token)
{
	if (ft_strcmp(token->token, "<") == 0 || ft_strcmp(token->token, ">") == 0
		|| ft_strcmp(token->token, ">>") == 0 || ft_strcmp(token->token, "<<")
		== 0)
		return (1);
	return (0);
}

t_ast_node	*parser_loop(t_ast_node *cmd_node, t_token *tokens, t_env *env)
{
	t_token		*prev_token;

	if (cmd_node->cmd_name == NULL)
		cmd_node->cmd_name = ft_strdup(tokens->token);
	else if (!is_redir_token(tokens) && ft_strcmp(tokens->token, "|") != 0)
		handle_args(cmd_node, tokens);
	else if (is_redir_token(tokens))
	{
		prev_token = tokens;
		tokens = tokens->next;
		if (tokens == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: parse error near `\n'\n");
			return (NULL);
		}
		handle_redirections(cmd_node, tokens, prev_token, env);
	}
	else if (ft_strcmp(tokens->token, "|") == 0)
	{
		cmd_node = make_pipe_node(cmd_node, tokens, env);
		if (cmd_node == NULL)
			return (NULL);
		return (cmd_node);
	}
	return (cmd_node);
}

t_ast_node	*parser(t_token *tokens, t_env *env)
{
	t_ast_node	*cmd_node;
	int			i;
	int			num_args;
	t_ast_node	**new_args;

	if (tokens == NULL)
		return (NULL);
	cmd_node = make_cmd_node();
	while (tokens != NULL)
	{
		cmd_node = parser_loop(cmd_node, tokens, env);
		tokens = tokens->next;
	}
	i = 0;
	num_args = cmd_node->cmd_arg_count + 1;
	new_args = malloc(sizeof(t_ast_node *) * num_args);
	while (i < cmd_node->cmd_arg_count)
	{
		new_args[i] = cmd_node->cmd_args[i];
		i++;
	}
	new_args[num_args - 1] = NULL;
	free(cmd_node->cmd_args);
	cmd_node->cmd_args = new_args;
	return (cmd_node);
}
