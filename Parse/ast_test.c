# include <fcntl.h>
# include <sys/wait.h>
# include <memory.h>
# include <stdint.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

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
}	t_type;

typedef struct s_token
{
	char		*read;
	char		**argument;
	t_type		type;
	int			priority;
	char		*path;
	int			len;
}	t_token;

typedef struct s_node
{
	t_token				*operation;
	struct s_node		*left;
	struct s_node		*right;
	int					n_childs;
}	t_node;

typedef struct s_list_env
{
	char				*content;
	int					len;
	size_t				variable_len;
	struct s_list_env	*next;
}	t_list_env;

typedef struct s_list_token
{
	t_token				*content;
	struct s_list_token	*next;
}	t_list_token;

t_node *create_ast_node(t_token *operation) {
    t_node *node = (t_node *)malloc(sizeof(t_node));
    if (!node) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    node->operation = operation;
    node->left = NULL;
    node->right = NULL;
    node->n_childs = 0;
    return node;
}
// Function to find the index of the highest-priority token in the token list
int find_highest_priority_token(t_token *tokens, int start, int end) {
    int i;
    int highest_priority_index = start;
    for (i = start; i <= end; i++) {
        if (tokens[i].priority < tokens[highest_priority_index].priority) {
            highest_priority_index = i;
        }
    }
    return highest_priority_index;
}
// Recursive function to build the AST
t_node *ast_creator(t_token *tokens, int start, int end) {
    if (start > end) {
        return NULL;
    }
    // Find the token with the highest priority (pipes first, then redirections)
    int highest_priority_index = find_highest_priority_token(tokens, start, end);
    // Create a node for the highest-priority token
    t_node *node = create_ast_node(&tokens[highest_priority_index]);
    // If the token is a pipe, its children are commands or other pipes
    if (tokens[highest_priority_index].type == PIPE) {
        node->left = ast_creator(tokens, start, highest_priority_index - 1);
        node->right = ast_creator(tokens, highest_priority_index + 1, end);
    }
    // If the token is a redirection, attach it to the appropriate command node
    else if (tokens[highest_priority_index].type == REDIR ||
             tokens[highest_priority_index].type == APPEND) {
        // Redirection affects the right side (file), so left is the command, right is the file
        node->left = ast_creator(tokens, start, highest_priority_index - 1);
        node->right = ast_creator(tokens, highest_priority_index + 1, end);
    }
    // If it's a command or argument, there may be more tokens to process in a sequential order
    else if (tokens[highest_priority_index].type == CMD || tokens[highest_priority_index].type == ARG) {
        node->left = ast_creator(tokens, start, highest_priority_index - 1);
        node->right = ast_creator(tokens, highest_priority_index + 1, end);
    }
    return node;
}
// Print the AST (for debugging purposes)
void print_ast(t_node *node, int level) {
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
int main() {
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
    int num_tokens = sizeof(tokens) / sizeof(t_token);
    // Create the AST
    t_node *root = ast_creator(tokens, 0, num_tokens - 1);
    // Print the AST (for debugging)
    printf("AST:\n");
    print_ast(root, 0);
    return 0;
}