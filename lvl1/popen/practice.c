/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:57:56 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/08/21 11:03:03 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

static void close_fodas(int fd[2])
{
	close(fd[0]);
	close(fd[0]);
}

int ft_popen(const char *file, char *const argv[], char type)
{
	int mango;
	int fd[2];

	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	
	if (pipe(fd) == -1)
		return (-1);

	mango = fork();
	if (mango == -1)
		return (close_fodas(fd), -1);

	if (mango == 0)
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
		exit(-1);
	}
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

int main()
{
	return 0;
}
