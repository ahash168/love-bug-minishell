#include "../../minishell.h"

void	execute(char **command, int input_file, int output_file, t_env *my_env)
{
	(void)output_file, (void)input_file;
	if (is_builtin_input(command[0]) == 0)
        exec_builtin(command, my_env);
}