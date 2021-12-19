#[derive(Clone, Copy, Debug, PartialEq)]
pub enum TokenType {
	Word = 0,    // alnum
	Redirection, // < << > >> &>
	Pipe,        // |
	Separator,   // ;
	Logical,     // && ||
	Unknown,     // ???
	End,         // EOF
}

impl Default for TokenType {
	fn default() -> Self {
		TokenType::Unknown
	}
}

#[derive(Clone, Debug, Default, PartialEq)]
pub struct Token {
	pub value: String,
	pub token_type: TokenType,
}

impl Token {
	pub fn new(value: Option<String>, token_type: TokenType) -> Self {
		match value {
			Some(value) => Token { value, token_type },
			None => Token::default(),
		}
	}
}
