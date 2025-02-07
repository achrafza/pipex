/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 06:20:59 by azahid            #+#    #+#             */
/*   Updated: 2025/02/07 07:04:09 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

char	**parse_envp(char *envp[])
{
	int		i;
	char	**sp;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
		{
			sp = ft_split(envp[i] + 5, ':');
			if (!sp)
				return (NULL);
			return (sp);
		}
		i++;
	}
	return (NULL);
}

char	*joined(char *commande, char *sp)
{
	char	*com;
	char	*joinedpath;

	com = ft_strjoin("/", commande);
	if (!com)
		return (NULL);
	joinedpath = ft_strjoin(sp, com);
	if (!joinedpath)
		return (free(com), NULL);
	return (free(com), joinedpath);
}

char	*find_access(char *path[], char *commande)
{
	char	**sp;
	char	*joinedpath;
	int		i;

	joinedpath = NULL;
	i = 0;
	if (!access(commande, F_OK | X_OK))
		return (commande);
	sp = parse_envp(path);
	if (!sp)
		return (NULL);
	while (sp[i])
	{
		joinedpath = joined(commande, sp[i]);
		if (!joinedpath)
			return (freeit(sp), NULL);
		if (++i && !(access(joinedpath, F_OK | X_OK)))
			return (freeit(sp), joinedpath);
		free(joinedpath);
	}
	return (free(joinedpath), freeit(sp), NULL);
}

char	**createargs1(char *str, char *envp[])
{
	char	**sp;
	char	*first;

	sp = ft_split(str, ' ');
	if (!sp)
		return (NULL);
	first = find_access(envp, sp[0]);
	if (!first)
		return (freeit(sp), NULL);
	free(sp[0]);
	sp[0] = first;
	return (sp);
}

char	**createargs2(char *str, char *envp[], int *x)
{
	char	**sp;
	char	*first;

	sp = ft_split(str, ' ');
	if (!sp)
		return (NULL);
	first = find_access(envp, sp[0]);
	if (!first)
	{
		*x = 127;
		return (freeit(sp), NULL);
	}
	free(sp[0]);
	sp[0] = first;
	return (sp);
}
