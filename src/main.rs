mod ast;
mod interpreter;
mod lexer;
mod parser;

use interpreter::{interpreter, InterpreterError};
use rustyline::error::ReadlineError;
use rustyline::Editor;

fn main() {
	let mut rl = Editor::<()>::new();

	loop {
		let readline = rl.readline(">> ");
		match readline {
			Ok(line) => {
				println!("Line: {}", line);
				match interpreter(line) {
					Ok(()) => println!("succeed"),
					Err(InterpreterError::ParserError(e)) => {
						// I can go with further granularity with:
						// Err(InterpreterError::ParserError(ParserError::UnexpectedToken))
						// Enumerating all possibilities and writing custom err msg like this
						eprintln!("failed with a parse error {:?}", e)
					}
					Err(e) => eprintln!("failed {:?}", e),
				}
			}
			Err(ReadlineError::Eof) => break,
			Err(e) => eprintln!("readline error: {}", e),
		}
	}
}
