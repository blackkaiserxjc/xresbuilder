
// Generated from Field.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"




class  FieldLexer : public antlr4::Lexer {
public:
  enum {
    BooleanLiteral = 1, Bool = 2, Int = 3, Float = 4, False_ = 5, String = 6, 
    LeftBracket = 7, RightBracket = 8, LeftBrace = 9, RightBrace = 10, True_ = 11, 
    Comma = 12, Colon = 13, Identifier = 14, Whitespace = 15, Newline = 16
  };

  explicit FieldLexer(antlr4::CharStream *input);
  ~FieldLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

