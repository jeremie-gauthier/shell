use crate::ast::Node;
use crate::lexer::TokenType;
use crate::parser::rules::RuleArg;
use crate::parser::{Parser, ParserError};

pub trait RuleCmd {
	fn cmd(&mut self) -> Result<Node, ParserError>;
}

impl RuleCmd for Parser {
	fn cmd(&mut self) -> Result<Node, ParserError> {
		let mut node = self.arg()?;

		if self.current_token.token_type == TokenType::Word {
			let next_arg = self.cmd()?;
			node.right = Some(Box::new(next_arg));
		}
		Ok(node)
	}
}
