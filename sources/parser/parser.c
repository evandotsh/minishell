/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:16:38 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/26 05:51:26 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_arg_token(t_token *tokens)
{
	return ((ft_strcmp(tokens->token, "|") != 0 && ft_strcmp(tokens->token,
				"<") != 0 && ft_strcmp(tokens->token, ">") != 0
			&& ft_strcmp(tokens->token, ">>") != 0 && ft_strcmp(tokens->token,
				"<<") != 0));
}

int	is_redir_token(t_token *tokens)
{
	return (ft_strcmp(tokens->token, "<") == 0 || ft_strcmp(tokens->token,
			">") == 0 || ft_strcmp(tokens->token, ">>") == 0
		|| ft_strcmp(tokens->token, "<<") == 0);
}

int	parser_loop(t_ast_node **cmd_node, t_token *tokens, t_env *env)
{
	t_token		*prev_token;
	int			ret;

	ret = 0;
	if ((*cmd_node)->cmd_name == NULL)
		(*cmd_node)->cmd_name = ft_strdup(tokens->token);
	else if (is_arg_token(tokens))
		handle_args(*cmd_node, tokens);
	else if (is_redir_token(tokens))
	{
		prev_token = tokens;
		tokens = tokens->next;
		if (tokens == NULL)
			return (ft_printf_fd(STDERR_FILENO,
					"minishell: parse error near `\\n'\n"), 1);
		handle_redirections(*cmd_node, tokens, prev_token, env);
		ret = 2;
	}
	else if (ft_strcmp(tokens->token, "|") == 0)
	{
		*cmd_node = make_pipe_node(*cmd_node, tokens, env);
		return (1);
	}
	return (ret);
}

t_ast_node	*fix_args(t_ast_node *cmd_node)
{
	int			i;
	int			num_args;
	t_ast_node	**new_args;

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

t_ast_node	*parser(t_token *tokens, t_env *env)
{
	t_ast_node	*cmd_node;
	int			ret;

	if (tokens == NULL)
		return (NULL);
	cmd_node = make_cmd_node();
	while (tokens != NULL)
	{
		ret = parser_loop(&cmd_node, tokens, env);
		if (ret == 1)
			return (cmd_node);
		else if (ret == 2)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	cmd_node = fix_args(cmd_node);
	return (cmd_node);
}
