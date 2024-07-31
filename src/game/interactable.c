/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:11:16 by ciusca            #+#    #+#             */
/*   Updated: 2024/07/31 21:05:34 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"
#include <time.h>


int	close_door(t_cubed *cubed, int i, int j)
{
	cubed->map[i][j] = 'D';
	return (0);
}

int	open_door(t_cubed *cubed, int i, int j)
{
	cubed->map[i][j] = 'C';
	return (0);
}

int	get_frame(t_cubed *cubed, int state, int i, int j)
{
	int	frame;
	int	change_frame;

	if (cubed->map[i][j] == 'C')
		cubed->texture[4].frame = FRAME_NUMBER - 1;
	else if (cubed->map[i][j] == 'D')
		cubed->texture[4].frame = 0;
	if (state == 0)
		change_frame = -1;
	else if (state == 1)
		change_frame = 1;
	else
		return (0);
	if ((get_curr_time(cubed->time)) % 1 == 0)// || cubed->texture[4].frame == FRAME_NUMBER - 1 || cubed->texture[4].frame == 0) 
		frame = cubed->texture[4].frame + change_frame;
	else
		frame = cubed->texture[4].frame;
	printf("frame: %d\n", frame);
	if ((frame != FRAME_NUMBER -1 || frame != 0))
	{
		cubed->map[i][j] = 'A';
	}
	if (frame < 0)
	{
		close_door(cubed, i, j);
		cubed->game->anim_state = -1;
		frame = 0;
	}
	if (frame > FRAME_NUMBER - 1)
	{
		open_door(cubed, i, j);
		cubed->game->anim_state = -1;
		frame = FRAME_NUMBER - 1;
	}
	cubed->texture[4] = cubed->door_anim[frame];
	return (frame);
}


int	player_in_door(int player_x, int player_y, char **map)
{
	int	i;
	int	j;

	i = (player_y / TILE_SIZE);
	j = (player_x / TILE_SIZE);
	if (map[i][j] == 'C')
		return (1);
	return (0);
}

void	interactable(t_cubed *cubed)
{
	t_player	*p;
	int	i;
	int	j;

	p = cubed->player;
	cubed->gui->close_door = 0;
	cubed->gui->open_door = 0;
	i = (int)((p->y + p->d_y * 40) / TILE_SIZE);
	j = (int)((p->x + p->d_x * 40) / TILE_SIZE);
	
	if (i < 0 || j < 0 || i >= cubed->game->ht || j >= cubed->game->wd)
		return ;
	// save the door position to change the character in the map
	if (cubed->map[i][j] == 'C')
		cubed->gui->close_door = 1;
	if (cubed->map[i][j] == 'D')
		cubed->gui->open_door = 1;
	if (cubed->map[i][j] == 'D' && cubed->keys->space)
		cubed->game->anim_state = 1;
	else if (cubed->map[i][j] == 'C' && cubed->keys->space && !player_in_door(p->x, p->y, cubed->map))
		cubed->game->anim_state = 0;
	
	get_frame(cubed, cubed->game->anim_state, i, j);
	//handle_doors(cubed->map, i, j);
	cubed->keys->space = 0;
}
