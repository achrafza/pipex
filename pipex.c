#include "pipex.h"
#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
char  *parse_envp(char *envp[])
{
  int i;
  i = 0;
  while(envp[i])
  {
    if(ft_strnstr(envp[i] ,"PATH=", 5) != NULL)
      return (envp[i]);
    i++;
  }
  return (NULL);
}
char *find_access(char *path[],char *commande){
  if(!access(commande, F_OK | X_OK)) return commande;
  char *acualpath = parse_envp(path);
  if(!acualpath)
    return (NULL);
  char **sp = ft_split(acualpath + 5, ':');
  if(!sp)
    return (NULL);
  char *joinedpath;
  int i =0;
  int acc;
  char *com;
  while(sp[i])
  {
    if(i) free(joinedpath), free(com);
    com = ft_strjoin("/",commande);
    
    joinedpath = ft_strjoin(sp[i],com);
    acc = access(joinedpath, F_OK | X_OK);
    if(!acc) return (joinedpath);
    i++;
  }
  return (NULL);
}
char **createargs(char *str,char *envp[]){
  char **sp =  ft_split(str, ' ');
  char *first = find_access(envp,sp[0]);
  if (!first || !sp) return (free(sp),NULL);
  sp[0] = first;
  return (sp);
}
int avtests(char* av[]){
  int i = 0;
  while(i < 5){
    if (av[i][0] =='\0') return 0;
    i++;
  }
  return 1;
}
int main(int ac, char *av[],char *envp[])
{
  int fdoutfile;
  int fdinfile;
  if (ac != 5 || !avtests(av)) return 1; 
  int fd[2];
  if(pipe(fd) == -1) return (perror("fail to pype"),1);
  char **createarg = createargs(av[2],envp);
  if(!createarg) return 1;
  fdinfile = open(av[1],O_RDWR, 0777); /*newly added*/
  if (fdinfile == -1){ perror("");exit(1);}
  int pidin = fork();
  if(pidin < 0) {
    perror("failed to fork\n");
    return (1);
  }
  if(pidin == 0){
    //fdinfile = open(av[1],O_RDWR, 0777);
    //if (fdinfile == -1){ perror("");exit(1);}
    if (dup2(fdinfile,0) == -1)
      return (perror("fail to dup2"),1);
    if (dup2(fd[1], 1) == -1)
      return (perror("fail to dup2"),1);
    close(fd[0]), close(fd[1]), close(fdinfile);
    execve(createarg[0],createarg,envp);
    perror("execve failed");
    exit(1);
    //(free(createarg), close(fdinfile),close(fd[1]),close(fd[0]));
    exit(1);
  }
  free(createarg);
  createarg = createargs(av[3], envp);
  if (!createarg) return (perror("command not found"),1);
  fdoutfile = open(av[4],O_CREAT | O_RDWR,0777);
  if (fdoutfile == -1) {perror("");exit(1);}
  int pidout = fork();
  if(pidout < 0) {
    perror("failed to fork\n");
    return (1);
  }
  if (pidout == 0){
    printf("1");
    //fdoutfile = open(av[4],O_CREAT | O_RDWR,0777);
    //if (fdoutfile == -1) {perror("");exit(1);}
    if(dup2(fd[0], 0) == -1) return (perror("fail to dup2"),1);
    if(dup2(fdoutfile,1) == -1) return (perror("fail to dup2"),1);
    close(fd[0]),close(fd[1]),close(fdoutfile);
    execve(createarg[0],createarg,envp);
    free(createarg);
    perror("exec failed to write in pipe");
    exit(1);
  }
  free(createarg);
  close(fd[1]);
  close(fd[0]);
  close(fdinfile);
  close(fdoutfile);
  waitpid(pidin, NULL, 0);
  waitpid(pidout, NULL, 0);
  exit(0);
}
