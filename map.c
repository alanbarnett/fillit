/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 15:36:47 by abarnett          #+#    #+#             */
/*   Updated: 2018/06/19 12:15:10 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
check line
see if row of piece fits in line
check below line at the same index if row of piece fits in that line
keep going until it either can't do it, or all the lines in the piece are checked
bitwise or each row recursively
*/

#include "libft.h"
#include "fillit.h"

void	place_mino(uint16_t map[], t_list *mino)
{
	int i;

	i = -1;
	map += Y(mino);
	while (++i < 4)
		*map++ ^= R(i, mino) >> X(mino);
}

int		find_spot(uint16_t map[], int size, t_list *mino, int row)
{
//	ft_putstr("size: ");
//	ft_putnbr(size);
//	ft_putstr(" | Y: ");
//	ft_putnbr(Y(mino));
//	ft_putstr(" | row: ");
//	ft_putnbr(row);
//	ft_putchar('\n');
	if (!map || (((Y(mino)  + row) >= size) && (R(row, mino) > 0)))
		return (-1);
	if (X(mino) >= (size - 3) && (BITS(mino) & (0x1111 << ((X(mino) - (size - 3))))))
	{
//		ft_putstr("going up to line: ");
		Y(mino)++;
//		ft_putnbr(Y(mino));
//		ft_putchar('\n');
//		ft_putstr("line bits: ");
//		print_bits(*(map + Y(mino)), 16);
//		ft_putchar('\n');
		X(mino) = 0;
		return (find_spot(map, size, mino, 0));
	}
	if (row == 0)
	{
//		ft_putendl("here");
		if (XOROR(*(map + Y(mino)), (R(row, mino) >> X(mino))))
		{
//			ft_putendl("going in here");
			if (find_spot(map + 1, size, mino, row + 1))
			{
//				ft_putendl("further in here");
				return (find_spot(map + 1, size, mino, row + 1));
			}
		}
//		ft_putstr("skipping x: ");
//		ft_putnbr(X(mino));
//		ft_putstr(" y: ");
//		ft_putnbr(Y(mino));
//		ft_putchar('\n');
		X(mino)++;
//		ft_putstr("onto x: ");
//		ft_putnbr(X(mino));
//		ft_putchar('\n');
		return (find_spot(map, size, mino, row));
	}
	if (row < 4 && XOROR(*(map + Y(mino)), (R(row, mino) >> X(mino))))
	{
//		ft_putstr("row: ");
//		ft_putnbr(row);
//		ft_putchar('\n');
		return (find_spot(map + 1, size, mino, row + 1));
	}
	else
		return (XOROR(*(map + Y(mino)), (R(row, mino) >> X(mino))));
}

void	fill_map(uint16_t map[], int *size, t_list *head)
{
	int		i;
	t_list	*cur;

	i = 1;
	cur = head;
	while (*size < 16)
	{
		while (cur->content && find_spot(map, *size, cur, 0) != -1)
		{
//			ft_putstr("piece ");
//			ft_putnbr(i);
//			ft_putchar('\n');
//			ft_putnbr(X(cur));
//			ft_putstr(", ");
//			ft_putnbr(Y(cur));
//			ft_putchar('\n');
			place_mino(map, cur);
//			print_map(map);
			cur = cur->next;
			i++;
		}
		if (!cur->content)
			return ;
		cur = head;
		ft_bzero(map, sizeof(uint16_t) * 16);

		(*size)++;
	}
}

int		ft_lstlen(t_list *head)
{
	int	count;

	count = 0;
	while (head && head->content)
	{
		count++;
		head = head->next;
	}
	return (count);
}

void	map_main(t_list *head)
{
	uint16_t	map[16];
	int			count;
	int			size;

	ft_bzero(map, sizeof(uint16_t) * 16);

	count = ft_lstlen(head);
	size = 2;
//	ft_putnbr(count);
//	ft_putchar('\n');
//	ft_putnbr(count * 4);
//	ft_putchar('\n');
	while (size * size <= count * 4)
		++size;
	--size;
//	ft_putnbr(size);
//	ft_putchar('\n');
	fill_map(map, &size, head);
//	ft_putnbr(size);
//	ft_putchar('\n');
	print_map(head, size);
 }
