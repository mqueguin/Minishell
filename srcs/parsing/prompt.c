/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:42:07 by tale-fau          #+#    #+#             */
/*   Updated: 2022/02/28 02:00:09 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_strcat_here(char **dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[0][i])
		i++;
	while (src[j])
	{
		dest[0][i] = src[j];
		i++;
		j++;
	}
}

char	*display_prompt(char *prompt, t_env *env)
{
	char	*line;
	char	*tmp;
	size_t	total_len;

	line = NULL;
	tmp = NULL;
	total_len = ft_strlen(prompt) + ft_strlen(BGRN) + ft_strlen(BLK) + 3;
	tmp = ft_calloc((sizeof(char)), total_len + 1);
	if (tmp == NULL)
		return (NULL);
	tmp[total_len] = '\0';
	ft_strcat_here(&tmp, BGRN);
	ft_strcat_here(&tmp, "@");
	ft_strcat_here(&tmp, prompt);
	ft_strcat_here(&tmp, "$ ");
	ft_strcat_here(&tmp, BLK);
	line = readline(tmp);
	if (line == NULL)
	{
		ft_putstr("  ");
		cmd_exit(env, NULL, 1, 0);
		return (NULL);
	}
	free(tmp);
	return (line);
}

char	*set_prompt(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if ((ft_strncmp(env->env, "USER", 4)) == SUCCESS)
			return (ft_strdup(env->env + 5));
		env = env->next;
	}
	env = tmp;
	return (NULL);
}
