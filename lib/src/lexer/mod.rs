use crate::{Token, TokenType};
use std::iter::Peekable;
use std::str::Chars;

pub mod rules;

pub struct Lexer<'a> {
    input: Peekable<Chars<'a>>,
}

impl<'a> Lexer<'a> {
	pub fn new(input: String) -> Self {
		Lexer {
			input: input.chars().peekable(),
		}
	}

	pub fn advance(&mut self) {
		self.input.next();
	}

	pub fn get_next_token(self) -> Token {
		while self.input.peek().is_some() {

			self.advance();
		}

		Token::new(None, TokenType::End)
	}
}
