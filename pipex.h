/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 07:07:24 by azahid            #+#    #+#             */
/*   Updated: 2025/02/07 07:07:49 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

char	**parse_envp(char *envp[]);
char	*find_access(char *path[], char *commande);
char	**createargs1(char *str, char *envp[]);
char	**createargs2(char *str, char *envp[], int *x);
int		avtests(char *av[]);
void	freeit(char **str);
pid_t	file_in(int *fd, char **createarg, char **av, char **envp);
pid_t	file_out(int *fd, char **createarg, char **av, char **envp);

#endif
