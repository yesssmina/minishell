/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sannagar <sannagar@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:37:45 by sannagar          #+#    #+#             */
/*   Updated: 2024/01/18 13:49:52 by sannagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_index(char *name, t_data *data)
{
	int		y;
	int		x;

	x = 0;
	while (data->env[x])
	{
		y = 0;
		while (data->env[x][y] && data->env[x][y] == name[y]
		&& name[y] != '\0' && name[y] != '=' &&
		data->env[x][y] != '\0' && data->env[x][y] != '=')
			y++;
		if ((data->env[x][y] == '\0' || data->env[x][y] == '=') &&
		(name[y] == '\0' || name[y] == '='))
			return (x);
		x++;
	}
	return (-1);
}

void	replace_var(char *new_var, t_data *data, int index)
{
	if (ft_strchr(new_var, '='))
	{
		free(data->env[index]);
		data->env[index] = ft_strdup(new_var);
	}
}

char	**export_env(char **old_env, char *export)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (envlen(old_env) + 1));
	if (!new_env)
		exit(EXIT_FAILURE);
	while (old_env[i])
	{
		new_env[i] = ft_strdup(old_env[i]);
		i++;
	}
	free_env(old_env);
	new_env[i] = ft_strdup(export);
	i++;
	new_env[i] = NULL;
	return (new_env);
}

void	export_alone(t_data *data)
{
	int		i;
	int		j;
	char	**temp_env;
	char	*swap;

	i = 0;
	temp_env = dup_env(data->env);
	while (temp_env[i + 1])
	{
		j = i + 1;
		if (ft_strncmp(temp_env[i], temp_env[j], INT_MAX) > 0)
		{
			swap = temp_env[j];
			temp_env[j] = temp_env[i];
			temp_env[i] = swap;
			i = 0;
		}
		else
			i++;
	}
	print_export(temp_env);
	free_env(temp_env);
}

void	handle_export(char **inputs, t_data *data)
{
	int	i;
	int	index;

	i = 1;
	if (inputs[i])
	{
		while (inputs[i])
		{
			index = var_index(inputs[i], data);
			if (index >= 0 && check_export(inputs[i], data))
				replace_var(inputs[i], data, index);
			else if (check_export(inputs[i], data))
				export_env_handle_env(data, inputs, i);
			else
				sentence_handle_export(data, inputs, i);
			i++;
		}
	}
	else
		export_alone(data);
}
