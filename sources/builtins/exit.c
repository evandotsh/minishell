/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:59:55 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/28 14:57:12 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

unsigned long long	ft_atoull(const char *str)
{
	int					i;
	unsigned long long	nb;
	unsigned long long	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * sign);
}

int	ft_is_code_valid(char *str)
{
	int	i;

	i = 0;
	if (ft_atoull(str) > 9223372036854775807ULL
		|| ft_atoull(str) < -9223372036854775808ULL)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_shell(t_ast_node *node, t_env *env, int exit_code)
{
	free_all_env(env);
	free_all_nodes(node);
	printf("exit\n");
	exit(exit_code);
}

int	sh_exit(t_ast_node *node, t_env *env)
{
	int	exit_code;

	if (get_node_arg_count(node) > 1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
		exit_code = 255;
		exit_shell(node, env, exit_code);
	}
	if (get_node_arg(node, 0))
	{
		if (ft_is_code_valid(get_node_arg(node, 0)))
			exit_code = ft_atoi(get_node_arg(node, 0)) % 256;
		else
		{
			ft_printf_fd(STDERR_FILENO,
				"minishell: exit: %s: numeric argument required\n",
				get_node_arg(node, 0));
			exit_shell(node, env, 255);
		}
	}
	else
		exit_code = 0;
	exit_shell(node, env, exit_code);
	return (exit_code);
}
