/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:42:07 by ahashem           #+#    #+#             */
/*   Updated: 2024/07/07 14:42:07 by ahashem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *var_expansion(char *str)
{
    char *expanded = calloc(1024, sizeof(char)); // Allocate enough space
    int i = 0, j = 0;
    char var_name[256]; // Assuming variable names are not longer than 255 characters

    while (str[i])
    {
        if (str[i] == '$')
        {
            i++;
            int k = 0;
            while (str[i] && (isalnum(str[i]) || str[i] == '_'))
            {
                var_name[k++] = str[i++];
            }
            var_name[k] = '\0';
            char *var_value = getenv(var_name);
            if (var_value)
            {
                strcpy(&expanded[j], var_value);
                j += strlen(var_value);
            }
        }
        else
        {
            expanded[j++] = str[i++];
        }
    }
    expanded[j] = '\0';
    return expanded;
}

char *expand_with_single_quotes(char *str)
{
    char *expanded = calloc(1024, sizeof(char)); // Allocate enough space
    int i = 0, j = 0;
    int in_single_quote = 0;
    char var_name[256]; // Assuming variable names are not longer than 255 characters

    while (str[i])
    {
        if (str[i] == '\'')
        {
            in_single_quote = !in_single_quote;
            expanded[j++] = str[i++];
        }
        else if (str[i] == '$' && !in_single_quote)
        {
            i++;
            int k = 0;
            while (str[i] && (isalnum(str[i]) || str[i] == '_'))
            {
                var_name[k++] = str[i++];
            }
            var_name[k] = '\0';
            char *var_value = getenv(var_name);
            if (var_value)
            {
                strcpy(&expanded[j], var_value);
                j += strlen(var_value);
            }
        }
        else
        {
            expanded[j++] = str[i++];
        }
    }
    expanded[j] = '\0';
    return expanded;
}

// char *var_expansion(char *str)
// {
//     char *expanded = calloc(1024, sizeof(char)); // Allocate enough space
//     int i = 0, j = 0;
//     char var_name[256]; // Assuming variable names are not longer than 255 characters
//     char quote = 0; // To track current quote type

//     while (str[i])
//     {
//         if (str[i] == '\'' && quote == '\"')
//         {
//             // Keep the single quote inside double quotes
//             expanded[j++] = str[i++];
//         }
//         else if (str[i] == '\'' || str[i] == '\"')
//         {
//             if (quote == 0)
//                 quote = str[i]; // Open a quote
//             else if (quote == str[i])
//                 quote = 0; // Close the quote
//             i++; // Skip the quote character
//         }
//         else if (str[i] == '$' && quote != '\'')
//         {
//             i++;
//             int k = 0;
//             while (str[i] && (isalnum(str[i]) || str[i] == '_'))
//             {
//                 var_name[k++] = str[i++];
//             }
//             var_name[k] = '\0';
//             char *var_value = getenv(var_name);
//             if (var_value)
//             {
//                 strcpy(&expanded[j], var_value);
//                 j += strlen(var_value);
//             }
//         }
//         else
//         {
//             expanded[j++] = str[i++];
//         }
//     }
//     expanded[j] = '\0';
//     return expanded;
// }

void expand_var(t_token *tokens)
{
	t_token *current;
	char *new_str;

	current = tokens;
	while (current)
	{
		if (current->type == DOUBLE || current->type == VAR)
		{
			new_str = var_expansion(current->str);
			free(current->str);
			current->str = new_str;
		}
		else if (current->type == PATH || current->type == ARG || current->type == CMD)
		{
			new_str = expand_with_single_quotes(current->str);
			free(current->str);
			current->str = new_str;
		}
		current = current->next;
	}
}

// void	expand_var(t_token *tokens)
// {
// 	t_token	*current;
// 	char	*new_str;

// 	current = tokens;
// 	while (current)
// 	{
// 		if (current->type == DOUBLE || current->type == VAR)
// 		{
// 			new_str = var_expansion(current->str);
// 			free(current->str);
// 			current->str = new_str;
// 		}
// 		else if (current->type == WORD)
// 		{
// 			new_str = var_expansion(current->str);
// 			free(current->str);
// 			current->str = new_str;
// 		}
// 		current = current->next;
// 	}
// }