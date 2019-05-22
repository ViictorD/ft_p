/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:51:12 by vdarmaya          #+#    #+#             */
/*   Updated: 2019/05/17 17:16:49 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	send_err_msg(int client, char *msg)
{
	return (send_data(client, msg, ft_strlen(msg), 501));
}

int			command_del(int client, char *cmd, char **argv)
{
	pid_t		pid;
	int			fd;
	char		*data;
	size_t		data_length;

	if (ft_tablen(argv) > 2 || *argv[1] == '-')
		return (send_err_msg(client, "Usage: rm <file>"));
	ft_strdel(argv);
	argv[0] = ft_strdup(cmd);
	pid = fork();
	fd = open(g_out, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!pid)
	{
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		execv(cmd, (char *const*)argv);
		exit(1);
	}
	if (pid > 0)
		wait4(0, NULL, 0, NULL);
	data_length = ft_readfile(fd, &data);
	close(fd);
	send_data(client, data, (data_length == (size_t)-1) ? 0 : data_length, 200);
	ft_strdel(&data);
	return (200);
}
