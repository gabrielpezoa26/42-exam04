/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcesar-n <gcesar-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:44:56 by gcesar-n          #+#    #+#             */
/*   Updated: 2025/08/20 16:52:58 by gcesar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int    picoshell(char **cmds[])
{
	if (!cmds || !cmds[0])
		return (1);

	pid_t pid;
	int status;
	int fd[2];
	int in_fd;
	int result = 0;
	int i = 0;
	int kids = 0;



	while(cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(fd) == -1)
				return (1);
		}
		else
		{
			fd[0] = -1;
			fd[1] = -1;
		}
		pid = fork();
		if (pid == -1)
			return (1);



		if (pid == 0)
		{
			if (in_fd != -1)
			{
				dup2(in_fd, 0);
				close(in_fd);
			}
			if (fd[1] != -1)
			{
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
			execvp(cmds[i][0], [i]);
			exit(1);
		}


		
		kids++;
		if (in_fd != -1)
			close(in_fd);
		if (fd[1] != -1)
			close(fd[1]);
		in_fd = fd[0];
		i++;
	}
	if (in_fd != -1)
		close(in_fd);
	while(kids--)
	{
		if (wait(&status) == -1)
			result = 0;
		else if(!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			result = 0;
	}
	return (result);
}
