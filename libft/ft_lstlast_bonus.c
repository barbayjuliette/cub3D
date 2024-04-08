/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay<marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:39:23 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/08 20:39:31 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// int main(void)
// {
// 	char *content = "I am the first node";
// 	t_list *list = ft_lstnew(content);

// 	t_list node;
// 	node.next = NULL;
// 	node.content = "second node";
// 	list->next = &node;

// 	printf("Content: %s\n", (char *)ft_lstlast(list)->content);
// 	return 0;
// }
