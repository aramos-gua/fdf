/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:21:02 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/02/22 10:21:35 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ll_fclean(gnl_list *start)
{
	gnl_list	*temp;

	while (start)
	{
		temp = (start)->next;
		free(start);
		start = temp;
	}
	start = NULL;
	return (NULL);
}

int	ft_final_len(gnl_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size += ft_strlen(lst->buffer);
		lst = lst -> next;
	}
	return (size);
}
