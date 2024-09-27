#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de enumeración de tipos
typedef enum e_type
{
    NONE,
    CMD,
    ARG,
    REDIR_R,
    REDIR_L,
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

// Definición de estructuras
typedef struct s_token
{
    char *read;   // Texto del token
    t_type type;  // Tipo de token
    int priority; // Prioridad del token
    char *path;   // Ruta (si aplica)
    int len;      // Longitud del token
} t_token;

typedef struct s_node
{
    t_token *operation;      // Información del nodo
    struct s_node *left;     // Puntero al hijo izquierdo
    struct s_node *right;    // Puntero al hijo derecho
    int n_childs;            // Número de hijos
} t_node;

typedef struct s_list_token
{
    t_token *content;             // Puntero al token
    struct s_list_token *next;    // Puntero al siguiente nodo
    struct s_list_token *prev;    // Puntero al nodo anterior
} t_list_token;

// Definiciones de funciones auxiliares
int ft_strcmp(const char *s1, const char *s2)
{
    return strcmp(s1, s2);
}

void ft_exit(const char *message, int exit_code)
{
    printf("Error: %s\n", message);
    exit(exit_code);
}

// Función para crear un nuevo token
t_token *create_token(char *read, t_type type, int priority)
{
    t_token *token = (t_token *)malloc(sizeof(t_token));
    if (!token)
    {
        ft_exit("Memory allocation failed for token", 1);
    }
    token->read = read;
    token->type = type;
    token->priority = priority;
    token->path = NULL;
    token->len = strlen(read);
    return token;
}

// Función para crear un nuevo nodo de la lista de tokens
t_list_token *create_list_token(t_token *token)
{
    t_list_token *list_token = (t_list_token *)malloc(sizeof(t_list_token));
    if (!list_token)
    {
        ft_exit("Memory allocation failed for list token", 1);
    }
    list_token->content = token;
    list_token->next = NULL;
    list_token->prev = NULL;
    return list_token;
}

// Función para agregar un nodo a la lista de tokens
void add_token_to_list(t_list_token **list, t_list_token *new_token)
{
    if (!(*list))
    {
        *list = new_token;
    }
    else
    {
        t_list_token *temp = *list;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_token;
        new_token->prev = temp;
    }
}

// This function will determine the type of token_list
void token_list_typer (t_list_token *token_list) {    
    t_list_token *head = token_list;
    int i = 0;
    printf("Entering token_list_typer\n");
    while(token_list){
        printf("i: %d\n", i++);    
        if (ft_strcmp(token_list->content->read, "|") == 0) {
            token_list->content->type = PIPE;
            token_list->content->priority = 1;
        } else if (ft_strcmp(token_list->content->read, ">") == 0) {
            token_list->content->type = REDIR_R;
            token_list->content->priority = 3;
        } else if (ft_strcmp(token_list->content->read, "<") == 0) {
            token_list->content->type = REDIR_L;
            token_list->content->priority = 3;
        } else if (ft_strcmp(token_list->content->read, ">>") == 0) {
            token_list->content->type = APPEND;
            token_list->content->priority = 4;
        } else if (ft_strcmp(token_list->content->read, "<<") == 0) {
            token_list->content->type = HEREDOC;
            token_list->content->priority = 4;
        } else if (ft_strcmp(token_list->content->read, "\n") == 0) {
            token_list->content->type = ENDLINE;
            token_list->content->priority = 2;
        } else 
        {
            token_list->content->type = CMD;
            token_list->content->priority = 2;
        }
        if (token_list)
            token_list = token_list->next;
    }
    printf("Exiting token_list_typer\n");
    token_list = head;
}

// Function to create a new AST node
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
    else if (highest_priority_token->content->type == REDIR_L ||
                highest_priority_token->content->type == REDIR_R ||
                    highest_priority_token->content->type == APPEND)
    {
        // Redirection affects the right side (file), so left is the command, right is the file
        if (highest_priority_token->prev != NULL)
        {
            node->left = ast_creator(start, highest_priority_token->prev);
            node->left->right = node; // Attach the redirection to the command
        }
        if (highest_priority_token->next != NULL)
            node->right = create_ast_node(highest_priority_token->next->content);
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
// Función de impresión del AST
void print_ast_helper(t_node *node, int depth, char *side)
{
    if (node == NULL)
        return;
    if (node->operation->type == CMD || node->operation->type == ARG)
    {
        printf("%*s%s IDENTIFIER: %s\n", depth * 2, "", side, node->operation->read);
        print_ast_helper(node->left, depth + 2, "left:  ");
        print_ast_helper(node->right, depth + 2, "right: ");
    }
    else if (node->operation->type == REDIR_R || node->operation->type == REDIR_L)
    {
        printf("%*s%s REDIRECTION: %s\n", depth * 2, "", side, node->operation->read);
        print_ast_helper(node->left, depth + 2, "left:  ");
        print_ast_helper(node->right, depth + 2, "right: ");
    }
    else if (node->operation->type == PIPE)
    {
        printf("%*s%s PIPE: %s\n", depth * 2, "", side, node->operation->read);
        print_ast_helper(node->left, depth + 2, "left:  ");
        print_ast_helper(node->right, depth + 2, "right: ");
    }
    else
    {
        printf("%*s%s UNKNOWN: %s\n", depth * 2, "", side, node->operation->read);
        print_ast_helper(node->left, depth + 2, "left:  ");
        print_ast_helper(node->right, depth + 2, "right: ");
    }
}

void print_ast(t_node *root)
{
    printf("AST STRUCTURE:\n");
    print_ast_helper(root, 0, "root: ");
}

// Función principal para probar
int main()
{
    t_list_token *token_list = NULL;

    // Crear tokens con el tipo y prioridad correctos
    t_token *token0 = create_token("pwd", CMD, 3);
    t_token *token01 = create_token("|", PIPE, 1);
    t_token *token1 = create_token("echo", CMD, 3);
    t_token *token2 = create_token("hola", ARG, 3);
    t_token *token3 = create_token(">", REDIR_R, 2);
    t_token *token4 = create_token("salida", FILE_PATH, 3);

    // Agregar tokens a la lista
    add_token_to_list(&token_list, create_list_token(token0));
    add_token_to_list(&token_list, create_list_token(token01));
    add_token_to_list(&token_list, create_list_token(token1));
    add_token_to_list(&token_list, create_list_token(token2));
    add_token_to_list(&token_list, create_list_token(token3));
    add_token_to_list(&token_list, create_list_token(token4));

    // Tipar la lista de tokens
    token_list_typer(token_list);

    // Crear el AST desde la lista de tokens
    t_node *ast = ast_creator(token_list, NULL);

    // Imprimir el AST
    print_ast(ast);

    // Liberar memoria (opcional)
    // Aquí puedes agregar código para liberar todos los nodos y tokens creados.

    return 0;
}
