# 💻 minishell

![Norminette Badge](https://github.com/evandotsh/minishell/actions/workflows/norminette.yml/badge.svg)

<a href="https://github.com/evandotsh/minishell/blob/main/PARCING.md">Parsing</a>
# Glossaire

## Pipeline
Un pipeline est une suite de commandes séparées par des redirections. Par exemple, `ls | wc -l > out.txt` est un pipeline.
Étant donné que nous n'avons pas à gérer les `&&` ou `;`, si la
ligne de commande contient plus d'une commande, il s'agit forcément d'un pipeline.

## Redirection
Une redirection est un symbole qui permet de rediriger la sortie standard d'une commande vers un fichier ou vers l'entrée standard d'une autre commande. Il existe 5 types de redirections: `>`, `>>`, `<`, `<<` et `|`.

## Token
Un token est une chaîne de caractères qui représente un mot. Par exemple, `ls | wc -l > out.txt` est composé des tokens `ls`, `|`, `wc`, `-l`, `>`, `out.txt`.
