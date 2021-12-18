use crate::lexer::Lexer;
use crate::parser::error::ParserError;
use crate::parser::Parser;
use crate::token::Token;

#[derive(Debug, PartialEq)]
pub struct Node {
	token: Token,
	pub left: Option<Box<Node>>,
	pub right: Option<Box<Node>>,
}

impl Node {
	pub fn new(token: Token, left: Option<Node>, right: Option<Node>) -> Self {
		Node {
			token,
			left: match left {
				Some(left_node) => Some(Box::new(left_node)),
				None => None,
			},
			right: match right {
				Some(right_node) => Some(Box::new(right_node)),
				None => None,
			},
		}
	}
}

impl TryFrom<String> for Node {
	type Error = ParserError;

	fn try_from(input: String) -> Result<Node, ParserError> {
		let lexer = Lexer::new(input);
		let parser = Parser::new(lexer);
		parser.parse_input()
	}
}

#[cfg(test)]
mod tests {
	use super::*;
	use crate::token::TokenType;

	#[test]
	fn test_ast_from_string() {
		let tested = Node::try_from(String::from("Hello world"));

		let hello_token = Token::new(Some(String::from("Hello")), TokenType::Word);
		let world_token = Token::new(Some(String::from("world")), TokenType::Word);
		let expected_ast = Node::new(hello_token, None, Some(Node::new(world_token, None, None)));

		assert_eq!(tested, Ok(expected_ast));
	}
}
