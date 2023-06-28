# Structure d'environnement
```c
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;
```

> `PWD=/Users/evan/dev/42cursus/minishell`

Ce qui se trouve avant le signe "=" est la clé (key),
ce qui se trouve après est la valeur (value). C'est une liste doublement chaînée qui va dans les deux sens (next et prev).

# Énumération des types de redirection
#### Cette énumération répertorie tous les types de redirection possibles.
```c
typedef enum e_redirtype
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_PIPE,
	REDIR_NONE
}					t_redirtype;
```


```
REDIR_IN = cat [<] in.txt
REDIR_OUT = ls [>] out.txt
REDIR_APPEND = ls [>>] out.txt
REDIR_HEREDOC = cat [<<] EOF
REDIR_PIPE = cat hello.txt [|] wc -l
REDIR_NONE = cat hello.txt (aucune redirection)
```

# Structure de redirection
#### Cette structure fait partie de chaque structure de commande et permet de fournir des informations sur les redirections d'une commande.
```c
typedef struct s_redir
{
	t_redirtype		type;
	char			*file;
	struct s_redir	*next;
}					t_redir;
```


```
type -> Type de redirection (voir l'énumération des types de redirection)
file -> Si la redirection est REDIR_IN, REDIR_OUT ou REDIR_APPEND, c'est le fichier, sinon NULL
```

# Structure de commande
```c
typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;
```


> **NOTE:** Une commande peut avoir plusieurs redirections (ls | wc -l > out.txt >> out.txt). Dans ce cas, il faut créer une liste chaînée de redirections.

Exemple de commande: `ls | wc -l > out.txt`

```c
t_cmd	*pipeline;
t_redir	*redir;

pipeline = malloc(sizeof(t_cmd) * 2);
redir = malloc(sizeof(t_redir));

redir->type = REDIR_PIPE;
redir->file = NULL;
redir->next = NULL;
pipeline[0].cmd = "ls";
pipeline[0].args = NULL;
pipeline[0].redir = redir;
pipeline[0].next = &pipeline[1];

redir = malloc(sizeof(t_redir));
redir->type = REDIR_OUT;
redir->file = "out.txt";
redir->next = NULL;
pipeline[1].cmd = "wc";
pipeline[1].args = malloc(sizeof(char *) * 2);
pipeline[1].args[0] = "-l";
pipeline[1].args[1] = NULL;
pipeline[1].redir = redir;
pipeline[1].next = NULL;
```

# Structure globale 🚧
```c
typedef struct s_minishell
{
	t_env			*env;
	int				last_exit_status;
}					t_minishell;
```

> **NOTE:** La structure globale est une structure qui contient toutes les informations nécessaires pour le shell. C'est une variable globale qui est accessible partout dans le programme.

```
env -> Liste chaînée des variables d'environnement
last_exit_status -> Dernier code de sortie de la dernière commande du dernier pipeline
```