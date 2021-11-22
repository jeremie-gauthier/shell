use crate::Token;
use crate::lexer::Lexer;

pub mod parser;
pub mod rules;

#[repr(C)]
pub struct BTNode {
    left: Option<Box<BTNode>>,
    right: Option<Box<BTNode>>,
    token: Token,
}

impl BTNode {
	pub fn new(token: Token, left: Option<BTNode>, right: Option<BTNode>) -> Self {
		BTNode {
			token,
			left: match left {
				Some(left_node) => Some(Box::new(left_node)),
				None => None
			},
			right: match right {
				Some(right_node) => Some(Box::new(right_node)),
				None => None
			}
		}
	}
}

pub struct Parser {
	lexer: Lexer,
	current_token: Token,
}

impl Parser {
	pub fn new(lexer: Lexer) -> Self {
		Parser { lexer, current_token: lexer.get_next_token() }
	}
}
