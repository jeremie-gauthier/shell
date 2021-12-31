use crate::ast::Node;
use crate::lexer::Lexer;
use crate::lexer::Token;
use crate::parser::{Parser, ParserError};

#[derive(Debug, PartialEq)]
pub struct AST {
    iterator: Vec<Token>,
    pub root: Node,
}

impl AST {
    pub fn new(root: Node) -> Self {
        let mut ast = AST {
            iterator: vec![],
            root: root.clone(),
        };
        ast.infix_course(Box::new(root));
        ast
    }

    fn infix_course(&mut self, node: Box<Node>) {
        if let Some(right) = node.right {
            self.infix_course(right);
        }
        self.iterator.push(node.token);
        if let Some(left) = node.left {
            self.infix_course(left);
        }
    }
}

impl Iterator for AST {
    type Item = Token;
    fn next(&mut self) -> Option<Self::Item> {
        self.iterator.pop()
    }
}

impl TryFrom<String> for AST {
    type Error = ParserError;

    fn try_from(input: String) -> Result<AST, ParserError> {
        let lexer = Lexer::new(input);
        let parser = Parser::new(lexer);
        let node = parser.parse_input()?;
        Ok(AST::new(node))
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::lexer::TokenType;

    #[test]
    fn test_ast_from_string() {
        let tested = AST::try_from(String::from("touch marvel && echo IronMan >> marvel"));

        let touch_token = Token::new(Some(String::from("touch")), TokenType::Word);
        let marvel_token = Token::new(Some(String::from("marvel")), TokenType::Word);
        let logical_and_token = Token::new(Some(String::from("&&")), TokenType::LogicalAnd);
        let echo_token = Token::new(Some(String::from("echo")), TokenType::Word);
        let iron_man_token = Token::new(Some(String::from("IronMan")), TokenType::Word);
        let redirection_token = Token::new(Some(String::from(">>")), TokenType::Redirection);
        let marvel_token2 = Token::new(Some(String::from("marvel")), TokenType::Word);

        let level_1l_2l = Node::new(touch_token, None, Some(Node::new(marvel_token, None, None)));
        let level_1l_2r = Node::new(
            echo_token,
            None,
            Some(Node::new(iron_man_token, None, None)),
        );

        let level_1l = Node::new(logical_and_token, Some(level_1l_2l), Some(level_1l_2r));
        let level_1r = Node::new(marvel_token2, None, None);

        let root = Node::new(redirection_token, Some(level_1l), Some(level_1r));
        assert_eq!(tested.unwrap().root, root);
    }

    #[test]
    fn test_ast_into_iter() {
        let ast = AST::try_from(String::from("touch marvel && echo IronMan >> marvel")).unwrap();

        let touch_token = Token::new(Some(String::from("touch")), TokenType::Word);
        let marvel_token = Token::new(Some(String::from("marvel")), TokenType::Word);
        let logical_and_token = Token::new(Some(String::from("&&")), TokenType::LogicalAnd);
        let echo_token = Token::new(Some(String::from("echo")), TokenType::Word);
        let iron_man_token = Token::new(Some(String::from("IronMan")), TokenType::Word);
        let redirection_token = Token::new(Some(String::from(">>")), TokenType::Redirection);
        let marvel_token2 = Token::new(Some(String::from("marvel")), TokenType::Word);

        let mut expected = vec![
            touch_token,
            marvel_token,
            logical_and_token,
            echo_token,
            iron_man_token,
            redirection_token,
            marvel_token2,
        ];
        expected.reverse();
        assert_eq!(ast.iterator, expected);
    }
}
