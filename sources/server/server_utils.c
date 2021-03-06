/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:51:44 by vdarmaya          #+#    #+#             */
/*   Updated: 2019/05/14 18:51:45 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			send_data(int client, const void *data, size_t size, int reply)
{
	int		ret;

	send(client, &reply, sizeof(int), 0);
	ret = send(client, &size, sizeof(size_t), 0);
	if (ret == -1)
		printf("Failed to deliver data size.\n");
	if (!size)
		return (0);
	ret = send(client, data, size, 0);
	if (ret == -1)
		printf("Failed to deliver data.\n");
	return (reply);
}
