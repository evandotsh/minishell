/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:16:38 by evmorvan          #+#    #+#             */
/*   Updated: 2023/08/23 16:50:53 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node *make_arg_node(char *arg_value) {

  t_ast_node *node;
  
  node = malloc(sizeof(t_ast_node));
  node->type = ND_ARG;
  node->arg_value = strdup(arg_value);
  return node;
}

t_ast_node *parser(t_token *tokens)
{
    t_ast_node *cmd_node;
    
    // Handle NULL case
    if (tokens == NULL)
    {
        return NULL;
    }
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
        // Parse command
        if (cmd_node->cmd_name == NULL)
        {
            cmd_node->cmd_name = strdup(tokens->token);
        }
        // Parse Arguments
        else if (strcmp(tokens->token, "|") != 0 && strcmp(tokens->token, "<") != 0 && strcmp(tokens->token, ">") != 0 && strcmp(tokens->token, ">>") != 0)
        {
            cmd_node->cmd_args = realloc(cmd_node->cmd_args, sizeof(struct t_ast_node *) * (cmd_node->cmd_arg_count + 1));
            cmd_node->cmd_arg_count++;
            cmd_node->cmd_args[cmd_node->cmd_arg_count - 1] = make_arg_node(tokens->token);
        }
        // Parse Redirections
        else if (strcmp(tokens->token, "<") == 0 || strcmp(tokens->token, ">") == 0 || strcmp(tokens->token, ">>") == 0)
        {
            tokens = tokens->next; // Assuming the file name is the next token
            if (tokens == NULL)
            {
                fprintf(stderr, "Invalid syntax: Expected filename after redirection operator\n");
                return NULL;
            }
            if (strcmp(tokens->token, "<") == 0)
            {
                cmd_node->cmd_stdin_source = 0;
                cmd_node->cmd_stdin_file = ft_strdup(tokens->token);
            }
            else
            {
                cmd_node->cmd_stdout_dest = 1;
                cmd_node->cmd_stdout_file = ft_strdup(tokens->token);
            }
        }
        // Parse Pipes
        else if (strcmp(tokens->token, "|") == 0)
        {
            t_ast_node *pipe_node = malloc(sizeof(t_ast_node));
            pipe_node->type = ND_PIPE;
            pipe_node->pipe_lhs = cmd_node;
            tokens = tokens->next; // Assume the command after | is the next token
            if (tokens == NULL)
            {
                fprintf(stderr, "Invalid syntax: Expected command after pipe operator\n");
                return NULL;
            }
            pipe_node->pipe_rhs = parser(tokens);
            return pipe_node;
        }
        tokens = tokens->next;
    }
    cmd_node->cmd_args[cmd_node->cmd_arg_count] = NULL;
    return cmd_node;
}