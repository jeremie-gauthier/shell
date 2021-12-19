use crate::ast::Node;
use crate::lexer::TokenType;
use crate::parser::rules::RuleCmd;
use crate::parser::{Parser, ParserError};

const OPERATORS: [TokenType; 3] = [TokenType::Pipe, TokenType::Redirection, TokenType::Logical];

fn is_operator(tok_type: &TokenType) -> bool {
	OPERATORS.contains(tok_type)
}

pub trait RuleExpr {
	fn expr(&mut self) -> Result<Node, ParserError>;
}

impl RuleExpr for Parser {
	fn expr(&mut self) -> Result<Node, ParserError> {
		let mut node = self.cmd()?;

		while is_operator(&self.current_token.token_type) {
			let token = self.current_token.clone();
			node = match &token.token_type {
				TokenType::Pipe => {
					self.eat(TokenType::Pipe)?;
					Node::new(token, Some(node), Some(self.cmd()?))
				}
				TokenType::Redirection => {
					self.eat(TokenType::Redirection)?;
					Node::new(token, Some(node), Some(self.cmd()?))
				}
				TokenType::Logical => {
					self.eat(TokenType::Logical)?;
					Node::new(token, Some(node), Some(self.cmd()?))
				}
				_ => return Err(ParserError::UnexpectedToken),
			};
		}
		Ok(node)
	}
}
