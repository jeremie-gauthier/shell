use std::os::raw::c_char;
use std::ffi::CString;
use std::ptr;

pub mod parser;
pub mod lexer;

#[no_mangle]
pub extern "C" fn hello_rust() -> *const u8 {
    "Hello, world!\0".as_ptr()
}

#[repr(C)]
pub enum TokenType {
    Whitespace = 0,
    Command,
    Operator,    // generic operator type for lexer
    Redirection, // is a specific operator
    Pipe,        // is a specific operator
    Separator,   // is a specific operator
    Logical,     // is a specific operator
    Unknown,
    End,
}

#[repr(C)]
pub struct Token {
    pub value: *const c_char,
    pub e_token_type: TokenType,
}

impl Token {
	pub fn new(value: Option<String>, e_token_type: TokenType) -> Self {
		match value {
			Some(v) => {
				let c_str = CString::new(v);
				if c_str.is_err() {
					return Token { value: ptr::null(), e_token_type: TokenType::Unknown };
				}

				Token { value: c_str.unwrap().as_ptr(), e_token_type }
			},
			None => Token { value: ptr::null(), e_token_type },
		}
	}
}
