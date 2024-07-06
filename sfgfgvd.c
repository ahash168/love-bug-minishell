#include "../../minishell.h"

void	print_cmds(t_cmd *head)
{
	int		i = 1;
	int		x = 0;
	t_cmd	*current = head;
	
	while (current != NULL)
	{
		printf("x: %d\n", x);		
		i = 1;
		printf("CMD: %s$\n", current->cmd[0]);
		while (current->cmd[i] != NULL)
			printf("ARG: %s$\n", current->cmd[i++]);
		current = current->next;
		x++;
	}
}

int	fill_cmd(t_token *token, t_cmd *cmd)
{
	int		i;
	int		j;
	t_token	*current;

	i = 0;
	j = 1;
	current = token;
	printf("entered fill cmd\n");
	while (current && current->type != PIPE) 
	{
		current = current->next;
		i++;
	}
	cmd->cmd = ft_calloc(i, sizeof(char *));
	printf("number of things before/after pipe: %d\n", i);
	i = 0;
	current = token;
	while (current && current->type != PIPE)
	{
		printf("before put cmd into struct\n");
		if (current->type == CMD)
			cmd->cmd[0] = current->str;
		else if (current->type == ARG)
			cmd->cmd[j++] = current->str;
		else if (current->type == SPACES)
			cmd->cmd[j++] = current->str;
		printf("after putting cmd and args in struct\n");
		current = current->next;
		i++;
	}
	cmd->cmd[j] = NULL;
	printf("count: %d\n", i);
	return (i);
}

t_cmd	*cmd_maker(t_token *tokens)
{
	int		i;
	t_token	*current;
	t_cmd	*cmds_list;
	t_cmd	*current_cmd;
	t_cmd	*last_cmd;
	
	current = tokens;
	cmds_list = NULL;
	last_cmd = NULL;
	while (current)
	{
		current_cmd = ft_calloc(1, sizeof(t_cmd));
		printf("before fill cmd\n");
		i = fill_cmd(current, current_cmd);
		printf("after fill cmd\n");
		printf("%s\n", current_cmd->cmd[0]);
		if (!cmds_list)
			cmds_list = current_cmd;
		else
			last_cmd->next = current_cmd;
		last_cmd = current_cmd;
		while (current && i-- >= 0)
			current = current->next;
		// if (current->type == PIPE)
		// 	current = current->next;
		// print_cmds(current_cmd);
		printf("after cmd while loop\n");
	}
	return (cmds_list);
}

void	init_cmds(t_token *tokens)
{
	t_cmd	*cmds;
	
	cmds = NULL;
	// printf("before cmd maker\n");
	cmds = cmd_maker(tokens);
	// printf("done with cmds making\n");
	print_cmds(cmds);
}
