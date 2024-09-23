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

// Función para asignar tipos y prioridades a los tokens
void token_list_typer(t_list_token *token_list)
{
    t_list_token *head = token_list;

    while (token_list)
    {
        if (ft_strcmp(token_list->content->read, "|") == 0)
        {
            token_list->content->type = PIPE;
            token_list->content->priority = 1;
        }
        else if (ft_strcmp(token_list->content->read, ">") == 0)
        {
            token_list->content->type = REDIR_R;
            token_list->content->priority = 2;
        }
        else if (ft_strcmp(token_list->content->read, "<") == 0)
        {
            token_list->content->type = REDIR_L;
            token_list->content->priority = 2;
        }
        else if (ft_strcmp(token_list->content->read, ">>") == 0)
        {
            token_list->content->type = APPEND;
            token_list->content->priority = 4;
        }
        else if (ft_strcmp(token_list->content->read, "<<") == 0)
        {
            token_list->content->type = HEREDOC;
            token_list->content->priority = 4;
        }
        else if (ft_strcmp(token_list->content->read, "\n") == 0)
        {
            token_list->content->type = ENDLINE;
            token_list->content->priority = 3;
        }
        else
        {
            token_list->content->type = CMD;
            token_list->content->priority = 3;
        }
        token_list = token_list->next;
    }
    token_list = head;
}

// Función para crear un nuevo nodo AST
t_node *create_ast_node(t_token *operation)
{
    t_node *node = (t_node *)malloc(sizeof(t_node));
    if (!node)
    {
        ft_exit("Memory allocation failed for AST node", 1);
    }
    node->operation = operation;
    node->left = NULL;
    node->right = NULL;
    node->n_childs = 0;
    return node;
}

// Función para insertar nodos en el AST según las reglas descritas
t_node *insert_redirection_node(t_node *root, t_token *token, t_list_token *prev, t_list_token *next)
{
    t_node *new_node = create_ast_node(token);
    
    if (token->type == REDIR_R || token->type == APPEND) {
        // Asignar el comando anterior como hijo izquierdo y el archivo como hijo derecho
        new_node->left = create_ast_node(prev->content);
        new_node->right = create_ast_node(next->content);
    } else if (token->type == REDIR_L || token->type == HEREDOC) {
        // Asignar el archivo como hijo izquierdo y el comando como hijo derecho
        new_node->left = create_ast_node(next->content);
        new_node->right = create_ast_node(prev->content);
    }
    new_node->n_childs = 2;

    return new_node;
}

// Función para crear el AST desde una lista de tokens
t_node *ast_creator(t_list_token *start, t_list_token *end) {
    t_list_token *current = start;
    t_node *root = NULL;
    t_node *last_pipe_node = NULL;
    t_node *new_node = NULL;

    while (current && current != end) {
        if (current->content->type == PIPE) {
            // Crear nodo de pipe
            new_node = create_ast_node(current->content);
            // Asignar subárbol izquierdo al último root construido
            if (root) {
                new_node->left = root;
            }
            root = new_node;
            last_pipe_node = root; // Recordar el nodo de pipe más reciente
        } else if (current->content->type == REDIR_R || current->content->type == REDIR_L || current->content->type == APPEND || current->content->type == HEREDOC) {
            // Si es una redirección, asociarla con el nodo anterior y siguiente
            if (current->prev && current->next) {
                new_node = insert_redirection_node(NULL, current->content, current->prev, current->next);
                if (last_pipe_node) {
                    // Colocar la redirección a la derecha del último pipe
                    last_pipe_node->right = new_node;
                } else {
                    // Si no hay pipe, es la raíz
                    root = new_node;
                }
            }
            // Saltar nodos usados para la redirección
            current = current->next->next; 
            continue;
        } else {
            // Nodo de comando o argumento
            new_node = create_ast_node(current->content);
            if (!root) {
                root = new_node;
            } else if (last_pipe_node) {
                // Si hay un pipe activo, asignar el nuevo nodo a la derecha del último pipe
                last_pipe_node->right = new_node;
                last_pipe_node = NULL; // Resetear el pipe después de usarlo
            } else {
                // Generalmente los comandos irán al subárbol izquierdo del root actual
                new_node->left = root;
                root = new_node;
            }
        }
        current = current->next;
    }

    return root;
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
