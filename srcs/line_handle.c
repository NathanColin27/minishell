/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 10:38:47 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/19 19:29:39 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_lexing(void)
{
	t_minishell	*minishell;
	int			nbr_tokens;
	char		*tmp;
	int			x;

	x = -1;
	minishell = get_minishell();
	tmp = minishell->line;
	minishell->line = ft_strtrim(tmp, "\t\r\v\f");
	free(tmp);
	if ((nbr_tokens = ft_tokens_count(minishell->line)) < 0)
	{
		ft_get_exit_code(NO_STATUS, ft_eof_error(nbr_tokens, 2));
		return(0);
	}
	if (!(minishell->tokens = malloc(sizeof(char*) * (nbr_tokens + 1))))
		exit(ft_free_minishell() && 0);
	while (++x < nbr_tokens)
	{
		tmp = ft_tokens_split(minishell->line, x + 1);
		minishell->tokens[x] = ft_strdup(tmp);
		free(tmp);
	}
	minishell->tokens[x] = NULL;
	return (1);
}

static int	ft_was_eof(void)
{
	t_minishell *minishell;
	char		*old_line;
	char		*line;

	minishell = get_minishell();
	if ((minishell->gnl_ret = get_next_line(1, &line)) < 0)
		ft_exit_error();
	if (minishell->was_eof)
		old_line = minishell->line;
	else
		old_line = "";
	if (!(minishell->line = ft_strjoin(old_line, line)))
		ft_exit_error();
	if (minishell->was_eof)
		free(old_line);
	free(line);
	if (minishell->gnl_ret > 0)
		minishell->was_eof = 0;
	else if (minishell->gnl_ret == 0)
	{
		ft_putstr("  \b\b");
		return (0);
	}
	return (1);
}

static int	ft_current_line(void)
{
	char		*line;
	t_minishell	*minishell;

	minishell = get_minishell();
	if ((minishell->gnl_ret = get_next_line(1, &line)) < 0)
		ft_exit_error();
	minishell->line = ft_strtrim(line, SPACE);
	free(line);
	if (minishell->gnl_ret == 0 && ft_strlen(minishell->line))
	{
		minishell->was_eof = 1;
		ft_putstr("  \b\b");
		return (0);
	}
	else if (minishell->gnl_ret == 0 && !ft_strlen(minishell->line))
	{
		ft_putstr("  \b\b");
		ft_eof_exit();
	}
	else if (!ft_strlen(minishell->line))
		return (0);
	return (1);
}

int			ft_line_handle(void)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	if (minishell->was_eof)
	{
		if (!(ft_was_eof()))
			return (0);
	}
	else
	{
		if (!(ft_current_line()))
			return (0);
	}
	if (minishell->line)
		if (!ft_lexing())
			return (0);
	return (1);
}
