grammar IDL;

program
  : statement
  ;

statement
  : pod
  | object
  | array
  ;

pod
  : Bool
  | Int
  | Long
  | Float
  | String;

object
  : field (Comma field)*
  ;

field
  :  Identifier Colon statement
  ;

array
  : LeftBracket statement RightBracket
  ;


/* keywords */
BooleanLiteral: False_ | True_;

Bool: 'bool';

Int: 'int';

Long: 'long';

Float: 'float';

False_: 'false';

String: 'string';

LeftBracket: '[';

RightBracket: ']';

LeftBrace: '{';

RightBrace: '}';

True_ : 'true';

Comma: ',';

Colon: ':';

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

Whitespace: [ \t]+ -> skip;

Newline: ('\r' '\n'? | '\n') -> skip;