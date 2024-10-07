#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <string.h>
#include <bsd/string.h>
#include <stdio.h>
#include <ctype.h>

#include <stdlib.h>
#include <sys/mman.h>

char	*strjoin(char const *s1, char const *s2)
{
	size_t	length_s1;
	size_t	length_s2;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	length_s1 = strlen(s1);
	length_s2 = strlen(s2);
	dest = malloc((length_s1 + length_s2 + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	memcpy(dest, s1, length_s1 + 1);
	memcpy(dest + length_s1, s2, length_s2 + 1);
	return (dest);
}

static long	get_file_size(int fd)
{
	long	filesize;

	filesize = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	return (filesize);
}

char    *get_temp_file(char *head, int size)
{
    int        urandom;
    char    *rand;
    char    *tmp;

    rand = calloc((size + 1), sizeof(char));
    urandom = open("/dev/urandom", O_RDONLY);
    if (urandom < 0)
        return (NULL);
    read(urandom, rand, size);
    close(urandom);
    tmp = rand;
    while (size--)
    {
        while (!(isalnum(*rand)))
            *rand = (unsigned char) *rand % 93 + 33;
        rand++;
    }
	rand = tmp;
    char *result = strjoin(head, rand);
	free(rand);
	return (result);
}

char *map_file_to_buffer(const char *file)
{
	int tmp_file_fd = open(file, O_RDWR);
	char *result = mmap(NULL, get_file_size(tmp_file_fd), PROT_READ | PROT_WRITE, MAP_PRIVATE, tmp_file_fd, 0);
	close (tmp_file_fd);
	return (result);
}


char *scrap_url(const char *page)
{
	char *tmp_file;
	static char *cmd[5] = { 
		"/bin/wget",
		NULL,
		"-O",
		NULL,
		NULL,
	};

	tmp_file = get_temp_file("/tmp/", 249);
	if (!tmp_file)
		return (NULL);
	int pid = fork();
	if (!pid)
	{
		cmd[1] = (char *)page;
		cmd[3] = tmp_file;
		execve(*cmd, cmd, NULL);
		exit(1);

	}
	waitpid(pid, NULL, 0);

	char *result = map_file_to_buffer(tmp_file);
	free(tmp_file);
	return (result);
}
