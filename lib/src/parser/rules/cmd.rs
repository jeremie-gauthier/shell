use crate::parser::rules::RuleArg;
use crate::parser::{BTNode, Parser, ParserError};

pub trait RuleCmd {
    fn cmd(&mut self) -> Result<BTNode, ParserError>;
}

impl RuleCmd for Parser {
    fn cmd(&mut self) -> Result<BTNode, ParserError> {
        let node = self.arg()?;
        Ok(node)
    }
}
