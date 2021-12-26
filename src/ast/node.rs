use crate::lexer::Token;

#[derive(Debug, PartialEq, Clone)]
pub struct Node {
    pub token: Token,
    pub left: Option<Box<Node>>,
    pub right: Option<Box<Node>>,
}

impl Node {
    pub fn new(token: Token, left: Option<Node>, right: Option<Node>) -> Self {
        let get_node = |node: Node| Box::new(node);

        Node {
            token,
            left: left.map(get_node),
            right: right.map(get_node),
        }
    }
}
