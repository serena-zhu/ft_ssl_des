/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yazhu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 17:27:33 by yazhu             #+#    #+#             */
/*   Updated: 2018/01/22 19:36:07 by yazhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

void				initialize_opt(t_opt *opt)
{
	opt->encrypt = 1;
	opt->base64 = 0;
	opt->b64_s = ft_strnew(4);;
//	opt->nopad = 0;
	opt->fd_in = 0;
	opt->fd_out = 1;
}

static void			populate_i_o(int argc, char **argv, int j, t_opt *opt)
{
	if (j >= argc)
		errors(argv, j, 1);
	else if (ft_strcmp(argv[j - 1], "-i") == 0)
	{
		if ((opt->fd_in = open(argv[j], O_RDONLY)) < 0)
			(j < argc) ? errors(argv, j, 4) : exit(1);
	}
	else
		opt->fd_out = j;
}

char				*populate_data(int argc, char **argv, char *key, t_opt *opt)
{
	int j;

	j = 2;
	while (j < argc)
	{
		if (ft_strcmp(argv[j], "-a") == 0 || ft_strcmp(argv[j], "-base64") == 0)
			opt->base64 = 1;
		else if (ft_strcmp(argv[j], "-d") == 0)
			opt->encrypt = 0;
		else if (ft_strcmp(argv[j], "-e") == 0)
			opt->encrypt = 1;
		else if (ft_strcmp(argv[j], "-i") == 0 || ft_strcmp(argv[j], "-o") == 0)
			populate_i_o(argc, argv, ++j, opt);
		else if (ft_strcmp(argv[j], "-k") == 0 && ++j)
			(j < argc) ? key = argv[j] : errors(argv, j, 2);
//		else if (ft_strcmp(argv[j], "-nopad") == 0)
//			opt->nopad = 1;
		else
			errors(argv, j, 3 * (argv[j][0] == '-'));
		j++;
	}
	if (opt->fd_out != 1 && (opt->fd_out = open(argv[opt->fd_out], O_CREAT
											| O_TRUNC | O_WRONLY, 0666)) < 0)
		exit(1);
	return (key);
}
