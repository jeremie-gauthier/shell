use std::io;
use std::iter::Peekable;
use std::process::Command;

use crate::ast::AST;
use crate::lexer::TokenType;
use crate::parser::ParserError;

#[derive(Debug)]
pub enum InterpreterError {
    ParserError(ParserError),
    RuntimeError(io::Error),
}

impl InterpreterError {
    fn from_parse(err: ParserError) -> InterpreterError {
        InterpreterError::ParserError(err)
    }

    fn from_exec(err: io::Error) -> InterpreterError {
        InterpreterError::RuntimeError(err)
    }
}

struct ShellCommand {
    command: Command,
}

impl From<&mut Peekable<AST>> for ShellCommand {
    fn from(ast: &mut Peekable<AST>) -> Self {
        let bin = ast.next().unwrap().value;
        let mut command = Command::new(bin);

        while let Some(token) = ast.peek() {
            match token.token_type {
                TokenType::Word => {
                    command.arg(&token.value);
                    ast.next();
                }
                _ => break,
            }
        }

        ShellCommand { command }
    }
}

#[derive(Debug)]
enum InterpreterObjects {
    Command(Command),
    TokenType(TokenType),
}

impl From<AST> for Vec<InterpreterObjects> {
    fn from(ast: AST) -> Self {
        let mut ast_peekable = ast.peekable();
        let mut stack = Vec::new();
        let mut operators: Vec<TokenType> = Vec::new();

        while let Some(token) = ast_peekable.peek() {
            match token.token_type {
                TokenType::Word => {
                    let command = ShellCommand::from(&mut ast_peekable).command;
                    stack.push(InterpreterObjects::Command(command));
                }
                _ => {
                    match operators.last() {
                        Some(operator) => {
                            if *operator < token.token_type {
                                let interpreter_obj =
                                    InterpreterObjects::TokenType(operators.pop().unwrap());
                                stack.push(interpreter_obj);
                                operators.push(token.token_type);
                            }
                        }
                        None => operators.push(token.token_type),
                    }
                    ast_peekable.next();
                }
            };
        }
        while !operators.is_empty() {
            stack.push(InterpreterObjects::TokenType(operators.pop().unwrap()));
        }
        stack
    }
}

// Si je me souviens bien, il faut a un moment garder le code retour du dernier bin lancé
// Pourquoi pas faire une impl de Interpreter, qui conserverait les metadata de ce genre

//  il faut en faire une struct !
pub fn interpreter(input: String) -> Result<(), InterpreterError> {
    let ast = AST::try_from(input).map_err(InterpreterError::from_parse)?;
    let stack = Vec::from(ast);
    println!("{:?}", stack);

    let mut op1 = None;
    let mut op2 = None;
    let mut last_cmd_status;

    for token in stack {
        match token {
            InterpreterObjects::Command(command) => {
                if let None = op1 {
                    op1 = Some(command);
                } else if let None = op2 {
                    op2 = Some(command);
                } else {
                    return Err(InterpreterError::ParserError(ParserError::UnexpectedToken));
                }
            }
            InterpreterObjects::TokenType(token_type) => match token_type {
                TokenType::LogicalAnd => {
                    last_cmd_status = op1.unwrap().status().map_err(InterpreterError::from_exec)?;
                    op1 = None;
                    if last_cmd_status.success() {
                        last_cmd_status =
                            op2.unwrap().status().map_err(InterpreterError::from_exec)?;
                    }
                    op2 = None;
                }
                TokenType::LogicalOr => {
                    last_cmd_status = op1.unwrap().status().map_err(InterpreterError::from_exec)?;
                    op1 = None;
                    if !last_cmd_status.success() {
                        last_cmd_status =
                            op2.unwrap().status().map_err(InterpreterError::from_exec)?;
                    }
                    op2 = None;
                }
                _ => (),
            },
        }
    }
    // let result = child_cmd.unwrap().command.status();
    // println!("{:?}", result.unwrap());

    Ok(())
}
