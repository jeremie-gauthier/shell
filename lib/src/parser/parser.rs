use crate::{c_str_to_rs, BTNode};
use libc::c_char;
use std::ptr;

type AST = BTNode;

#[no_mangle]
pub extern "C" fn parser(input: *const c_char) -> *const BTNode {
    let r_str = c_str_to_rs(input);

    match AST::try_from(r_str) {
        Ok(ast) => {
            println!("{:?}", ast);
            Box::into_raw(Box::new(ast))
        }
        Err(err) => {
            eprintln!("Parser error: {}", err);
            ptr::null()
        }
    }
}
