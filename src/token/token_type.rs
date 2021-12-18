#[derive(Clone, Copy, Debug, PartialEq)]
pub enum TokenType {
	Whitespace = 0, // space
	Word,           // alnum
	Operator,       // generic operator type for lexer
	Redirection,    // < << > >> &>
	Pipe,           // |
	Separator,      // ;
	Logical,        // && ||
	Unknown,        // ???
	End,            // EOF
}

impl Default for TokenType {
	fn default() -> Self {
		TokenType::Unknown
	}
}
