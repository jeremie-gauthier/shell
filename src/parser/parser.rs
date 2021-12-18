use crate::ast::Node;

type AST = Node;

pub fn parser(input: String) -> Option<Node> {
	match AST::try_from(input) {
		Ok(ast) => Some(ast),
		Err(err) => {
			eprintln!("Parser error: {}", err);
			None
		}
	}
}
