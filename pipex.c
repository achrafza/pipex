/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 05:13:14 by azahid            #+#    #+#             */
/*   Updated: 2025/02/07 07:05:26 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	avtests(char *av[])
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (!av[i] || av[i][0] == '\0')
			return (0);
		i++;
	}
	return (1);
}

void	freeit(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

pid_t	file_in(int *fd, char **createarg, char **av, char **envp)
{
	int	fdinfile;
	int	pidin;

	fdinfile = open(av[1], O_RDWR, 0777);
	if (fdinfile == -1)
		return (close(fd[0]), close(fd[1]), perror("fail to fd"), -1);
	pidin = fork();
	if (pidin < 0)
		return (close(fdinfile), close(fd[0]), close(fd[1]), freeit(createarg),
			perror("failed to fork"), -1);
	if (pidin == 0)
	{
		if (dup2(fdinfile, 0) == -1 || dup2(fd[1], 1) == -1)
			return (close(fdinfile), close(fd[0]), close(fd[1]),
				freeit(createarg), perror("fail to dup2"), -1);
		close(fd[0]);
		close(fd[1]);
		close(fdinfile);
		if (createarg)
			execve(createarg[0], createarg, envp);
		perror("execve failed");
		exit(1);
	}
	close(fd[1]);
	return (pidin);
}

pid_t	file_out(int *fd, char **createarg, char **av, char **envp)
{
	int	fdoutfile;
	int	pidout;

	fdoutfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (!createarg || fdoutfile == -1)
		return (close(fd[0]), perror("cnf"), -1);
	pidout = fork();
	if (pidout < 0)
		return (close(fd[0]), close(fdoutfile), freeit(createarg),
			perror("ftf"), -1);
	if (pidout == 0)
	{
		if (dup2(fd[0], 0) == -1 || dup2(fdoutfile, 1) == -1)
			return (close(fd[0]), close(fdoutfile), freeit(createarg),
				perror("ftd"), -1);
		close(fd[0]);
		close(fdoutfile);
		if (createarg)
			execve(createarg[0], createarg, envp);
		freeit(createarg);
		perror("exec failed to write in pipe");
		exit(1);
	}
	close(fd[0]);
	return (pidout);
}

int	main(int ac, char *av[], char *envp[])
{
	static int	status;
	int			fd[2];
	char		**createarg;
	int			pidin;
	int			pidout;

	if (ac != 5 || !avtests(av))
		return (1);
	if (pipe(fd) == -1)
		return (perror("fail to pipe"), 1);
	createarg = createargs1(av[2], envp);
	pidin = file_in(fd, createarg, av, envp);
	freeit(createarg);
	createarg = createargs2(av[3], envp, &status);
	pidout = file_out(fd, createarg, av, envp);
	freeit(createarg);
	if (status == 127)
		exit(127);
	if (pidin > 0)
		waitpid(pidin, &status, 0);
	if (pidout == -1)
		return (close(fd[0]), close(fd[1]), 1);
	if (pidout > 0)
		waitpid(pidout, &status, 0);
	exit(WEXITSTATUS(status));
}
