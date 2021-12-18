use crate::TokenType;

#[derive(Clone, Debug, Default, PartialEq)]
pub struct Token {
	pub value: String,
	pub token_type: TokenType,
}

impl Token {
	pub fn new(value: Option<String>, token_type: TokenType) -> Self {
		match value {
			Some(value) => Token { value, token_type },
			None => Token {
				value: String::default(),
				token_type,
			},
		}
	}
}
