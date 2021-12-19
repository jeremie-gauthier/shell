pub mod ast;
pub mod lexer;
pub mod parser;

use rustyline::error::ReadlineError;
use rustyline::Editor;

fn main() {
	let mut rl = Editor::<()>::new();

	loop {
		let readline = rl.readline(">> ");
		match readline {
			Ok(line) => {
				println!("Line: {}", line);
				if let Some(ast) = parser::parser::parser(line) {
					println!("{:?}", ast);
				}
			}
			Err(ReadlineError::Eof) => break,
			Err(e) => eprintln!("readline error: {}", e),
		}
	}
}
