/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   petitshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztaouil <ztaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 16:43:50 by ztaouil           #+#    #+#             */
/*   Updated: 2021/09/02 19:18:42 by ztaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PETITSHELL_H
# define PETITSHELL_H

# include "../parser/parser.h"
# include "../list/list.h"
# include "../libft/libft.h"
# include "../signals/signal.h"
# include "../builtins/builtins.h"//
# include "../execution/execution.h"
# include <unistd.h>

void		execution_loop(t_wrapper *wrp);

#endif