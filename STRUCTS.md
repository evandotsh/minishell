## Structure `t_token`

Structure représentant un jeton (token) dans l'analyseur syntaxique (parser).

### Propriétés

- `token`: Une chaîne de caractères représentant le jeton.
- `next`: Un pointeur vers le prochain jeton.

---

## Énumération `t_node_type`

Cette énumération répertorie les types de nodes de l'arbre d'analyse syntaxique (AST) possibles.

### Valeurs

- `ND_CMD`: Node représentant une commande.
- `ND_ARG`: Node représentant un argument de commande.
- `ND_PIPE`: Node représentant un opérateur de pipe.

---

## Structure `t_ast_node`

Structure représentant un node de l'arbre d'analyse syntaxique (AST).

### Propriétés

- `type`: Le type de node (`t_node_type`) indiquant le rôle du node.
- `cmd_name`: Une chaîne de caractères représentant le nom de la commande, applicable uniquement lorsque le node est de type `ND_CMD`.
- `cmd_args`: Un tableau de pointeurs vers des nodes représentant les arguments de la commande, applicable uniquement lorsque le node est de type `ND_CMD`.
- `cmd_arg_count`: Le nombre d'arguments de la commande, applicable uniquement lorsque le node est de type `ND_CMD`.
- `cmd_stdin_source`: Un entier indiquant la source d'entrée standard pour la commande, si applicable. (0 représente l'entrée standard par défaut)
- `cmd_stdin_file`: Une chaîne de caractères représentant le fichier provenant duquel la commande reçoit l'entrée standard, si applicable.
- `cmd_stdout_dest`: Un entier indiquant la destination de sortie standard pour la commande, si applicable. (0 représente la sortie standard par défaut)
- `cmd_stdout_file`: Une chaîne de caractères représentant le fichier dans lequel la commande redirige la sortie standard, si applicable.
- `cmd_pipe_read`: Un entier représentant le descripteur de fichier de lecture du pipe pour la commande, si applicable.
- `cmd_pipe_write`: Un entier représentant le descripteur de fichier d'écriture du pipe pour la commande, si applicable.
- `arg_value`: Une chaîne de caractères représentant la valeur de l'argument, applicable uniquement lorsque le node est de type `ND_ARG`.
- `pipe_lhs`: Un pointeur vers le node de gauche dans une opération de pipe, applicable uniquement lorsque le node est de type `ND_PIPE`.
- `pipe_rhs`: Un pointeur vers le node de droite dans une opération de pipe, applicable uniquement lorsque le node est de type `ND_PIPE`.

### Représentation en arbre explicite:
```
                    ND_PIPE
               /               \
          ND_CMD                 ND_CMD
        /       \               /       \
   ND_ARG    ND_ARG        ND_ARG    ND_ARG
     |         |             |         |
    "ls"      "-l"         "wc"      "-c"
                                 |
                                ND_ARG
                                  |
                               "out.txt"
```

### Représentation en arbre concis:
```
ND_PIPE
|
|- ND_CMD (ls)
|  |- ND_ARG (-l)
|
|- ND_CMD (wc)
   |- ND_ARG (-c)
   |
   |- ND_ARG (out.txt)
```

---

## Structure `t_env`

Structure représentant une variable d'environnement.

### Propriétés

- `key`: Une chaîne de caractères représentant la clé de la variable d'environnement.
- `value`: Une chaîne de caractères représentant la valeur de la variable d'environnement.
- `next`: Un pointeur vers la prochaine variable d'environnement.
- `prev`: Un pointeur vers la variable d'environnement précédente.

---