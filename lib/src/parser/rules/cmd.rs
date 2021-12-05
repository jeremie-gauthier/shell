use crate::parser::rules::RuleArg;
use crate::parser::{BTNode, Parser, ParserError};
use crate::TokenType;

pub trait RuleCmd {
    fn cmd(&mut self) -> Result<BTNode, ParserError>;
}

impl RuleCmd for Parser {
    fn cmd(&mut self) -> Result<BTNode, ParserError> {
        let mut node = self.arg()?;

        if self.current_token.e_token_type == TokenType::Word {
            let next_arg = self.cmd()?;
            node.right = Some(Box::new(next_arg));
            Ok(node)
        } else {
            Ok(node)
        }
    }
}
