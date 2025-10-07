/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 00:30:48 by randrade          #+#    #+#             */
/*   Updated: 2025/10/02 14:56:28 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	ft_count_words(char const *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
		{
			if (s[i + 1] == ' ' || s[i + 1] == '\t' || s[i + 1] == '\0')
				count++;
		}
		i++;
	}
	return (count);
}

static int	ft_wrdlen(char const *s)
{
	int	i;

	i = 0;
	while (s[i] != ' ' && s[i] != '\t' && s[i])
		i++;
	return (i);
}

static char	*ft_wrdcpy(char const *s, char **ptr)
{
	int	i;

	i = 0;
	while (*s != ' ' && *s != '\t' && *s)
	{
		(*ptr)[i] = *s;
		i++;
		s++;
	}
	(*ptr)[i] = '\0';
	return ((char *)s);
}

char	**split_spaces(char const *s)
{
	char	**ptr;
	int		count_words;
	int		wrd_len;
	int		i;

	count_words = ft_count_words(s);
	ptr = (char **)ft_calloc((count_words + 1), sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < count_words)
	{
		while (*s == ' ' || *s == '\t')
			s++;
		wrd_len = ft_wrdlen(s);
		ptr[i] = (char *)ft_calloc(wrd_len + 1, sizeof(char));
		if (ptr[i] == NULL)
		{
			ft_free_double_array(ptr);
			return (NULL);
		}
		s = ft_wrdcpy(s, &ptr[i]);
		i++;
	}
	return (ptr);
}
