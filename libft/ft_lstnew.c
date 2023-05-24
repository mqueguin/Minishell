/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 23:15:04 by tale-fau          #+#    #+#             */
/*   Updated: 2021/06/02 16:00:02 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
