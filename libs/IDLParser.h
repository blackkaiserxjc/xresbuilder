
// Generated from IDL.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"




class  IDLParser : public antlr4::Parser {
public:
  enum {
    BooleanLiteral = 1, Bool = 2, Int = 3, Float = 4, False_ = 5, String = 6, 
    LeftBracket = 7, RightBracket = 8, LeftBrace = 9, RightBrace = 10, True_ = 11, 
    Comma = 12, Colon = 13, Identifier = 14, Whitespace = 15, Newline = 16
  };

  enum {
    RuleProgram = 0, RuleStatement = 1, RulePod = 2, RuleObject = 3, RuleField = 4, 
    RuleArray = 5
  };

  explicit IDLParser(antlr4::TokenStream *input);
  ~IDLParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ProgramContext;
  class StatementContext;
  class PodContext;
  class ObjectContext;
  class FieldContext;
  class ArrayContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PodContext *pod();
    ObjectContext *object();
    ArrayContext *array();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  PodContext : public antlr4::ParserRuleContext {
  public:
    PodContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Bool();
    antlr4::tree::TerminalNode *Int();
    antlr4::tree::TerminalNode *Float();
    antlr4::tree::TerminalNode *String();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PodContext* pod();

  class  ObjectContext : public antlr4::ParserRuleContext {
  public:
    ObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FieldContext *> field();
    FieldContext* field(size_t i);
    std::vector<antlr4::tree::TerminalNode *> Comma();
    antlr4::tree::TerminalNode* Comma(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ObjectContext* object();

  class  FieldContext : public antlr4::ParserRuleContext {
  public:
    FieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *Colon();
    StatementContext *statement();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FieldContext* field();

  class  ArrayContext : public antlr4::ParserRuleContext {
  public:
    ArrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LeftBracket();
    StatementContext *statement();
    antlr4::tree::TerminalNode *RightBracket();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayContext* array();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

