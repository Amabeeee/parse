/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:57:56 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/15 11:16:47 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_re(t_env **env, char *str)
{
	char	*res;

	res = ft_strdup(str);
	res = expand(res, env);
	return (res);
}

char	*expand_sliced(char *str, t_env **envp)
{
	char	**token_slice;
	char	*tmp;

	token_slice = slice_token(str);
	tmp = expand_concate_sliced(token_slice, envp);
	ft_free(token_slice);
	return (tmp);
}
