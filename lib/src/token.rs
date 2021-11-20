use std::os::raw::c_char;

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

#[repr(C)]
pub struct Lexer {
    pub input: *const c_char,
    pub tokens: *const Token,
    pub tokens_len: libc::c_ulong,
    pub tokens_cap: libc::c_ulong,
    pub input_idx: usize,
    pub has_error: bool,
}
