/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/20 08:08:04 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_special(char *str, int var_start, char c)
{
	if (c == '?')
		return (result_spe(str, ft_itoa(exit_code_convert(g_last_return)), \
		var_start, var_start + 2));
	if (c == '"' || c == '\'' || c == 0)
		return (result_spe(str, ft_strdup(""), var_start, var_start + 1));
	return (ft_strdup(str));
}

char	*expand_normal(char *str, t_env **envp, int var_start)
{
	int	var_end;

	if (str[var_start + 1] >= '1' && str[var_start + 1] <= '9')
	{
		var_end = var_start + 2;
		while (ft_isalnum(str[var_end]) || str[var_end] == '_')
			var_end++;
		return (result_spe(str, ft_strdup(""), var_start, var_start + 2));
	}
	var_end = var_start + 1;
	while (ft_isalnum(str[var_end]) || str[var_end] == '_')
		var_end++;
	return (result(str, envp, var_start, var_end));
}

int	size_variable(char *str, int i, t_env **envp)
{
	int		j;
	char	*var_name;
	char	*replace;

	j = i;
	if (str[j] == '$')
	{
		j++;
		if (str[j] == '\0')
			return (0);
		if (str[j + 1] == '?')
			return (1);
		while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
			j++;
	}
	var_name = copy_var_name(str, i + 1, (j - i));
	replace = get_env_var(envp, var_name);
	j = ft_strlen(replace);
	free(var_name);
	return (j);
}

int	pre_expand(char **current, t_env **envp)
{
	int	i;
	int	j;
	int	in_singleq;
	int	in_doubleq;

	i = 0;
	j = 0;
	in_singleq = 0;
	in_doubleq = 0;
	while ((*current)[i])
	{
		update_quote_state((*current)[i], &in_singleq, &in_doubleq);
		if ((*current)[i] == '$' && !in_singleq)
		{
			j = size_variable((*current), i, envp);
			if (process_dollar(current, envp, &i) == -1)
				return (-1);
			i += j;
		}
		else
			i++;
	}
	return (0);
}

char	*expand(char *str, t_env **envp)
{
	char	*current;

	current = ft_strdup(str);
	if (!current)
		return (NULL);
	if (pre_expand(&current, envp) == -1)
	{
		free(current);
		return (NULL);
	}
	free(str);
	return (current);
}
