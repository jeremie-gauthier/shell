use crate::parser::rules::{expr, cmd, arg};
use crate::parser::BTNode;
use crate::{Token, TokenType};
use libc::c_char;
use std::ffi::{CStr};

fn c_str_to_rs(input: *const c_char) -> String {
    let c_str = unsafe {
        assert!(!input.is_null());
        CStr::from_ptr(input)
    };

    let r_str = c_str.to_str().unwrap_or_default();
    r_str.to_string()
}

#[no_mangle]
pub extern "C" fn parser(input: *const c_char) -> *const BTNode {
    let r_str = c_str_to_rs(input);

	// pas sur que ca fonctionne
	let end_token = Token::new(None, TokenType::End);
	let btree = Box::new(BTNode::new(end_token, None, None));
	Box::into_raw(btree)
}
