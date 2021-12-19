# Lexical analysis

The **lexical analyzer** (lexer) reads the stream of characters making up the source program and groups the characters into meaningful sequences called **lexemes**.
For each lexeme, the lexical analyzer produces as output a **token** of the form below that it passes on to the subsequent phase, [syntax analysis](../parser/README.md).

```rust
pub struct Token {
    pub value: String,
    pub token_type: TokenType,
}
```

## Lexemes

Using the [Rust grammar](https://doc.rust-lang.org/reference/notation.html?highlight=grammar#grammar) to describe them:

```txt
WORD:          string of alphanumeric chars
PIPE:          |
SEPARATOR:     ;
LOGICAL_OR:    ||
LOGICAL_AND:   &&
REDIRECTION:   <<, <, >, >>, &> (get the name of each and create separate tokens)
```
