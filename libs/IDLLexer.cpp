
// Generated from IDL.g4 by ANTLR 4.9.1

#include "IDLLexer.h"

using namespace antlr4;

IDLLexer::IDLLexer(CharStream *input)
    : Lexer(input)
{
    _interpreter = new atn::LexerATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

IDLLexer::~IDLLexer()
{
    delete _interpreter;
}

std::string IDLLexer::getGrammarFileName() const
{
    return "IDL.g4";
}

const std::vector<std::string> &IDLLexer::getRuleNames() const
{
    return _ruleNames;
}

const std::vector<std::string> &IDLLexer::getChannelNames() const
{
    return _channelNames;
}

const std::vector<std::string> &IDLLexer::getModeNames() const
{
    return _modeNames;
}

const std::vector<std::string> &IDLLexer::getTokenNames() const
{
    return _tokenNames;
}

dfa::Vocabulary &IDLLexer::getVocabulary() const
{
    return _vocabulary;
}

const std::vector<uint16_t> IDLLexer::getSerializedATN() const
{
    return _serializedATN;
}

const atn::ATN &IDLLexer::getATN() const
{
    return _atn;
}

// Static vars and initialization.
std::vector<dfa::DFA> IDLLexer::_decisionToDFA;
atn::PredictionContextCache IDLLexer::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN IDLLexer::_atn;
std::vector<uint16_t> IDLLexer::_serializedATN;

std::vector<std::string> IDLLexer::_ruleNames = {
    "BooleanLiteral", "Bool", "Int", "Long", "Float", "False_", "String",
    "LeftBracket", "RightBracket", "LeftBrace", "RightBrace", "True_", "Comma",
    "Colon", "Identifier", "IdentifierNondigit", "Nondigit", "Digit", "UniversalCharacterName",
    "HexQuad", "HexadecimalDigit", "Whitespace", "Newline"};

std::vector<std::string> IDLLexer::_channelNames = {
    "DEFAULT_TOKEN_CHANNEL", "HIDDEN"};

std::vector<std::string> IDLLexer::_modeNames = {
    "DEFAULT_MODE"};

std::vector<std::string> IDLLexer::_literalNames = {
    "", "", "'bool'", "'int'", "'long'", "'float'", "'false'", "'string'",
    "'['", "']'", "'{'", "'}'", "'true'", "','", "':'"};

std::vector<std::string> IDLLexer::_symbolicNames = {
    "", "BooleanLiteral", "Bool", "Int", "Long", "Float", "False_", "String",
    "LeftBracket", "RightBracket", "LeftBrace", "RightBrace", "True_", "Comma",
    "Colon", "Identifier", "Whitespace", "Newline"};

dfa::Vocabulary IDLLexer::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> IDLLexer::_tokenNames;

IDLLexer::Initializer::Initializer()
{
    // This code could be in a static initializer lambda, but VS doesn't allow access to private class members from there.
    for (size_t i = 0; i < _symbolicNames.size(); ++i)
    {
        std::string name = _vocabulary.getLiteralName(i);
        if (name.empty())
        {
            name = _vocabulary.getSymbolicName(i);
        }

        if (name.empty())
        {
            _tokenNames.push_back("<INVALID>");
        }
        else
        {
            _tokenNames.push_back(name);
        }
    }

    _serializedATN = {
        0x3,
        0x608b,
        0xa72a,
        0x8133,
        0xb9ed,
        0x417c,
        0x3be7,
        0x7786,
        0x5964,
        0x2,
        0x13,
        0x9a,
        0x8,
        0x1,
        0x4,
        0x2,
        0x9,
        0x2,
        0x4,
        0x3,
        0x9,
        0x3,
        0x4,
        0x4,
        0x9,
        0x4,
        0x4,
        0x5,
        0x9,
        0x5,
        0x4,
        0x6,
        0x9,
        0x6,
        0x4,
        0x7,
        0x9,
        0x7,
        0x4,
        0x8,
        0x9,
        0x8,
        0x4,
        0x9,
        0x9,
        0x9,
        0x4,
        0xa,
        0x9,
        0xa,
        0x4,
        0xb,
        0x9,
        0xb,
        0x4,
        0xc,
        0x9,
        0xc,
        0x4,
        0xd,
        0x9,
        0xd,
        0x4,
        0xe,
        0x9,
        0xe,
        0x4,
        0xf,
        0x9,
        0xf,
        0x4,
        0x10,
        0x9,
        0x10,
        0x4,
        0x11,
        0x9,
        0x11,
        0x4,
        0x12,
        0x9,
        0x12,
        0x4,
        0x13,
        0x9,
        0x13,
        0x4,
        0x14,
        0x9,
        0x14,
        0x4,
        0x15,
        0x9,
        0x15,
        0x4,
        0x16,
        0x9,
        0x16,
        0x4,
        0x17,
        0x9,
        0x17,
        0x4,
        0x18,
        0x9,
        0x18,
        0x3,
        0x2,
        0x3,
        0x2,
        0x5,
        0x2,
        0x34,
        0xa,
        0x2,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x4,
        0x3,
        0x4,
        0x3,
        0x4,
        0x3,
        0x4,
        0x3,
        0x5,
        0x3,
        0x5,
        0x3,
        0x5,
        0x3,
        0x5,
        0x3,
        0x5,
        0x3,
        0x6,
        0x3,
        0x6,
        0x3,
        0x6,
        0x3,
        0x6,
        0x3,
        0x6,
        0x3,
        0x6,
        0x3,
        0x7,
        0x3,
        0x7,
        0x3,
        0x7,
        0x3,
        0x7,
        0x3,
        0x7,
        0x3,
        0x7,
        0x3,
        0x8,
        0x3,
        0x8,
        0x3,
        0x8,
        0x3,
        0x8,
        0x3,
        0x8,
        0x3,
        0x8,
        0x3,
        0x8,
        0x3,
        0x9,
        0x3,
        0x9,
        0x3,
        0xa,
        0x3,
        0xa,
        0x3,
        0xb,
        0x3,
        0xb,
        0x3,
        0xc,
        0x3,
        0xc,
        0x3,
        0xd,
        0x3,
        0xd,
        0x3,
        0xd,
        0x3,
        0xd,
        0x3,
        0xd,
        0x3,
        0xe,
        0x3,
        0xe,
        0x3,
        0xf,
        0x3,
        0xf,
        0x3,
        0x10,
        0x3,
        0x10,
        0x3,
        0x10,
        0x7,
        0x10,
        0x6b,
        0xa,
        0x10,
        0xc,
        0x10,
        0xe,
        0x10,
        0x6e,
        0xb,
        0x10,
        0x3,
        0x11,
        0x3,
        0x11,
        0x5,
        0x11,
        0x72,
        0xa,
        0x11,
        0x3,
        0x12,
        0x3,
        0x12,
        0x3,
        0x13,
        0x3,
        0x13,
        0x3,
        0x14,
        0x3,
        0x14,
        0x3,
        0x14,
        0x3,
        0x14,
        0x3,
        0x14,
        0x3,
        0x14,
        0x3,
        0x14,
        0x3,
        0x14,
        0x3,
        0x14,
        0x3,
        0x14,
        0x5,
        0x14,
        0x82,
        0xa,
        0x14,
        0x3,
        0x15,
        0x3,
        0x15,
        0x3,
        0x15,
        0x3,
        0x15,
        0x3,
        0x15,
        0x3,
        0x16,
        0x3,
        0x16,
        0x3,
        0x17,
        0x6,
        0x17,
        0x8c,
        0xa,
        0x17,
        0xd,
        0x17,
        0xe,
        0x17,
        0x8d,
        0x3,
        0x17,
        0x3,
        0x17,
        0x3,
        0x18,
        0x3,
        0x18,
        0x5,
        0x18,
        0x94,
        0xa,
        0x18,
        0x3,
        0x18,
        0x5,
        0x18,
        0x97,
        0xa,
        0x18,
        0x3,
        0x18,
        0x3,
        0x18,
        0x2,
        0x2,
        0x19,
        0x3,
        0x3,
        0x5,
        0x4,
        0x7,
        0x5,
        0x9,
        0x6,
        0xb,
        0x7,
        0xd,
        0x8,
        0xf,
        0x9,
        0x11,
        0xa,
        0x13,
        0xb,
        0x15,
        0xc,
        0x17,
        0xd,
        0x19,
        0xe,
        0x1b,
        0xf,
        0x1d,
        0x10,
        0x1f,
        0x11,
        0x21,
        0x2,
        0x23,
        0x2,
        0x25,
        0x2,
        0x27,
        0x2,
        0x29,
        0x2,
        0x2b,
        0x2,
        0x2d,
        0x12,
        0x2f,
        0x13,
        0x3,
        0x2,
        0x6,
        0x5,
        0x2,
        0x43,
        0x5c,
        0x61,
        0x61,
        0x63,
        0x7c,
        0x3,
        0x2,
        0x32,
        0x3b,
        0x5,
        0x2,
        0x32,
        0x3b,
        0x43,
        0x48,
        0x63,
        0x68,
        0x4,
        0x2,
        0xb,
        0xb,
        0x22,
        0x22,
        0x2,
        0x9b,
        0x2,
        0x3,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x5,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x7,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x9,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0xb,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0xd,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0xf,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x11,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x13,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x15,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x17,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x19,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x1b,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x1d,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x1f,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x2d,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2,
        0x2f,
        0x3,
        0x2,
        0x2,
        0x2,
        0x3,
        0x33,
        0x3,
        0x2,
        0x2,
        0x2,
        0x5,
        0x35,
        0x3,
        0x2,
        0x2,
        0x2,
        0x7,
        0x3a,
        0x3,
        0x2,
        0x2,
        0x2,
        0x9,
        0x3e,
        0x3,
        0x2,
        0x2,
        0x2,
        0xb,
        0x43,
        0x3,
        0x2,
        0x2,
        0x2,
        0xd,
        0x49,
        0x3,
        0x2,
        0x2,
        0x2,
        0xf,
        0x4f,
        0x3,
        0x2,
        0x2,
        0x2,
        0x11,
        0x56,
        0x3,
        0x2,
        0x2,
        0x2,
        0x13,
        0x58,
        0x3,
        0x2,
        0x2,
        0x2,
        0x15,
        0x5a,
        0x3,
        0x2,
        0x2,
        0x2,
        0x17,
        0x5c,
        0x3,
        0x2,
        0x2,
        0x2,
        0x19,
        0x5e,
        0x3,
        0x2,
        0x2,
        0x2,
        0x1b,
        0x63,
        0x3,
        0x2,
        0x2,
        0x2,
        0x1d,
        0x65,
        0x3,
        0x2,
        0x2,
        0x2,
        0x1f,
        0x67,
        0x3,
        0x2,
        0x2,
        0x2,
        0x21,
        0x71,
        0x3,
        0x2,
        0x2,
        0x2,
        0x23,
        0x73,
        0x3,
        0x2,
        0x2,
        0x2,
        0x25,
        0x75,
        0x3,
        0x2,
        0x2,
        0x2,
        0x27,
        0x81,
        0x3,
        0x2,
        0x2,
        0x2,
        0x29,
        0x83,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2b,
        0x88,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2d,
        0x8b,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2f,
        0x96,
        0x3,
        0x2,
        0x2,
        0x2,
        0x31,
        0x34,
        0x5,
        0xd,
        0x7,
        0x2,
        0x32,
        0x34,
        0x5,
        0x19,
        0xd,
        0x2,
        0x33,
        0x31,
        0x3,
        0x2,
        0x2,
        0x2,
        0x33,
        0x32,
        0x3,
        0x2,
        0x2,
        0x2,
        0x34,
        0x4,
        0x3,
        0x2,
        0x2,
        0x2,
        0x35,
        0x36,
        0x7,
        0x64,
        0x2,
        0x2,
        0x36,
        0x37,
        0x7,
        0x71,
        0x2,
        0x2,
        0x37,
        0x38,
        0x7,
        0x71,
        0x2,
        0x2,
        0x38,
        0x39,
        0x7,
        0x6e,
        0x2,
        0x2,
        0x39,
        0x6,
        0x3,
        0x2,
        0x2,
        0x2,
        0x3a,
        0x3b,
        0x7,
        0x6b,
        0x2,
        0x2,
        0x3b,
        0x3c,
        0x7,
        0x70,
        0x2,
        0x2,
        0x3c,
        0x3d,
        0x7,
        0x76,
        0x2,
        0x2,
        0x3d,
        0x8,
        0x3,
        0x2,
        0x2,
        0x2,
        0x3e,
        0x3f,
        0x7,
        0x6e,
        0x2,
        0x2,
        0x3f,
        0x40,
        0x7,
        0x71,
        0x2,
        0x2,
        0x40,
        0x41,
        0x7,
        0x70,
        0x2,
        0x2,
        0x41,
        0x42,
        0x7,
        0x69,
        0x2,
        0x2,
        0x42,
        0xa,
        0x3,
        0x2,
        0x2,
        0x2,
        0x43,
        0x44,
        0x7,
        0x68,
        0x2,
        0x2,
        0x44,
        0x45,
        0x7,
        0x6e,
        0x2,
        0x2,
        0x45,
        0x46,
        0x7,
        0x71,
        0x2,
        0x2,
        0x46,
        0x47,
        0x7,
        0x63,
        0x2,
        0x2,
        0x47,
        0x48,
        0x7,
        0x76,
        0x2,
        0x2,
        0x48,
        0xc,
        0x3,
        0x2,
        0x2,
        0x2,
        0x49,
        0x4a,
        0x7,
        0x68,
        0x2,
        0x2,
        0x4a,
        0x4b,
        0x7,
        0x63,
        0x2,
        0x2,
        0x4b,
        0x4c,
        0x7,
        0x6e,
        0x2,
        0x2,
        0x4c,
        0x4d,
        0x7,
        0x75,
        0x2,
        0x2,
        0x4d,
        0x4e,
        0x7,
        0x67,
        0x2,
        0x2,
        0x4e,
        0xe,
        0x3,
        0x2,
        0x2,
        0x2,
        0x4f,
        0x50,
        0x7,
        0x75,
        0x2,
        0x2,
        0x50,
        0x51,
        0x7,
        0x76,
        0x2,
        0x2,
        0x51,
        0x52,
        0x7,
        0x74,
        0x2,
        0x2,
        0x52,
        0x53,
        0x7,
        0x6b,
        0x2,
        0x2,
        0x53,
        0x54,
        0x7,
        0x70,
        0x2,
        0x2,
        0x54,
        0x55,
        0x7,
        0x69,
        0x2,
        0x2,
        0x55,
        0x10,
        0x3,
        0x2,
        0x2,
        0x2,
        0x56,
        0x57,
        0x7,
        0x5d,
        0x2,
        0x2,
        0x57,
        0x12,
        0x3,
        0x2,
        0x2,
        0x2,
        0x58,
        0x59,
        0x7,
        0x5f,
        0x2,
        0x2,
        0x59,
        0x14,
        0x3,
        0x2,
        0x2,
        0x2,
        0x5a,
        0x5b,
        0x7,
        0x7d,
        0x2,
        0x2,
        0x5b,
        0x16,
        0x3,
        0x2,
        0x2,
        0x2,
        0x5c,
        0x5d,
        0x7,
        0x7f,
        0x2,
        0x2,
        0x5d,
        0x18,
        0x3,
        0x2,
        0x2,
        0x2,
        0x5e,
        0x5f,
        0x7,
        0x76,
        0x2,
        0x2,
        0x5f,
        0x60,
        0x7,
        0x74,
        0x2,
        0x2,
        0x60,
        0x61,
        0x7,
        0x77,
        0x2,
        0x2,
        0x61,
        0x62,
        0x7,
        0x67,
        0x2,
        0x2,
        0x62,
        0x1a,
        0x3,
        0x2,
        0x2,
        0x2,
        0x63,
        0x64,
        0x7,
        0x2e,
        0x2,
        0x2,
        0x64,
        0x1c,
        0x3,
        0x2,
        0x2,
        0x2,
        0x65,
        0x66,
        0x7,
        0x3c,
        0x2,
        0x2,
        0x66,
        0x1e,
        0x3,
        0x2,
        0x2,
        0x2,
        0x67,
        0x6c,
        0x5,
        0x21,
        0x11,
        0x2,
        0x68,
        0x6b,
        0x5,
        0x21,
        0x11,
        0x2,
        0x69,
        0x6b,
        0x5,
        0x25,
        0x13,
        0x2,
        0x6a,
        0x68,
        0x3,
        0x2,
        0x2,
        0x2,
        0x6a,
        0x69,
        0x3,
        0x2,
        0x2,
        0x2,
        0x6b,
        0x6e,
        0x3,
        0x2,
        0x2,
        0x2,
        0x6c,
        0x6a,
        0x3,
        0x2,
        0x2,
        0x2,
        0x6c,
        0x6d,
        0x3,
        0x2,
        0x2,
        0x2,
        0x6d,
        0x20,
        0x3,
        0x2,
        0x2,
        0x2,
        0x6e,
        0x6c,
        0x3,
        0x2,
        0x2,
        0x2,
        0x6f,
        0x72,
        0x5,
        0x23,
        0x12,
        0x2,
        0x70,
        0x72,
        0x5,
        0x27,
        0x14,
        0x2,
        0x71,
        0x6f,
        0x3,
        0x2,
        0x2,
        0x2,
        0x71,
        0x70,
        0x3,
        0x2,
        0x2,
        0x2,
        0x72,
        0x22,
        0x3,
        0x2,
        0x2,
        0x2,
        0x73,
        0x74,
        0x9,
        0x2,
        0x2,
        0x2,
        0x74,
        0x24,
        0x3,
        0x2,
        0x2,
        0x2,
        0x75,
        0x76,
        0x9,
        0x3,
        0x2,
        0x2,
        0x76,
        0x26,
        0x3,
        0x2,
        0x2,
        0x2,
        0x77,
        0x78,
        0x7,
        0x5e,
        0x2,
        0x2,
        0x78,
        0x79,
        0x7,
        0x77,
        0x2,
        0x2,
        0x79,
        0x7a,
        0x3,
        0x2,
        0x2,
        0x2,
        0x7a,
        0x82,
        0x5,
        0x29,
        0x15,
        0x2,
        0x7b,
        0x7c,
        0x7,
        0x5e,
        0x2,
        0x2,
        0x7c,
        0x7d,
        0x7,
        0x57,
        0x2,
        0x2,
        0x7d,
        0x7e,
        0x3,
        0x2,
        0x2,
        0x2,
        0x7e,
        0x7f,
        0x5,
        0x29,
        0x15,
        0x2,
        0x7f,
        0x80,
        0x5,
        0x29,
        0x15,
        0x2,
        0x80,
        0x82,
        0x3,
        0x2,
        0x2,
        0x2,
        0x81,
        0x77,
        0x3,
        0x2,
        0x2,
        0x2,
        0x81,
        0x7b,
        0x3,
        0x2,
        0x2,
        0x2,
        0x82,
        0x28,
        0x3,
        0x2,
        0x2,
        0x2,
        0x83,
        0x84,
        0x5,
        0x2b,
        0x16,
        0x2,
        0x84,
        0x85,
        0x5,
        0x2b,
        0x16,
        0x2,
        0x85,
        0x86,
        0x5,
        0x2b,
        0x16,
        0x2,
        0x86,
        0x87,
        0x5,
        0x2b,
        0x16,
        0x2,
        0x87,
        0x2a,
        0x3,
        0x2,
        0x2,
        0x2,
        0x88,
        0x89,
        0x9,
        0x4,
        0x2,
        0x2,
        0x89,
        0x2c,
        0x3,
        0x2,
        0x2,
        0x2,
        0x8a,
        0x8c,
        0x9,
        0x5,
        0x2,
        0x2,
        0x8b,
        0x8a,
        0x3,
        0x2,
        0x2,
        0x2,
        0x8c,
        0x8d,
        0x3,
        0x2,
        0x2,
        0x2,
        0x8d,
        0x8b,
        0x3,
        0x2,
        0x2,
        0x2,
        0x8d,
        0x8e,
        0x3,
        0x2,
        0x2,
        0x2,
        0x8e,
        0x8f,
        0x3,
        0x2,
        0x2,
        0x2,
        0x8f,
        0x90,
        0x8,
        0x17,
        0x2,
        0x2,
        0x90,
        0x2e,
        0x3,
        0x2,
        0x2,
        0x2,
        0x91,
        0x93,
        0x7,
        0xf,
        0x2,
        0x2,
        0x92,
        0x94,
        0x7,
        0xc,
        0x2,
        0x2,
        0x93,
        0x92,
        0x3,
        0x2,
        0x2,
        0x2,
        0x93,
        0x94,
        0x3,
        0x2,
        0x2,
        0x2,
        0x94,
        0x97,
        0x3,
        0x2,
        0x2,
        0x2,
        0x95,
        0x97,
        0x7,
        0xc,
        0x2,
        0x2,
        0x96,
        0x91,
        0x3,
        0x2,
        0x2,
        0x2,
        0x96,
        0x95,
        0x3,
        0x2,
        0x2,
        0x2,
        0x97,
        0x98,
        0x3,
        0x2,
        0x2,
        0x2,
        0x98,
        0x99,
        0x8,
        0x18,
        0x2,
        0x2,
        0x99,
        0x30,
        0x3,
        0x2,
        0x2,
        0x2,
        0xb,
        0x2,
        0x33,
        0x6a,
        0x6c,
        0x71,
        0x81,
        0x8d,
        0x93,
        0x96,
        0x3,
        0x8,
        0x2,
        0x2,
    };

    atn::ATNDeserializer deserializer;
    _atn = deserializer.deserialize(_serializedATN);

    size_t count = _atn.getNumberOfDecisions();
    _decisionToDFA.reserve(count);
    for (size_t i = 0; i < count; i++)
    {
        _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
    }
}

IDLLexer::Initializer IDLLexer::_init;
