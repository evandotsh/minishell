/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:16:38 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/22 08:19:11 by evmorvan         ###   ########.fr       */
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

	if (tokens == NULL)
		return (NULL);
	cmd_node = make_cmd_node();
	while (tokens != NULL)
	{
		cmd_node = parser_loop(cmd_node, tokens, env);
		tokens = tokens->next;
	}
	cmd_node->cmd_args = ft_realloc(cmd_node->cmd_args,
			sizeof(struct t_ast_node *) * (cmd_node->cmd_arg_count + 1));
	cmd_node->cmd_args[cmd_node->cmd_arg_count] = NULL;
	return (cmd_node);
}
