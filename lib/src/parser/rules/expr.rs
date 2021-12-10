use crate::parser::rules::RuleCmd;
use crate::parser::{BTNode, Parser, ParserError};
use crate::TokenType;

const OPERATORS: [TokenType; 3] = [TokenType::Pipe, TokenType::Redirection, TokenType::Logical];

fn is_operator(tok_type: &TokenType) -> bool {
    OPERATORS.contains(tok_type)
}

pub trait RuleExpr {
    fn expr(&mut self) -> Result<BTNode, ParserError>;
}

impl RuleExpr for Parser {
    fn expr(&mut self) -> Result<BTNode, ParserError> {
        let mut node = self.cmd()?;

        while is_operator(&self.current_token.e_token_type) {
            let token = self.current_token.clone();
            node = match &token.e_token_type {
                TokenType::Pipe => {
                    self.eat(TokenType::Pipe)?;
                    BTNode::new(token, Some(node), Some(self.cmd()?))
                }
                TokenType::Redirection => {
                    self.eat(TokenType::Redirection)?;
                    BTNode::new(token, Some(node), Some(self.cmd()?))
                }
                TokenType::Logical => {
                    self.eat(TokenType::Logical)?;
                    BTNode::new(token, Some(node), Some(self.cmd()?))
                }
                _ => return Err(ParserError::UnexpectedToken),
            };
        }
        Ok(node)
    }
}
