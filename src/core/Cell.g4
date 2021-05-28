grammar Cell;

/* parser */
program:
    statement
    ;

statement:
    pod
    | object
    | array
    ;

object:
    field (Comma field)*
    ;

field:
    pod
    | array
    ;

pod:
    BooleanLiteral
    | StringLiteral
    | IntegerLiteral
    | FloatingLiteral
    ;

array
    : LeftBracket statement (Semi statement)* RightBracket
    ;

/* lexer */
IntegerLiteral:
	DecimalLiteral
	| OctalLiteral
	| HexadecimalLiteral
	| BinaryLiteral;

FloatingLiteral:
	Fractionalconstant Exponentpart?
	| Digitsequence Exponentpart;

StringLiteral:
    '"' Schar* '"';

BooleanLiteral: False_ | True_;

/* keywords */
LeftBracket : '[';

RightBracket : ']';

Comma : ',';

Semi : ';';

False_ : 'false' | 'False' | 'FALSE';

True_ : 'true' | 'True' | 'TRUE';

/* fragment */
fragment Hexquad:
	HEXADECIMALDIGIT HEXADECIMALDIGIT HEXADECIMALDIGIT HEXADECIMALDIGIT;

fragment Universalcharactername:
	'\\u' Hexquad
	| '\\U' Hexquad Hexquad;

Identifier:
	Identifiernondigit (Identifiernondigit | DIGIT)*;

fragment Identifiernondigit: NONDIGIT | Universalcharactername;

fragment NONDIGIT: [a-zA-Z_];

fragment DIGIT: [0-9];

DecimalLiteral: NONZERODIGIT ('\''? DIGIT)*;

OctalLiteral: '0' ('\''? OCTALDIGIT)*;

HexadecimalLiteral: ('0x' | '0X') HEXADECIMALDIGIT (
		'\''? HEXADECIMALDIGIT
	)*;

BinaryLiteral: ('0b' | '0B') BINARYDIGIT ('\''? BINARYDIGIT)*;

fragment NONZERODIGIT: [1-9];

fragment OCTALDIGIT: [0-7];

fragment HEXADECIMALDIGIT: [0-9a-fA-F];

fragment BINARYDIGIT: [01];

fragment Cchar:
	~ ['\\\r\n]
	| Escapesequence
	| Universalcharactername;
fragment Escapesequence:
	Simpleescapesequence
	| Octalescapesequence
	| Hexadecimalescapesequence;
fragment Simpleescapesequence:
	'\\\''
	| '\\"'
	| '\\?'
	| '\\\\'
	| '\\a'
	| '\\b'
	| '\\f'
	| '\\n'
	| '\\r'
	| ('\\' ('\r' '\n'? | '\n'))
	| '\\t'
	| '\\v';

fragment Octalescapesequence:
	'\\' OCTALDIGIT
	| '\\' OCTALDIGIT OCTALDIGIT
	| '\\' OCTALDIGIT OCTALDIGIT OCTALDIGIT;

fragment Hexadecimalescapesequence: '\\x' HEXADECIMALDIGIT+;

fragment Fractionalconstant:
	Digitsequence? '.' Digitsequence
	| Digitsequence '.';

fragment Exponentpart:
	'e' SIGN? Digitsequence
	| 'E' SIGN? Digitsequence;

fragment SIGN: [+-];

fragment Digitsequence: DIGIT ('\''? DIGIT)*;

fragment Schar:
	~ ["\\\r\n]
	| Escapesequence
	| Universalcharactername;
fragment Rawstring: 'R"' (( '\\' ["()] )|~[\r\n (])*? '(' ~[)]*? ')'  (( '\\' ["()]) | ~[\r\n "])*? '"';

/* skip */
Whitespace: [ \t]+ -> skip;

Newline: ('\r' '\n'? | '\n') -> skip;