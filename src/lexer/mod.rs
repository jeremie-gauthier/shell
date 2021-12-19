mod terminals;
mod token;

use crate::parser::ParserError;
use terminals::{is_operator, TerminalOperator, TerminalWord};
pub use token::{Token, TokenType};

pub struct Lexer {
	input: String,
	current_pos: usize,
}

impl Lexer {
	pub fn new(input: String) -> Self {
		Lexer {
			input,
			current_pos: 0,
		}
	}

	fn advance(&mut self) {
		self.current_pos += 1
	}

	fn advance_by(&mut self, len: usize) {
		self.current_pos += len;
	}

	pub fn get_next_token(&mut self) -> Result<Token, ParserError> {
		while let Some(c) = self.input.chars().nth(self.current_pos) {
			match c {
				_ if c.is_ascii_whitespace() => self.advance(),
				_ if c.is_ascii_alphanumeric() => {
					return self.word();
				}
				_ if is_operator(c) => return self.operator(),
				_ => {
					return Err(ParserError::UnexpectedToken);
				}
			};
		}

		Ok(Token::new(None, TokenType::End))
	}
}
