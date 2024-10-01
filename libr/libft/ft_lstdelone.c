/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:09:53 by nhayoun           #+#    #+#             */
/*   Updated: 2024/04/25 12:17:28 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libr.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del((lst)->content);
	free(lst);
}
