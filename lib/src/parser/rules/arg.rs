use crate::parser::{BTNode, Parser, ParserError};
use crate::TokenType;

pub trait RuleArg {
    fn arg(&mut self) -> Result<BTNode, ParserError>;
}

impl RuleArg for Parser {
    fn arg(&mut self) -> Result<BTNode, ParserError> {
        let token = self.current_token.clone();
        self.eat(TokenType::Word)?;
        Ok(BTNode::new(token, None, None))
    }
}
