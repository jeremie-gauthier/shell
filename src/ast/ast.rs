use crate::ast::Node;
use crate::lexer::Lexer;
use crate::parser::{Parser, ParserError};

pub type AST = Node;

impl TryFrom<String> for AST {
	type Error = ParserError;

	fn try_from(input: String) -> Result<AST, ParserError> {
		let lexer = Lexer::new(input);
		let parser = Parser::new(lexer);
		parser.parse_input()
	}
}

#[cfg(test)]
mod tests {
	use super::*;
	use crate::lexer::{Token, TokenType};

	#[test]
	fn test_ast_from_string() {
		let tested = AST::try_from(String::from("Hello world"));

		let hello_token = Token::new(Some(String::from("Hello")), TokenType::Word);
		let world_token = Token::new(Some(String::from("world")), TokenType::Word);
		let expected_ast = Node::new(hello_token, None, Some(Node::new(world_token, None, None)));

		assert_eq!(tested, Ok(expected_ast));
	}
}
