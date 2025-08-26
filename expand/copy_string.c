/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/19 19:53:16 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_replace(char *res, char *replace, int *k)
{
	int	j;

	j = 0;
	while (replace[j])
	{
		res[*k] = replace[j];
		(*k)++;
		j++;
	}
}

void	copy_after_var(char *res, char *str, int *k, int i)
{
	while (str[i])
	{
		res[*k] = str[i];
		(*k)++;
		i++;
	}
}

char	*result_spe(char *str, char *replace, int var_start, int var_end)
{
	int		k;
	int		i;
	int		len;
	char	*res;

	k = 0;
	i = 0;
	len = ft_strlen(str) - (var_end - var_start) + ft_strlen(replace);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	while (i < var_start)
		res[k++] = str[i++];
	copy_replace(res, replace, &k);
	i = var_end;
	copy_after_var(res, str, &k, i);
	res[k] = '\0';
	free(replace);
	return (res);
}

char	*get_replace(char *str, int start, int end, t_env **envp)
{
	char	*var_name;
	char	*replace;

	var_name = copy_var_name(str, start + 1, (end - start));
	replace = get_env_var(envp, var_name);
	free(var_name);
	if (!replace)
		return (ft_strdup(""));
	return (ft_strdup(replace));
}

char	*result(char *str, t_env **envp, int start, int end)
{
	int		k;
	int		i;
	int		len;
	char	*res;
	char	*replace;

	replace = get_replace(str, start, end, envp);
	k = 0;
	i = 0;
	len = ft_strlen(str) - (end - start) + ft_strlen(replace);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	while (i < start)
		res[k++] = str[i++];
	copy_replace(res, replace, &k);
	i = end;
	copy_after_var(res, str, &k, i);
	res[k] = '\0';
	free(replace);
	return (res);
}
