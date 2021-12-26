use std::iter::Peekable;
use std::process::Command;

use crate::ast::AST;
use crate::lexer::{Token, TokenType};
use crate::parser::ParserError;

#[derive(Debug)]
pub enum InterpreterError {
    ParserError(ParserError),
    RuntimeError,
}

impl InterpreterError {
    fn from_parse(err: ParserError) -> InterpreterError {
        InterpreterError::ParserError(err)
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

// impl From<&mut Peekable<AST>> for Command {
//     fn from(ast: &mut Peekable<AST>) -> Self {
//         let mut input_cmd = ast.take_while(|token| token.token_type == TokenType::Word);
//         println!("{:?}", input_cmd);
//         let bin = input_cmd.next().unwrap().value;
//         let command = input_cmd.fold(Command::new(bin), |mut shell_cmd, token| {
//             shell_cmd.arg(token.value);
//             shell_cmd
//         });
//         ShellCommand { command }
//     }
// }

// struct Interpreter {
//     ast: AST,
//     command: Option<Command>,
// }

// impl Interpreter {
//     pub fn new(input: String) -> Result<Self, InterpreterError> {
//         let ast = AST::try_from(input).map_err(InterpreterError::from_parse)?;
//         Ok(Interpreter { ast, command: None })
//     }

//     fn get_command(mut self) {
//         let mut input_cmd = self
//             .ast
//             .take_while(|token| token.token_type == TokenType::Word);
//         let bin = input_cmd.next().unwrap().value;
//         let command = input_cmd.fold(Command::new(bin), |mut shell_cmd, token| {
//             shell_cmd.arg(token.value);
//             shell_cmd
//         });
//         self.command = Some(command);
//     }

//     pub fn eval(mut self) -> Result<(), InterpreterError> {
//         let mut peekable = self.ast.peekable();
//         while let Some(token) = peekable.peek() {
//             match token.token_type {
//                 TokenType::Word => self.get_command(),
//                 _ => (),
//             }
//         }
//         Ok(())
//     }
// }

#[derive(Debug)]
enum InterpreterObjects {
    Command(Command),
    TokenType(TokenType),
}

type Stack = Vec<InterpreterObjects>;

impl From<AST> for Stack {
    fn from(ast: AST) -> Self {
        let mut ast_peekable = ast.peekable();
        let mut stack = Vec::new();
        let mut operators: Vec<TokenType> = Vec::new();

        while let Some(token) = ast_peekable.peek() {
            println!("BUILDING (token):: {:?}", token);
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
            println!("BUILDING (stack):: {:?}", stack);
        }
        for operator in operators {
            stack.push(InterpreterObjects::TokenType(operator));
        }
        stack
    }
}

// Si je me souviens bien, il faut a un moment garder le code retour du dernier bin lancé
// Pourquoi pas faire une impl de Interpreter, qui conserverait les metadata de ce genre

//  il faut en faire une struct !
pub fn interpreter(input: String) -> Result<(), InterpreterError> {
    // let mut interpreter = Interpreter::new(input)?;
    // interpreter.eval()

    let ast = AST::try_from(input).map_err(InterpreterError::from_parse)?;
    let stack = Stack::from(ast);
    println!("{:?}", stack);
    // println!("{:?}", ast);
    // let mut child_cmd: Option<ShellCommand> = None;
    // let mut can_run_next_cmd = true;

    // while let Some(token) = ast.peek() {
    //     println!("{:?}", token);

    //     match token.token_type {
    //         TokenType::Word => child_cmd = Some(ShellCommand::from(&mut ast)),
    //         _ => {
    //             let result = child_cmd.unwrap().command.status();
    //             match token.token_type {
    //                 TokenType::Logical => {
    //                     if token.value == "&&" {
    //                         can_run_next_cmd = result.unwrap().success();
    //                     } else if token.value == "||" {
    //                         can_run_next_cmd = !result.unwrap().success();
    //                     }
    //                 }
    //                 _ => (),
    //             }

    //             ast.next();
    //         }
    //     };
    // }

    // let result = child_cmd.unwrap().command.status();
    // println!("{:?}", result.unwrap());

    Ok(())
}
