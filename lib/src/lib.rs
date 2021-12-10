use crate::lexer::Lexer;
use crate::parser::error::ParserError;
use crate::parser::Parser;
use std::error::Error;
use std::ffi::{CStr, CString};
use std::os::raw::c_char;
use std::{fmt, ptr};

pub mod lexer;
pub mod parser;

pub fn c_str_to_rs(input: *const c_char) -> String {
    let c_str = unsafe {
        if !input.is_null() {
            Some(CStr::from_ptr(input))
        } else {
            None
        }
    };

    match c_str {
        Some(c_string) => {
            let r_str = c_string.to_str().unwrap_or_default();
            r_str.to_string()
        }
        None => String::default(),
    }
}

#[repr(C)]
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum TokenType {
    Whitespace = 0, // space
    Word,           // alnum
    Operator,       // generic operator type for lexer
    Redirection,    // < << > >> &>
    Pipe,           // |
    Separator,      // ;
    Logical,        // && ||
    Unknown,        // ???
    End,            // EOF
}

#[repr(C)]
#[derive(Clone)]
pub struct Token {
    pub value: *const c_char,
    pub e_token_type: TokenType,
}

impl fmt::Debug for Token {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("Token")
            .field("value", &c_str_to_rs(self.value))
            .field("token_type", &self.e_token_type)
            .finish()
    }
}

impl Default for Token {
    fn default() -> Self {
        Token {
            value: ptr::null(),
            e_token_type: TokenType::Unknown,
        }
    }
}

impl Token {
    pub fn new(value: Option<String>, e_token_type: TokenType) -> Self {
        match value {
            Some(v) => match CString::new(v) {
                Ok(c_str) => Token {
                    value: c_str.into_raw(),
                    e_token_type,
                },
                Err(_err) => Token::default(),
            },
            None => Token {
                value: ptr::null(),
                e_token_type,
            },
        }
    }
}

#[repr(C)]
// Do not change the order of attributes as it would break the
//  C memory representation
pub struct BTNode {
    left: Option<Box<BTNode>>,
    right: Option<Box<BTNode>>,
    token: Token,
}

impl fmt::Debug for BTNode {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("BTNode")
            .field("token", &self.token)
            .field("left", &self.left)
            .field("right", &self.right)
            .finish()
    }
}

impl BTNode {
    pub fn new(token: Token, left: Option<BTNode>, right: Option<BTNode>) -> Self {
        BTNode {
            token,
            left: match left {
                Some(left_node) => Some(Box::new(left_node)),
                None => None,
            },
            right: match right {
                Some(right_node) => Some(Box::new(right_node)),
                None => None,
            },
        }
    }
}

impl fmt::Display for BTNode {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{:?}", self.token)
    }
}

impl Error for BTNode {}

impl TryFrom<String> for BTNode {
    type Error = ParserError;

    fn try_from(input: String) -> Result<BTNode, ParserError> {
        let lexer = Lexer::new(input);
        let parser = Parser::new(lexer);
        parser.parse_input()
    }
}
