/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:47:46 by nromito           #+#    #+#             */
/*   Updated: 2024/07/15 00:27:12 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

/* pixel put velocizzata */
void	better_pixel_put(t_img *img, int x, int y, int color)
{
	int offset;
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(offset + img->pixel_ptr)) = color;
}


/* per mettere pixel piu velocemente alloco spazio di memoria come per un immagine
poi faccio il pixel put piu veloce dentro quella 'immagine' specificando un colore*/
void	create_img(t_img *img, void *mlx, int size, int color)
{
	//img = malloc(sizeof(t_img));
	img->img = mlx_new_image(mlx, size, size);
	img->pixel_ptr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_len, &img->endian);

	// si puo cambiare con il while
	for (int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			better_pixel_put(img, j, i, color);
		}
	}
	
}

int	main(int argc, char **argv)
{
	t_cubed		cubed;
	t_img		*img;

	(void)argv;
	if (argc != 2)
		return (ft_putendl_fd(USAGE, 2), 1);
	parsing(argv, argc);
		//check_map(argv[1])
	screen_setting(&cubed);
	img = malloc(sizeof(t_img));
	cubed.img = img;
	create_img(img, cubed.mlx, 8, 0x00FF00);
	mlx_put_image_to_window(cubed.mlx, cubed.window, cubed.img->img, 300, 300);
	//mlx_key_hook(cubed.window, &key_events, &cubed);
	mlx_hook(cubed.window, 17, 1L << 17, &ft_close, &cubed);
	mlx_hook(cubed.window, 02, 1L<<0, &key_events, &cubed);
	// rendering();
	mlx_loop(cubed.mlx);
	return (0);
}
