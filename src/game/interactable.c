/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:11:16 by ciusca            #+#    #+#             */
/*   Updated: 2024/08/03 22:47:27 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubed.h"

int	check_last_frame(int frame, t_cubed *cubed, int i, int j)
{
	if (frame < 0)
	{
		cubed->map[i][j] = 'D';
		cubed->game->anim_state = -1;
		frame = 0;
	}
	if (frame > FRAME_NUMBER - 1)
	{
		cubed->map[i][j] = 'C';
		cubed->game->anim_state = -1;
		frame = FRAME_NUMBER - 1;
	}
	return (frame);
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
	if ((get_curr_time(cubed->time)) % 1 == 0)
		frame = cubed->texture[4].frame + change_frame;
	else
		frame = cubed->texture[4].frame;
	if ((frame != FRAME_NUMBER -1 || frame != 0))
		cubed->map[i][j] = 'A';
	frame = check_last_frame(frame, cubed, i, j);
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

int	*save_door_pos(int i, int j, t_cubed *cubed)
{
	static int	door_pos[2];
	t_player	*p;

	p = cubed->player;
	if (cubed->map[i][j] == 'D' && cubed->keys->space)
	{
		door_pos[0] = i;
		door_pos[1] = j;
		cubed->game->anim_state = 1;
	}
	else if (cubed->map[i][j] == 'C' && cubed->keys->space
			&& !player_in_door(p->x, p->y, cubed->map))
	{
		door_pos[0] = i;
		door_pos[1] = j;
		cubed->game->anim_state = 0;
	}
	return (door_pos);
}

void	interactable(t_cubed *cubed)
{
	t_player		*p;
	int				i;
	int				j;
	int				*door_pos;

	p = cubed->player;
	cubed->gui->close_door = 0;
	cubed->gui->open_door = 0;
	i = (int)((p->y + p->d_y * 40) / TILE_SIZE);
	j = (int)((p->x + p->d_x * 40) / TILE_SIZE);
	if (i < 0 || j < 0 || i >= cubed->game->ht || j >= cubed->game->wd)
		return ;
	if (cubed->map[i][j] == 'C')
		cubed->gui->close_door = 1;
	if (cubed->map[i][j] == 'D')
		cubed->gui->open_door = 1;
	door_pos = save_door_pos(i, j, cubed);
	if (door_pos[0] != 0 && door_pos[1] != 0)
	{
		i = door_pos[0];
		j = door_pos[1];
	}
	get_frame(cubed, cubed->game->anim_state, i, j);
	cubed->keys->space = 0;
}
