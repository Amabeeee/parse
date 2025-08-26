/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/16 14:15:23 by amdevezi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			k;

	ptr = (unsigned char *)s;
	k = 0;
	while (k < n)
	{
		ptr[k] = '\0';
		k++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	taille;

	taille = nmemb * size;
	if (size != 0 && taille / size != nmemb)
		return (NULL);
	ptr = malloc(taille + 1);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, taille);
	return (ptr);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->in = 0;
	cmd->out = 1;
	cmd->argv = NULL;
	cmd->cmd_name = NULL;
	cmd->is_builtin = 0;
	cmd->next = NULL;
	cmd->ft_pipe[0] = 0;
	cmd->ft_pipe[1] = 1;
	return (cmd);
}

t_cmd	*parse_tokens(char **tokens, t_env **envp)
{
	t_cmd		*head;
	t_cmd		*current;
	t_process	context;
	int			i;

	head = NULL;
	current = NULL;
	i = 0;
	context.head = &head;
	context.cur = &current;
	context.tok = tokens;
	context.i = &i;
	context.ev = envp;
	while (tokens[i])
	{
		process_token(&context);
		if (current->in == -2)
		{
			free_cmd_list(head);
			return (NULL);
		}
	}
	return (head);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		i = 0;
		tmp = cmd->next;
		if (cmd->cmd_name != NULL)
			free(cmd->cmd_name);
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				free(cmd->argv[i]);
				i++;
			}
			free(cmd->argv);
		}
		close_in_out(cmd);
		free(cmd);
		cmd = tmp;
	}
}
