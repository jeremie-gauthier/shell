use crate::lexer::Lexer;
use crate::parser::Parser;
use crate::{c_str_to_rs, BTNode};
use libc::c_char;
use std::ptr;

#[no_mangle]
pub extern "C" fn parser(input: *const c_char) -> *const BTNode {
    let r_str = c_str_to_rs(input);
    let lexer = Lexer::new(r_str);
    let parser = Parser::new(lexer);
    if parser.is_err() {
        return ptr::null();
    }

    match parser.unwrap().parse_input() {
        Ok(ast) => {
            println!("{:?}", ast);
            Box::into_raw(Box::new(ast))
        }
        Err(err) => {
            eprintln!("Parser error: {}", err);
            ptr::null()
        }
    }

    // // pas sur que ca fonctionne
    // let end_token = Token::new(None, TokenType::End);
    // let btree = Box::new(BTNode::new(end_token, None, None));
    // Box::into_raw(btree)
}
