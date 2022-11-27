#include "ast.h"
#include "parser.h"
#include "shell.h"

#include <stdio.h>

// pipeline: cmd "|" cmd ("|" cmd)*
t_ast *parse_pipeline(const t_shell *const shell, t_parser *const parser)
{
	t_ast *node = parse_cmd(shell, parser);

	while (IS_VALID_TOKEN(parser->current_token.type, Pipe))
	{
		node = ast_create_node(parser->current_token, node, NULL);
		eat(shell, parser, Pipe);
		node->right = parse_cmd(shell, parser);
	}

	return node;
}

// /!\ Cmds in pipes are run asynchronously by nature. (Wait the N commands after spawn them)
// also, this save time & memory

// il faut return une node
// comment gerer le pipeline ?
// les docs s'accordent sur le fait de creer une rule special pour cela
// ca veut donc dire une node dediee aux pipelines
// ca veut donc dire que toutes les commandes de la pipeline sont contenues dans une seule node
// cela fait sens car plus tard, pendant l'ajout des operateurs binaires,
// 		le controle s'effectuera sur le retour de la pipeline toute entiere
// COMMENT STRUCTURER LA DATA D'UNE PIPELINE ?
// peut-etre creer une struct pipeline { size_t size; t_token *cmds; }
//  -> par contre, avant d'arriver a ce resultat, il va falloir refactor la rule cmd
// 		afin qu'elle retourne une commande ainsi que ses arguments sous la forme d'un seul token
// 		(c'est de cette facon que la grammaire Bash est ecrite)

// Il faudrait refactor toute la grammaire du projet afin de copier celle de Bash
// 		pour simplifier l'ajout de fonctionnalites futures