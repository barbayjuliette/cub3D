/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:43:30 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/07 17:43:33 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}

// int main(void)
// {
// 	char *content = "hello world";

// 	t_list *list = ft_lstnew(content);
// 	if (list)
// 	{
// 		printf("This is the content of my list: %s\n", (char *)list->content);
// 	}
// 	return 0;
// }