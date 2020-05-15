/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 19:15:12 by jlensing      #+#    #+#                 */
/*   Updated: 2020/04/07 02:13:14 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	while (lst != NULL)
	{
		if (lst->content != NULL)
			f(lst->content);
		lst = lst->next;
	}
}
