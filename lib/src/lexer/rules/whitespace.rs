use std::ffi::CStr;
use std::ptr;

use crate::{Lexer, Token, TokenType};

#[no_mangle]
pub extern "C" fn whitespace(lexer: *mut Lexer) -> Token {
    let c_str = unsafe { CStr::from_ptr((*lexer).input) };
    let input = c_str.to_str();

    if input.is_err() {
        unsafe {
            (*lexer).input_idx += 1;
        };
        return Token {
            value: ptr::null(),
            e_token_type: TokenType::Whitespace,
        };
    }

    let mut chars_indices = input.unwrap().char_indices();
    if chars_indices
        .nth(unsafe { (*lexer).input_idx } as usize)
        .is_some()
    {
        let next_non_whitspace_char = chars_indices.find(|(_, c)| !c.is_whitespace());
        let next_char_idx = next_non_whitspace_char.unwrap().0;
        unsafe {
            (*lexer).input_idx = next_char_idx;
        };
    } else {
        unsafe {
            (*lexer).input_idx += 1;
        };
    }

    Token {
        value: ptr::null(),
        e_token_type: TokenType::Whitespace,
    }
}
