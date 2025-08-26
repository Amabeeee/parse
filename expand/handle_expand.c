/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:40:05 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/14 18:22:58 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_normal_var(char *str, t_env **envp, int var_start)
{
	char	*tmp;

	tmp = expand_normal(str, envp, var_start);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*handle_special_var(char *str, int var_start)
{
	char	*tmp;

	tmp = expand_special(str, var_start, str[var_start + 1]);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*handle_dollar(char *str, t_env **envp, int var_start)
{
	if (is_special_var(str[var_start + 1]))
		return (handle_special_var(str, var_start));
	if (!is_valid_var_start(str[var_start + 1]))
		return (ft_strdup(str));
	return (handle_normal_var(str, envp, var_start));
}

int	process_dollar(char **current, t_env **envp, int *i)
{
	char	*new_str;

	new_str = handle_dollar(*current, envp, *i);
	if (!new_str)
		return (-1);
	if (strcmp(new_str, *current) == 0)
	{
		free(new_str);
		(*i)++;
	}
	else
	{
		free(*current);
		*current = new_str;
		*i = 0;
	}
	return (0);
}
