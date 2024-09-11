#include <fcntl.h>
#include <sys/wait.h>
#include <memory.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

typedef enum e_type
{
    NONE,
    CMD,
    ARG,
    REDIR,
    PIPE,
    SEMICOLON,
    PARENTHESIS,
    BUILTIN,
    ENV,
    VARIABLE,
    EXPANSION,
    ASSIGNMENT,
    FILE_PATH,
    HEREDOC,
    ENDLINE,
    APPEND,
} t_type;

typedef struct s_token
{
    char *read;
    char **argument;
    t_type type;
    int priority;
    char *path;
    int len;
} t_token;

typedef struct s_node
{
    t_token *operation;
    struct s_node *left;
    struct s_node *right;
    int n_childs;
} t_node;

typedef struct s_list_env
{
    char *content;
    int len;
    size_t variable_len;
    struct s_list_env *next;
} t_list_env;

typedef struct s_list_token
{
    t_token *content;
    struct s_list_token *next;
    struct s_list_token *prev; // Add the prev member
} t_list_token;

t_node *create_ast_node(t_token *operation)
{
    t_node *node = (t_node *)malloc(sizeof(t_node));
    if (!node)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    node->operation = operation;
    node->left = NULL;
    node->right = NULL;
    node->n_childs = 0;
    printf("Created node: %s\n", operation->read); // Add printf statement
    return node;
}

// Function to find the highest-priority token in the token list
t_list_token *find_highest_priority_token(t_list_token *start, t_list_token *end)
{
    t_list_token *current = start;
    t_list_token *highest_priority_token = start;
    while (current != end->next)
    {
        if (current->content->priority < highest_priority_token->content->priority)
        {
            highest_priority_token = current;
        }
        current = current->next;
    }
    return highest_priority_token;
}

// Recursive function to build the AST
t_node *ast_creator(t_list_token *start, t_list_token *end)
{
    if (start == NULL || start == end->next)
        return NULL;
    printf("ast_creator called with start: %s, end: %s\n",
           start ? start->content->read : "NULL",
           end ? end->content->read : "NULL");

    // Find the token with the highest priority (pipes first, then redirections)
    t_list_token *highest_priority_token = find_highest_priority_token(start, end);
    // Create a node for the highest-priority token
    t_node *node = create_ast_node(highest_priority_token->content);
    // If the token is a pipe, its children are commands or other pipes
    if (highest_priority_token->content->type == PIPE)
    {
        if (highest_priority_token->prev != NULL)
            node->left = ast_creator(start, highest_priority_token->prev);
        if (highest_priority_token->next != NULL)
            node->right = ast_creator(highest_priority_token->next, end);
    }
    // If the token is a redirection, attach it to the appropriate command node
    else if (highest_priority_token->content->type == REDIR ||
             highest_priority_token->content->type == APPEND)
    {
        // Redirection affects the right side (file), so left is the command, right is the file
        if (highest_priority_token->prev != NULL)
            node->left = ast_creator(start, highest_priority_token->prev);
        if (highest_priority_token->next != NULL)
            node->right = ast_creator(highest_priority_token->next, end);
    }
    // If it's a command or argument, there may be more tokens to process in a sequential order
    else if (highest_priority_token->content->type == CMD || highest_priority_token->content->type == ARG)
    {
        if (highest_priority_token->prev != NULL)
            node->left = ast_creator(start, highest_priority_token->prev);
        if (highest_priority_token->next != NULL)
            node->right = ast_creator(highest_priority_token->next, end);
    }
    return node;
}

// Print the AST (for debugging purposes)
void print_ast(t_node *node, int level)
{
    if (node == NULL)
        return;
    print_ast(node->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("    ");
    if (node->operation->type == PIPE)
        printf("| (PIPE)\n");
    else if (node->operation->type == REDIR || node->operation->type == APPEND)
        printf("%s (REDIRECTION)\n", node->operation->read);
    else if (node->operation->type == CMD)
        printf("%s (COMMAND)\n", node->operation->read);
    else if (node->operation->type == ARG)
        printf("%s (ARGUMENT)\n", node->operation->read);
    print_ast(node->left, level + 1);
}

int main()
{
    // Example token list (simulating an input like ls -l | grep txt > out.txt)
    t_token tokens[] = {
        {"ls", NULL, CMD, 3, NULL, 2},
        {"-l", NULL, ARG, 3, NULL, 2},
        {"|", NULL, PIPE, 1, NULL, 1},
        {"grep", NULL, CMD, 3, NULL, 4},
        {"txt", NULL, ARG, 3, NULL, 3},
        {">", NULL, REDIR, 2, NULL, 1},
        {"out.txt", NULL, FILE_PATH, 3, NULL, 7},
    };

    t_list_token *head = NULL;
    t_list_token *prev = NULL;
    t_list_token *new = NULL;
    for (size_t i = 0; i < sizeof(tokens) / sizeof(t_token); i++) // Change int to size_t
    {
        new = (t_list_token *)malloc(sizeof(t_list_token));
        new->content = &tokens[i];
        new->next = NULL;
        new->prev = prev; // Set the prev pointer
        if (prev != NULL)
        {
            prev->next = new;
        }
        else
        {
            head = new; // Set head to the first element
        }
        prev = new;
    }

    t_list_token *end = head;
    while (end->next != NULL)
    {
        end = end->next;
    }

    // Create the AST
    t_node *root = ast_creator(head, end);

    // Print the AST (for debugging)
    printf("AST:\n");
    print_ast(root, 0);

    // Free the allocated memory
    t_list_token *current = head;
    while (current != NULL)
    {
        t_list_token *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}