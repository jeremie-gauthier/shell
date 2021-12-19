use crate::ast::AST;

pub fn parser(input: String) -> Option<AST> {
	match AST::try_from(input) {
		Ok(ast) => Some(ast),
		Err(err) => {
			eprintln!("Parser error: {}", err);
			None
		}
	}
}
