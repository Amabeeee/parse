/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:57:56 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/09 17:38:55 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(char *value, t_token *prev)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = strdup(value);
	if (!new->value)
	{
		free (new);
		return (NULL);
	}
	new->type = ARG;
	new->prev = prev;
	new->next = NULL;
	return (new);
}

t_token	*token_list(char **tokens)
{
	t_token	*first;
	t_token	*prev;
	t_token	*new_node;
	int		i;

	first = NULL;
	prev = NULL;
	i = 0;
	while (tokens[i])
	{
		new_node = create_token(tokens[i], prev);
		if (!new_node)
			return (NULL);
		if (!prev)
			first = new_node;
		else
			prev->next = new_node;
		prev = new_node;
		i++;
	}
	return (first);
}

void	init_type(t_token *token)
{
	if (ft_strcmp(token->value, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->value, "<<") == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->value, "<") == 0)
		token->type = IN;
	else if (ft_strcmp(token->value, ">") == 0)
		token->type = OUT;
	else if (ft_strcmp(token->value, "|") == 0)
		token->type = PIPE;
	else
		token->type = ARG;
}

void	free_token_list(t_token *first)
{
	t_token	*tmp;

	while (first)
	{
		tmp = first;
		first = first->next;
		free(tmp->value);
		free(tmp);
	}
}

void	type_foreach(t_token *list)
{
	while (list)
	{
		init_type(list);
		list = list -> next;
	}
}
