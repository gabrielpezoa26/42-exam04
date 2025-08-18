/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:57:56 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/08/18 18:54:15 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void close_fd(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int ft_popen(const char *file, char *const argv[], char type)
{
	int	fd[2];
	int	pid;

	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);

	if (pipe(fd) == -1)
		return (close_fd(fd), -1);

	pid = fork();
	if (pid == -1)
		return (close_fd(fd), -1);

	// processo filho
	if (pid == 0)
	{
		if (type == 'r')
		{
			close(fd[0]);
			if (dup2(fd[1], STDOUT_FILENO) == -1)
			{
				close(fd[1]);
				exit(-1);
			}
			close(fd[1]);
		}
		else
		{
			close(fd[1]);
			if (dup2(fd[0], STDIN_FILENO) == -1)
			{
				close(fd[0]);
				exit(-1);
			}
			close(fd[0]);
		}
		execvp(file, argv);
		exit (-1);
	}

	//processo pai
	if (type == 'r')
	{
		close(fd[1]);
		return (fd[0]);
	}
	else
	{
		close(fd[0]);
		return (fd[1]);
	}
	return (-1);
}


int	main() {
	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	dup2(fd, 0);
	fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
	char	*line;
	while ((line = get_next_line(fd)))
		printf("%s", line);
}


// int main()
// {
//     int  fd;
//     char line[9999];
// 	int		b_read;

//     fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
// 	dup2(fd, STDIN_FILENO);
// 	close(fd);
// 	fd = ft_popen("wc", (char *const []){"wc", "-l", NULL}, 'w');
//     while (b_read = read(0, line, 9999))
// 	{
// 		line[b_read] = '\0';
// 		write(fd, line, b_read);
// 	}
// 	close(fd);
//     return (0);
// }


// Assignment name  : ft_popen
// Expected files   : ft_popen.c
// Allowed functions: pipe, fork, dup2, execvp, close, exit
// --------------------------------------------------------------------------------------

// Write the following function:

// int ft_popen(const char *file, char *const argv[], char type);

// The function must launch the executable file with the arguments argv (using execvp).
// If type is 'r' the function must return a file descriptor connected to the output of the command.
// If type is 'w' the function must return a file descriptor connected to the input of the command.
// In case of error or invalid parameter the function must return -1.