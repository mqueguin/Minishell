/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tale-fau <tale-fau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:10:12 by mqueguin          #+#    #+#             */
/*   Updated: 2022/02/22 22:53:28 by tale-fau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_env(int err, char *msg)
{
	if (err == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (err == 1)
	{
		ft_putstr_fd("minishell: setenv ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": Invalid argument\n", 2);
	}
	return (1);
}

static int	ft_count_line(char *str, char c)
{
	int	size;

	size = 0;
	while (*str)
	{
		if (*str == c)
			size++;
		str++;
	}
	size++;
	return (size);
}

static char	*ft_recover_line(char *str, char c, int *start)
{
	char	*line;
	int		i;
	int		tmp;
	int		k;

	i = 0;
	tmp = *start;
	while (str[tmp])
	{
		if (str[tmp] == c && i > 0)
			break ;
		i++;
		tmp++;
	}
	line = malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (NULL);
	k = 0;
	while (i > k)
	{
		line[k++] = str[*start];
		*start += 1;
	}
	line[k] = '\0';
	return (line);
}

char	**ft_mini_split(char *str, char c)
{
	char	**tab;
	int		i;
	int		j;

	tab = malloc(sizeof(char *) * (ft_count_line(str, c) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_count_line(str, c))
	{
		tab[i] = ft_recover_line(str, c, &j);
		if (tab[i] == NULL)
		{
			ft_free_tab(tab);
			return (NULL);
		}
		i++;
	}
	tab[ft_count_line(str, c)] = 0;
	return (tab);
}

char	*ft_strjoin_free_str(char *s1, char *s2, int b_free, int i)
{
	char	*ret;
	size_t	len;
	int		j;

	if (!s2)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	ret = ft_calloc(1, len);
	if (ret == NULL)
		return (NULL);
	j = 0;
	if (s1)
		while (s1[i])
			ret[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		ret[j] = s2[i++];
		j++;
	}
	ret[j] = '\0';
	if (b_free == 1)
		free(s1);
	return (ret);
}
