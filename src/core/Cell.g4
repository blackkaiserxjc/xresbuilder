grammar Cell;

program
    : statement
    ;

statement
    : object
    | array
    ;

object
    : field (',' field)*
    ;

field
    : Identifier
    | DigitSequence
    | StringLiteral
    | array
    ;

array
    : '[' statement (';' statement)* ']'
    ;

Identifier
  :   IdentifierNondigit
  (   IdentifierNondigit
  |   Digit
  )*
    ;
fragment
IdentifierNondigit
  :   Nondigit
  |   UniversalCharacterName
  ;

fragment
Nondigit
  :   [a-zA-Z_]
    ;

fragment
Digit
  :   [0-9]
    ;

fragment
UniversalCharacterName
  :   '\\u' HexQuad
  |   '\\U' HexQuad HexQuad
  ;

fragment
HexQuad
  :   HexadecimalDigit HexadecimalDigit HexadecimalDigit HexadecimalDigit
  ;

fragment
HexadecimalDigit
  :   [0-9a-fA-F]
    ;

DigitSequence
    :   Digit+
    ;

StringLiteral
    : '"' CCharSequence'"'
    ;

fragment
CCharSequence
    :   CChar+
    ;

fragment
CChar
    :   ~['\\\r\n]
    |   EscapeSequence
    ;
fragment
EscapeSequence
    :   SimpleEscapeSequence
    |   OctalEscapeSequence
    |   HexadecimalEscapeSequence
    |   UniversalCharacterName
    ;
fragment
SimpleEscapeSequence
    :   '\\' ['"?abfnrtv\\]
    ;
fragment
OctalEscapeSequence
    :   '\\' OctalDigit OctalDigit? OctalDigit?
    ;
fragment
HexadecimalEscapeSequence
    :   '\\x' HexadecimalDigit+
    ;

fragment
OctalConstant
    :   '0' OctalDigit*
    ;

fragment
OctalDigit
    :   [0-7]
    ;

Whitespace: [ \t]+ -> skip;

Newline: ('\r' '\n'? | '\n') -> skip;