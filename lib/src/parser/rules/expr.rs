use crate::parser::rules::RuleCmd;
use crate::parser::{BTNode, Parser, ParserError};

pub trait RuleExpr {
    fn expr(&mut self) -> Result<BTNode, ParserError>;
}

impl RuleExpr for Parser {
    fn expr(&mut self) -> Result<BTNode, ParserError> {
        let node = self.cmd()?;
        Ok(node)
    }
}
