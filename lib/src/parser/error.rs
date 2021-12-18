use std::fmt;

#[derive(Debug, PartialEq)]
pub enum ParserError {
    UnexpectedToken,
}

impl fmt::Display for ParserError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let description = match *self {
            ParserError::UnexpectedToken => "unexpected token",
        };
        f.write_str(description)
    }
}
