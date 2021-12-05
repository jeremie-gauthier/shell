use crate::lexer::Lexer;
use crate::parser::error::ParserError;
use crate::{Token, TokenType};

pub trait TerminalWord {
    fn word(&mut self) -> Result<Token, ParserError>;
}

impl TerminalWord for Lexer {
    fn word(&mut self) -> Result<Token, ParserError> {
        let token_value: String = self
            .input
            .chars()
            .skip(self.current_pos)
            .take_while(char::is_ascii_graphic)
            .collect();
        self.advance_by(token_value.len());
        Ok(Token::new(Some(token_value), TokenType::Word))
    }
}
