grammar MyGrammar;

// Parser rule
parse_all:
    srule EOF;

srule   
    : 'a' srule 'b'
    | 'a' 'b'
;

// Lexer rule
UNKNOWN_KEYWORD : .;