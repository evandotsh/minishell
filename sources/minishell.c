/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:10:56 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/11 13:45:12 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_token(t_token *token)
{
	printf("\n[");
	while (token != NULL)
	{
		printf("*%s,", token->token);
		token = token->next;
	}
	printf("]\n");
}

void	print_ast_node(t_ast_node *node, int depth)
{
	if (node == NULL)
		return ;
	// add indent
	for (int i = 0; i < depth; i++)
		printf("  ");
	// print node type
	switch (node->type)
	{
	case ND_CMD:
		printf("CMD");
		break ;
	case ND_ARG:
		printf("ARG");
		break ;
	case ND_PIPE:
		printf("PIPE");
		break ;
	default:
		printf("UNKNOWN");
		break ;
	}
	// print additional information
	if (node->type == ND_CMD)
	{
		printf("(name=%s, argc=%d)", node->cmd_name, node->cmd_arg_count);
		printf("\n");
		for (int i = 0; i < node->cmd_arg_count; i++)
		{
			print_ast_node(node->cmd_args[i], depth + 1);
		}
		if (node->cmd_stdin_source)
			printf("  Input source: %s\n", node->cmd_stdin_file);
		if (node->cmd_stdout_dest)
			printf("  Output destination: %s\n", node->cmd_stdout_file);
	}
	else if (node->type == ND_ARG)
	{
		printf("(value=%s)", node->arg_value);
		printf("\n");
	}
	else if (node->type == ND_PIPE)
	{
		printf("\n");
		print_ast_node(node->pipe_lhs, depth + 1);
		for (int i = 0; i < depth + 1; i++)
			printf("  ");
		printf("| PIPE\n");
		print_ast_node(node->pipe_rhs, depth + 1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char *line;
	t_token *token;
	t_ast_node *cmds;
	t_env *env;
	int debug;

	debug = 0;
	if (argc == 2 && strcmp(argv[1], "--debug") == 0)
		debug = 1;
	env = env_from_parent(envp);
	(void)env;
	while (TRUE)
	{
		printf("\n%sminishell$ \n%s", C_PURPLE, C_YELLOW);
		line = readline(PROMPT C_RESET);
		add_history(line);
		//ft_printf("%s\n", line);
		if (line != NULL && line[0] != '\0')
		{
			token = lexer(line);
			cmds = parser(token);
			if (debug)
			{
				print_token(token);
				print_ast_node(cmds, 0);
			}
			expander(cmds, env);
			executor(cmds, env);
		}
		if (line == NULL)
		{
			ft_printf("exit\n");
			free(line);
			exit(0);
		}
		free_all_nodes(cmds);
		// executor(cmds, env);
		// free_all_nodes(cmds);
		// free(line);
	}
	free(line);
	return (0);
}