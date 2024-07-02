#include "../../minishell.h"

void	execute_commands(t_parsed_commands parsed_commands, t_env *my_env)
{
	int i;
	i = 0;
	while (i < parsed_commands.commands_length)
	{
		execute(parsed_commands.commands[i], parsed_commands.input_file, parsed_commands.output_file, my_env);
		i++;
	}
}