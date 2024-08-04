/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:29:17 by nromito           #+#    #+#             */
/*   Updated: 2024/08/04 16:21:12 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"	
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define RESET "\033[0m"

# define ERROR "$RED Error $RESET: "

# define USAGE "\n\033[1;31mUsage\033[0m: \033[1;32m./cub3D path/to/map\033[0m\n"

// make all error wwords in red
#define SYNTAX "\033[1;31mError\033[0m: syntax error\n"



#endif