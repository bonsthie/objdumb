#include <unistd.h>
#include <sys/wait.h>

char *scrap_url(const char *page)
{
	int fd[2];
	static

	if (pipe(fd) == -1)
		return (NULL);
	int pid = fork();
	if (!pid)
	{

	}
	waitpid(pid, NULL, 0);



}
