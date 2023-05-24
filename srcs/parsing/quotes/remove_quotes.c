/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:21:35 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 01:56:13 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_quote(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = (int)ft_strlen(str);
	while (i < len)
	{
		if (str[i] == DOUBLE_QUOTE)
		{
			return (DBL_Q);
		}
		else if (str[i] == SINGLE_QUOTE)
		{
			return (SGL_Q);
		}
		i++;
	}
	return (FAILURE);
}

char	*need_to_remove_quotes(char *content)
{
	if (find_quote(content) == DBL_Q)
	{
		content = remove_double_quotes(content, 0, 0);
		if (content == NULL)
			return (NULL);
	}
	else if (find_quote(content) == SGL_Q)
	{
		content = remove_single_quotes(content, 0, 0);
		if (content == NULL)
			return (NULL);
	}
	return (content);
}

char	*remove_double_quotes(char *str, int i, int j)
{
	int		len;
	char	*ret;

	len = ft_strlen(str);
	ret = NULL;
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (ret == NULL)
	{
		free(str);
		return (NULL);
	}
	ft_bzero(ret, len + 1);
	if (str[i] == DOLLAR)
		i++;
	while (str[i] == DOUBLE_QUOTE)
		i++;
	while (str[i] && i < len)
	{
		if (str[i] == DOUBLE_QUOTE)
			i++;
		else
			ret[j++] = str[i++];
	}
	free(str);
	return (ret);
}

char	*remove_single_quotes(char *str, int i, int j)
{
	int		len;
	char	*ret;

	len = ft_strlen(str);
	ret = NULL;
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (ret == NULL)
	{
		free(str);
		return (NULL);
	}
	ft_bzero(ret, ft_strlen(ret));
	if (str[i] == DOLLAR)
		i++;
	while (str[i] == SINGLE_QUOTE)
		i++;
	while (str[i] && i < len)
	{
		if (str[i] == SINGLE_QUOTE)
			i++;
		else
			ret[j++] = str[i++];
	}
	free(str);
	return (ret);
}
