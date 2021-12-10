# Shell grammar

Using the [Rust grammar](https://doc.rust-lang.org/reference/notation.html?highlight=grammar#grammar) to describe it.

## Terminals

```txt
WORD: 		string of alphanumeric chars
PIPE: 		|
SEPARATOR: 	;
LOGICAL_OR:	||
LOGICAL_AND:	&&
REDIRECTION: <<, <, >, >>, &> (get the name of each and create separate tokens)
```

## Rules

_arg_:		WORD
_cmd_:		_arg_<sup>+</sup>
_expr_:		_cmd_ ( _operator_<sup>+</sup> _cmd_<sup>?</sup> )<sup>*</sup>
_operator_: 	_redirection_ | PIPE | _logical_ | SEPARATOR
_redirection_:	< | << | > | >> | &>
_logical_: 	LOGICAL_OR | LOGICAL_AND