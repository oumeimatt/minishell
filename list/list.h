/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-yous <oel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 19:28:40 by oel-yous          #+#    #+#             */
/*   Updated: 2021/09/04 19:28:41 by oel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

t_list		*new_list(void *data);
t_list		*last_list(t_list *lst);
int			size_list(t_list *lst);
void		addback_list(t_list **alst, t_list *lst);
void		destroy_list(t_list *lst);

#endif