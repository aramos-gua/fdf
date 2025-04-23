/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:21:32 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/02/22 10:21:34 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "../libft.h"

typedef struct gnl_s_list
{
	char			buffer[BUFFER_SIZE + 1];
	struct gnl_s_list	*next;
	int				fd;
}	gnl_list;

char	*get_next_line(int fd);
void	*ll_fclean(gnl_list *current);
int		ft_final_len(gnl_list *lst);
#endif
