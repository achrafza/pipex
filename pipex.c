#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

char	*parse_envp(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			return (envp[i]);
		i++;
	}
	return (NULL);
}
void	freeit(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i++]);
	}
	free(str);
	str = NULL;
}
char	*find_access(char *path[], char *commande)
{
	char	*acualpath;
	char	**sp;
	char	*joinedpath;
	int		i;
	char	*com;

	if (!access(commande, F_OK | X_OK))
		return (commande);
	acualpath = parse_envp(path);
	if (!acualpath)
		return (NULL);
	sp = ft_split(acualpath + 5, ':');
	if (!sp)
		return (NULL);
	i = 0;
	while (sp[i])
	{
		if (i)
			(free(joinedpath), free(com));
		com = ft_strjoin("/", commande);
		if (!com)
			return (freeit(sp), NULL);
		joinedpath = ft_strjoin(sp[i], com);
		if (!joinedpath)
			return (freeit(sp), free(com), NULL);
		if (!access(joinedpath, F_OK | X_OK))
			return (freeit(sp), free(com), joinedpath);
		i++;
	}
	return (free(joinedpath), free(com), freeit(sp), NULL);
}
char	**createargs(char *str, char *envp[])
{
	char	**sp;
	char	*first;
	char	*temp;

	sp = ft_split(str, ' ');
	if (!sp)
		return (NULL);
	first = find_access(envp, sp[0]);
	if (!first)
		return (freeit(sp), NULL);
	temp = sp[0];
	sp[0] = first;
	return (free(temp), sp);
}
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
int	main(int ac, char *av[], char *envp[])
{
	int		fdoutfile;
	int		fdinfile;
	int		fd[2];
	char	**createarg;
	int		pidin;
	int		pidout;

	if (ac != 5 || !avtests(av))
		return (1);
	if (pipe(fd) == -1)
		return (perror("fail to pype"), 1);
	createarg = createargs(av[2], envp);
	fdinfile = open(av[1], O_RDWR, 0777);
	if (fdinfile == -1)
		(close(fd[0]), close(fd[1]),perror("fail to fd"));
	pidin = fork();
	if (pidin < 0)
	{
		perror("failed to fork\n");
		return (close(fdinfile), close(fd[0]), close(fd[1]), freeit(createarg),
			1);
	}
	if (pidin == 0)
	{
		if (dup2(fdinfile, 0) == -1)
			return (close(fdinfile), close(fd[0]), close(fd[1]),
				freeit(createarg), perror("fail to dup2"), 1);
		if (dup2(fd[1], 1) == -1)
			return (close(fdinfile), close(fd[0]), close(fd[1]),
				freeit(createarg), perror("fail to dup2"), 1);
		(close(fd[0]), close(fd[1]), close(fdinfile));
		if(createarg)
      execve(createarg[0], createarg, envp);
		perror("execve failed");
		exit(1);
	}
	freeit(createarg);
	createarg = createargs(av[3], envp);
	if (!createarg)
		(close(fd[0]), close(fd[1]), close(fdinfile), perror("cnf"));
	fdoutfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fdoutfile == -1)
		return (freeit(createarg), close(fd[0]), close(fd[1]), close(fdoutfile),
			perror("cnf"), 1);
	pidout = fork();
	if (pidout < 0)
		return (freeit(createarg), close(fd[0]), close(fd[1]), close(fdoutfile),
			perror("ftf"), 1);
	if (pidout == 0)
	{
    if (dup2(fd[0], 0) == -1)
			return (free(createarg), close(fd[0]), close(fd[1]),
				close(fdoutfile), perror("ftd"), 1);
		if (dup2(fdoutfile, 1) == -1)
			return (free(createarg), close(fd[0]), close(fd[1]),
				close(fdoutfile), perror("ftd"), 1);
	  (close(fd[0]), close(fd[1]), close(fdoutfile));
    if(createarg)
		  execve(createarg[0], createarg, envp);
		//freeit(createarg);
		perror("exec failed to write in pipe");
		exit(1);
	}
	freeit(createarg);
	close(fd[1]);
	close(fd[0]);
	close(fdinfile);
	close(fdoutfile);
	waitpid(pidin, NULL, 0);
	waitpid(pidout, NULL, 0);
	exit(0);
}
