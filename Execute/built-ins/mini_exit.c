#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int status_calc(char *str)
{
    int i;
    int status;

    i = 0;
    status = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (-1);
        status = status * 10 + (str[i] - '0');
        i++;
    }
    return (status);
}

void mini_exit(t_node *node, t_list_env *env, t_son *son, int status)
{
    char *trimmed_str;
    int exit_status;

    rl_clear_history();
    t_free_node(node);
    ft_free_env_list(env);
    ft_free_token_list(node->operation);
    ft_free_son(son);

    trimmed_str = ft_strtrim(ft_strtrim(node->operation->read, "exit("), ")");
    exit_status = status_calc(trimmed_str);
    free(trimmed_str);

    if (exit_status == -1)
    {
        fprintf(stderr, "exit: numeric argument required\n");
        exit_status = 2;
    }

    exit(exit_status);
}