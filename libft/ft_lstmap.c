/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 22:51:07 by tale-fau          #+#    #+#             */
/*   Updated: 2021/01/07 23:28:22 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = ft_lstnew(f(lst->content));
	new = tmp;
	while (lst->next)
	{
		lst = lst->next;
		new->next = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		new = new->next;
	}
	return (tmp);
}
