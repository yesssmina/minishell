/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sannagar <sannagar@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:37:38 by sannagar          #+#    #+#             */
/*   Updated: 2024/01/16 18:22:00 by sannagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	if (ft_isdigit(str[i]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	print_export(char **env)
{
	int	i;
	int	j;
	int	equal;

	i = -1;
	while (env[++i])
	{
		equal = 1;
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][j])
		{
			if (env[i][j] == '\\' || env[i][j] == '$' ||
			env[i][j] == '\"')
				write(1, "\\", 1);
			write(1, &env[i][j], 1);
			if (env[i][j] == '=' && equal-- == 1)
				write(1, "\"", 1);
			j++;
		}
		if (equal != 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
	return (1);
}

void	sentence_handle_export(t_data *data, char **inputs, int i)
{
	ft_putstr_fd("minishell: export: '", 1);
	ft_putstr_fd(inputs[i], 1);
	error_sentence("': not a valid identifier\n", 1, data);
}

void	export_env_handle_env(t_data *data, char **inputs, int i)
{
	data->env = export_env(data->env, inputs[i]);
	if (!data->env)
		exit(EXIT_FAILURE);
}
