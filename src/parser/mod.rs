pub mod error;
pub mod parser;
pub mod rules;

use crate::ast::Node;
use crate::lexer::Lexer;
use crate::parser::error::ParserError;
use crate::parser::rules::RuleExpr;
use crate::{Token, TokenType};

pub struct Parser {
	lexer: Lexer,
	current_token: Token,
}

impl Parser {
	pub fn new(lexer: Lexer) -> Self {
		Parser {
			lexer,
			current_token: Token::default(),
		}
	}

	fn eat(&mut self, token_type: TokenType) -> Result<(), ParserError> {
		if self.current_token.token_type == token_type {
			self.current_token = self.lexer.get_next_token()?;
			Ok(())
		} else {
			Err(ParserError::UnexpectedToken)
		}
	}

	pub fn parse_input(mut self) -> Result<Node, ParserError> {
		self.current_token = self.lexer.get_next_token()?;
		self.expr()
	}
}
