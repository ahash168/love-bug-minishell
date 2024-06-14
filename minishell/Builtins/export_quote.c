/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <mgordag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 01:20:16 by mgordag           #+#    #+#             */
/*   Updated: 2022/10/18 09:36:18 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

char	**set_export_quote(char **export)
{
	int		line;
	char	**ret;
	char	*var_name;
	char	*var_data;
	char	*quote_data;

	line = -1;
	ret = malloc(sizeof(char *) * count_line(export) + 1);
	while (++line < count_line(export))
	{
		var_name = get_var_name(export[line]);
		var_data = get_var_data(export[line]);
		exp_data_add_quote(var_name, var_data, &quote_data);
		ret[line] = ft_strjoin(var_name, quote_data);
		free_two_str(&var_name, &var_data);
		free(quote_data);
	}
	ret[count_line(export)] = NULL;
	return (ret);
}
