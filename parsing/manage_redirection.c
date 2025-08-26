/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdevezi <amdevezi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:49:23 by amdevezi          #+#    #+#             */
/*   Updated: 2025/08/17 00:33:37 by lauraper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_argument(t_cmd *cmd, char *token)
{
	int		argc;
	int		j;
	char	**new_argv;

	argc = 0;
	if (cmd->argv != NULL)
	{
		while (cmd->argv[argc])
			argc++;
	}
	new_argv = ft_calloc(argc + 2, sizeof(char *));
	j = 0;
	while (j < argc)
	{
		new_argv[j] = ft_strdup(cmd->argv[j]);
		j++;
	}
	new_argv[argc] = ft_strdup(token);
	new_argv[argc + 1] = NULL;
	if (cmd->argv != NULL)
		ft_free(cmd->argv);
	cmd->argv = new_argv;
}

void	handle_argument(t_cmd *cmd, char *token)
{
	if (!cmd->cmd_name)
	{
		cmd->cmd_name = ft_strdup(token);
		cmd->is_builtin = ft_is_built_in(cmd);
		cmd->argv = ft_calloc(1, sizeof(char *));
		cmd->argv[0] = NULL;
	}
	else
		append_argument(cmd, token);
}

void	process_token(t_process *p)
{
	if (!*(p->cur))
	{
		*(p->cur) = init_cmd();
		if (!*(p->head))
			*(p->head) = *(p->cur);
	}
	if (is_redirection(p->tok[*(p->i)]))
	{
		if ((*(p->cur))->in == -1 || (*(p->cur))->out == -1)
			(*(p->i))++;
		else
			*(p->i) = handle_redirection(*(p->cur), (p->tok), *(p->i), (p->ev));
	}
	else if (!ft_strcmp(p->tok[*(p->i)], "|"))
	{
		(*(p->cur))->next = init_cmd();
		*(p->cur) = (*(p->cur))->next;
		(*(p->i))++;
	}
	else
	{
		handle_argument(*(p->cur), p->tok[*(p->i)]);
		(*(p->i))++;
	}
}
