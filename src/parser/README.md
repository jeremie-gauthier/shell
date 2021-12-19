# Syntax analysis

The parser uses the first components of the tokens produced by the [lexical analyzer](../lexer/README.md) to create an **abstract syntax tree** (AST) representation that depicts the grammatical structure of the token stream.

## Rules

_arg_:		WORD
_cmd_:		_arg_<sup>+</sup>
_expr_:		_cmd_ ( _operator_<sup>+</sup> _cmd_<sup>?</sup> )<sup>*</sup>
_operator_: 	_redirection_ | PIPE | _logical_ | SEPARATOR
_redirection_:	< | << | > | >> | &>
_logical_: 	LOGICAL_OR | LOGICAL_AND