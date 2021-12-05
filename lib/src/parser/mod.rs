pub mod error;
pub mod parser;
pub mod rules;

use crate::lexer::Lexer;
use crate::parser::error::ParserError;
use crate::parser::rules::RuleExpr;
use crate::{BTNode, Token, TokenType};

pub struct Parser {
    lexer: Lexer,
    current_token: Token,
}

impl Parser {
    pub fn new(lexer: Lexer) -> Result<Self, ParserError> {
        Ok(Parser {
            lexer,
            current_token: Token::default(),
        })
    }

    fn eat(&mut self, token_type: TokenType) -> Result<(), ParserError> {
        if self.current_token.e_token_type == token_type {
            self.current_token = self.lexer.get_next_token()?;
            Ok(())
        } else {
            Err(ParserError::UnexpectedToken)
        }
    }

    pub fn parse_input(mut self) -> Result<BTNode, ParserError> {
        self.current_token = self.lexer.get_next_token()?;
        let token = self.current_token.clone();
        println!("current_token: {:?}", token);
        self.expr()
    }
}
