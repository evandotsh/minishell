/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:16:38 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/19 16:18:03 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*make_arg_node(char *arg_value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->type = ND_ARG;
	node->arg_value = strdup(arg_value);
	return (node);
}

char	*handle_heredoc(t_token *tokens)
{
	char	*delim;
	char	*line;
	char	*result;
	int		fd;
	char	*random;

	random = ft_itoa(ft_random());
	result = ft_strjoin("/tmp/heredoc", random);
	free(random);
	delim = ft_strdup(tokens->token);
	fd = open(result, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return (NULL);
	}
	while (1)
	{
		line = readline("> ");
		if (strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (result);
}

t_ast_node	*parser(t_token *tokens)
{
	t_ast_node	*cmd_node;
	t_ast_node	*pipe_node;
	t_token		*prev_token;
	char		*tmp_heredoc;

	if (tokens == NULL)
		return (NULL);
	cmd_node = malloc(sizeof(t_ast_node));
	cmd_node->type = ND_CMD;
	cmd_node->cmd_name = NULL;
	cmd_node->cmd_args = calloc(1, sizeof(t_ast_node *));
	cmd_node->cmd_arg_count = 0;
	cmd_node->cmd_stdin_source = 0;
	cmd_node->cmd_stdout_dest = 0;
	cmd_node->cmd_stdin_file = NULL;
	cmd_node->cmd_stdout_file = NULL;
	while (tokens != NULL)
	{
		if (cmd_node->cmd_name == NULL)
			cmd_node->cmd_name = ft_strdup(tokens->token);
		else if (strcmp(tokens->token, "|") != 0 && strcmp(tokens->token,
				"<") != 0 && strcmp(tokens->token, ">") != 0
			&& strcmp(tokens->token, ">>") != 0 && strcmp(tokens->token,
				"<<") != 0)
		{
			cmd_node->cmd_args = realloc(cmd_node->cmd_args,
					sizeof(struct t_ast_node *) * (cmd_node->cmd_arg_count
						+ 1));
			cmd_node->cmd_arg_count++;
			cmd_node->cmd_args[cmd_node->cmd_arg_count
				- 1] = make_arg_node(tokens->token);
		}
		else if (strcmp(tokens->token, "<") == 0 || strcmp(tokens->token,
				">") == 0 || strcmp(tokens->token, ">>") == 0 || strcmp(
				tokens->token, "<<") == 0)
		{
			prev_token = tokens;
			tokens = tokens->next;
			if (tokens == NULL)
			{
				ft_printf_fd(STDERR_FILENO, "minishell: parse error near `\n'\n");
				return (NULL);
			}
			if (strcmp(prev_token->token, "<") == 0)
			{
				cmd_node->cmd_stdin_source = 0;
				cmd_node->cmd_stdin_file = ft_strdup(tokens->token);
			}
			else if (strcmp(prev_token->token, ">") == 0)
			{
				cmd_node->cmd_stdout_dest = 1;
				cmd_node->cmd_stdout_file = ft_strdup(tokens->token);
			}
			else if (strcmp(prev_token->token, ">>") == 0)
			{
				cmd_node->cmd_stdout_dest = 2;
				cmd_node->cmd_stdout_file = ft_strdup(tokens->token);
			}
			else if (strcmp(prev_token->token, "<<") == 0)
			{
				cmd_node->cmd_stdin_source = 0;
				tmp_heredoc = handle_heredoc(tokens);
				cmd_node->cmd_stdin_file = ft_strdup(tmp_heredoc);
				printf("heredoc: %s\n", tmp_heredoc);
				free(tmp_heredoc);
			}
		}
		else if (strcmp(tokens->token, "|") == 0)
		{
			pipe_node = malloc(sizeof(t_ast_node));
			pipe_node->type = ND_PIPE;
			pipe_node->pipe_lhs = cmd_node;
			tokens = tokens->next;
			if (tokens == NULL)
			{
				free(pipe_node);
				ft_printf_fd(2, "minishell: Expected command after pipe\n");
				return (NULL);
			}
			pipe_node->pipe_rhs = parser(tokens);
			return (pipe_node);
		}
		tokens = tokens->next;
	}
	cmd_node->cmd_args = realloc(cmd_node->cmd_args,
			sizeof(struct t_ast_node *) * (cmd_node->cmd_arg_count + 1));
	cmd_node->cmd_args[cmd_node->cmd_arg_count] = NULL;
	return (cmd_node);
}

void	free_all_nodes(t_ast_node *nodes)
{
	if (nodes == NULL)
		return ;
	if (nodes->type == ND_CMD)
	{
		free(nodes->cmd_name);
		while (nodes->cmd_arg_count > 0)
		{
			free_all_nodes(nodes->cmd_args[nodes->cmd_arg_count - 1]);
			nodes->cmd_arg_count--;
		}
		free(nodes->cmd_args);
		free(nodes->cmd_stdin_file);
		free(nodes->cmd_stdout_file);
	}
	else if (nodes->type == ND_PIPE)
	{
		free_all_nodes(nodes->pipe_lhs);
		free_all_nodes(nodes->pipe_rhs);
	}
	else if (nodes->type == ND_ARG)
		free(nodes->arg_value);
	free(nodes);
}
