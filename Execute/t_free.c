#include "minishell.h"

// Recursive function to free the AST
void	t_free_node(t_node *node)
{
    if (node == NULL)
        return ;
    t_free_node(node->left);
    t_free_node(node->right);
    free(node);
}

void    ft_free_env_list(t_list_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env->next;
        free(env->content);
        free(env);
        free(env->path);
        free(env->env);
        free(env->variable_len);
        free(env->len);
        env = tmp;
    }
}

void    ft_free_token_list(t_list_token *token)
{
    t_token *tmp;

    while (token)
    {
        tmp = token->next;
        free(token->content->read);
        free(token->content->path);
        free(token->content->len);
        free(token->content->priority);
        free(token->content->type);
        free(token->content);
        free(token);
        token = tmp;
    }
}

void    ft_free_son(t_son *son)
{
    free(son->content);
    free(son->len);
    free(son->path);
    free(son->env);
    free(son->next);
    free(son->prev);
    free(son);
}

void    ft_free(t_list_env env,t_node node ,t_list_token token,t_son son)
{
    if(env != NULL) 
        ft_free_env_list(env);
    if(node !=NULL)
        t_free_node(node);
    if(token != NULL)
        ft_free_token_list(token);
    if(son != NULL)
        ft_free_son(son);
}