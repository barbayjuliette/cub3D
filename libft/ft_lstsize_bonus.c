/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay<marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:29:01 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/08 20:29:11 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// int main(int argc, char const *argv[])
// {
// 	char *content = "I am the first node";
// 	t_list *list = ft_lstnew(content);

// 	t_list node;
// 	node.next = NULL;
// 	node.content = "second node";
// 	list->next = &node;

// 	int count = ft_lstsize(list);
// 	printf("There are %d nodes", count);
// 	return 0;
// }
