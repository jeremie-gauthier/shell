use crate::ast::Node;
use crate::lexer::TokenType;
use crate::parser::{Parser, ParserError};

pub trait RuleArg {
	fn arg(&mut self) -> Result<Node, ParserError>;
}

impl RuleArg for Parser {
	fn arg(&mut self) -> Result<Node, ParserError> {
		let token = self.current_token.clone();
		self.eat(TokenType::Word)?;
		Ok(Node::new(token, None, None))
	}
}
