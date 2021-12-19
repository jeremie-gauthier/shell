use crate::lexer::{Lexer, Token, TokenType};
use crate::parser::error::ParserError;

const OPERATORS: &'static str = "<>&|";
pub fn is_operator(c: char) -> bool {
	OPERATORS.contains(c)
}

pub trait TerminalOperator {
	fn operator(&mut self) -> Result<Token, ParserError>;
}

impl TerminalOperator for Lexer {
	fn operator(&mut self) -> Result<Token, ParserError> {
		let current_char = self.input.chars().nth(self.current_pos).unwrap_or_default();
		let next_char = self
			.input
			.chars()
			.nth(self.current_pos + 1)
			.unwrap_or_default();
		println!("current_char {}", current_char);

		let tok_type = match current_char {
			'&' => ampersand_disambiguation(next_char), // ambiguite REDIRECTION | LOGICAL_AND
			'|' => pipe_disambiguation(next_char),      // ambiguite PIPE | LOGICAL_OR
			'<' | '>' => TokenType::Redirection,
			_ => return Err(ParserError::UnexpectedToken),
		};

		println!("tok_type: {:?}", tok_type);

		let tok_value = match tok_type {
			TokenType::Logical => format!("{}{}", current_char, next_char),
			TokenType::Pipe => String::from(current_char),
			TokenType::Redirection => {
				let chars: Vec<char> = self.input.chars().skip(self.current_pos).collect();
				redirection_op(chars)?
			}
			_ => return Err(ParserError::UnexpectedToken),
		};

		self.advance_by(tok_value.len());
		Ok(Token::new(Some(tok_value), tok_type))
	}
}

fn ampersand_disambiguation(next_char: char) -> TokenType {
	match next_char {
		'&' => TokenType::Logical,     // &&
		'>' => TokenType::Redirection, // &>
		_ => TokenType::Unknown,
	}
}

fn pipe_disambiguation(next_char: char) -> TokenType {
	match next_char {
		'|' => TokenType::Logical,
		_ => TokenType::Pipe,
	}
}

fn redirection_op(chars: std::vec::Vec<char>) -> Result<String, ParserError> {
	// at this point, current_char is known to exists
	let current_char = unsafe { chars.get_unchecked(0) };
	let next_char = chars.get(1).unwrap_or(&'\0');

	match current_char {
		'<' => {
			if *next_char == '<' {
				Ok(String::from("<<"))
			} else {
				Ok(String::from('<'))
			}
		}
		'>' => {
			if *next_char == '>' {
				Ok(String::from(">>"))
			} else {
				Ok(String::from('>'))
			}
		}
		'&' => {
			if *next_char == '>' {
				Ok(String::from("&>"))
			} else {
				Err(ParserError::UnexpectedToken)
			}
		}
		_ => Err(ParserError::UnexpectedToken),
	}
}
