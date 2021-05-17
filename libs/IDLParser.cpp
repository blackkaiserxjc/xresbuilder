
// Generated from IDL.g4 by ANTLR 4.9.1


#include "IDLVisitor.h"

#include "IDLParser.h"


using namespace antlrcpp;
using namespace antlr4;

IDLParser::IDLParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

IDLParser::~IDLParser() {
  delete _interpreter;
}

std::string IDLParser::getGrammarFileName() const {
  return "IDL.g4";
}

const std::vector<std::string>& IDLParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& IDLParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

IDLParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::StatementContext* IDLParser::ProgramContext::statement() {
  return getRuleContext<IDLParser::StatementContext>(0);
}


size_t IDLParser::ProgramContext::getRuleIndex() const {
  return IDLParser::RuleProgram;
}


antlrcpp::Any IDLParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::ProgramContext* IDLParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, IDLParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(12);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

IDLParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IDLParser::PodContext* IDLParser::StatementContext::pod() {
  return getRuleContext<IDLParser::PodContext>(0);
}

IDLParser::ObjectContext* IDLParser::StatementContext::object() {
  return getRuleContext<IDLParser::ObjectContext>(0);
}

IDLParser::ArrayContext* IDLParser::StatementContext::array() {
  return getRuleContext<IDLParser::ArrayContext>(0);
}


size_t IDLParser::StatementContext::getRuleIndex() const {
  return IDLParser::RuleStatement;
}


antlrcpp::Any IDLParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::StatementContext* IDLParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, IDLParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(17);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case IDLParser::Bool:
      case IDLParser::Int:
      case IDLParser::Float:
      case IDLParser::String: {
        enterOuterAlt(_localctx, 1);
        setState(14);
        pod();
        break;
      }

      case IDLParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(15);
        object();
        break;
      }

      case IDLParser::LeftBracket: {
        enterOuterAlt(_localctx, 3);
        setState(16);
        array();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PodContext ------------------------------------------------------------------

IDLParser::PodContext::PodContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::PodContext::Bool() {
  return getToken(IDLParser::Bool, 0);
}

tree::TerminalNode* IDLParser::PodContext::Int() {
  return getToken(IDLParser::Int, 0);
}

tree::TerminalNode* IDLParser::PodContext::Float() {
  return getToken(IDLParser::Float, 0);
}

tree::TerminalNode* IDLParser::PodContext::String() {
  return getToken(IDLParser::String, 0);
}


size_t IDLParser::PodContext::getRuleIndex() const {
  return IDLParser::RulePod;
}


antlrcpp::Any IDLParser::PodContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLVisitor*>(visitor))
    return parserVisitor->visitPod(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::PodContext* IDLParser::pod() {
  PodContext *_localctx = _tracker.createInstance<PodContext>(_ctx, getState());
  enterRule(_localctx, 4, IDLParser::RulePod);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(19);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << IDLParser::Bool)
      | (1ULL << IDLParser::Int)
      | (1ULL << IDLParser::Float)
      | (1ULL << IDLParser::String))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectContext ------------------------------------------------------------------

IDLParser::ObjectContext::ObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<IDLParser::FieldContext *> IDLParser::ObjectContext::field() {
  return getRuleContexts<IDLParser::FieldContext>();
}

IDLParser::FieldContext* IDLParser::ObjectContext::field(size_t i) {
  return getRuleContext<IDLParser::FieldContext>(i);
}

std::vector<tree::TerminalNode *> IDLParser::ObjectContext::Comma() {
  return getTokens(IDLParser::Comma);
}

tree::TerminalNode* IDLParser::ObjectContext::Comma(size_t i) {
  return getToken(IDLParser::Comma, i);
}


size_t IDLParser::ObjectContext::getRuleIndex() const {
  return IDLParser::RuleObject;
}


antlrcpp::Any IDLParser::ObjectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLVisitor*>(visitor))
    return parserVisitor->visitObject(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::ObjectContext* IDLParser::object() {
  ObjectContext *_localctx = _tracker.createInstance<ObjectContext>(_ctx, getState());
  enterRule(_localctx, 6, IDLParser::RuleObject);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(21);
    field();
    setState(26);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(22);
        match(IDLParser::Comma);
        setState(23);
        field(); 
      }
      setState(28);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldContext ------------------------------------------------------------------

IDLParser::FieldContext::FieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::FieldContext::Identifier() {
  return getToken(IDLParser::Identifier, 0);
}

tree::TerminalNode* IDLParser::FieldContext::Colon() {
  return getToken(IDLParser::Colon, 0);
}

IDLParser::StatementContext* IDLParser::FieldContext::statement() {
  return getRuleContext<IDLParser::StatementContext>(0);
}


size_t IDLParser::FieldContext::getRuleIndex() const {
  return IDLParser::RuleField;
}


antlrcpp::Any IDLParser::FieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLVisitor*>(visitor))
    return parserVisitor->visitField(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::FieldContext* IDLParser::field() {
  FieldContext *_localctx = _tracker.createInstance<FieldContext>(_ctx, getState());
  enterRule(_localctx, 8, IDLParser::RuleField);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(29);
    match(IDLParser::Identifier);
    setState(30);
    match(IDLParser::Colon);
    setState(31);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayContext ------------------------------------------------------------------

IDLParser::ArrayContext::ArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IDLParser::ArrayContext::LeftBracket() {
  return getToken(IDLParser::LeftBracket, 0);
}

IDLParser::StatementContext* IDLParser::ArrayContext::statement() {
  return getRuleContext<IDLParser::StatementContext>(0);
}

tree::TerminalNode* IDLParser::ArrayContext::RightBracket() {
  return getToken(IDLParser::RightBracket, 0);
}


size_t IDLParser::ArrayContext::getRuleIndex() const {
  return IDLParser::RuleArray;
}


antlrcpp::Any IDLParser::ArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IDLVisitor*>(visitor))
    return parserVisitor->visitArray(this);
  else
    return visitor->visitChildren(this);
}

IDLParser::ArrayContext* IDLParser::array() {
  ArrayContext *_localctx = _tracker.createInstance<ArrayContext>(_ctx, getState());
  enterRule(_localctx, 10, IDLParser::RuleArray);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(33);
    match(IDLParser::LeftBracket);
    setState(34);
    statement();
    setState(35);
    match(IDLParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> IDLParser::_decisionToDFA;
atn::PredictionContextCache IDLParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN IDLParser::_atn;
std::vector<uint16_t> IDLParser::_serializedATN;

std::vector<std::string> IDLParser::_ruleNames = {
  "program", "statement", "pod", "object", "field", "array"
};

std::vector<std::string> IDLParser::_literalNames = {
  "", "", "'bool'", "'int'", "'float'", "'false'", "'string'", "'['", "']'", 
  "'{'", "'}'", "'true'", "','", "':'"
};

std::vector<std::string> IDLParser::_symbolicNames = {
  "", "BooleanLiteral", "Bool", "Int", "Float", "False_", "String", "LeftBracket", 
  "RightBracket", "LeftBrace", "RightBrace", "True_", "Comma", "Colon", 
  "Identifier", "Whitespace", "Newline"
};

dfa::Vocabulary IDLParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> IDLParser::_tokenNames;

IDLParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x12, 0x28, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x14, 0xa, 0x3, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x1b, 0xa, 
    0x5, 0xc, 0x5, 0xe, 0x5, 0x1e, 0xb, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x2, 0x2, 
    0x8, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0x2, 0x3, 0x4, 0x2, 0x4, 0x6, 0x8, 
    0x8, 0x2, 0x24, 0x2, 0xe, 0x3, 0x2, 0x2, 0x2, 0x4, 0x13, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0x15, 0x3, 0x2, 0x2, 0x2, 0x8, 0x17, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x1f, 0x3, 0x2, 0x2, 0x2, 0xc, 0x23, 0x3, 0x2, 0x2, 0x2, 0xe, 0xf, 0x5, 
    0x4, 0x3, 0x2, 0xf, 0x3, 0x3, 0x2, 0x2, 0x2, 0x10, 0x14, 0x5, 0x6, 0x4, 
    0x2, 0x11, 0x14, 0x5, 0x8, 0x5, 0x2, 0x12, 0x14, 0x5, 0xc, 0x7, 0x2, 
    0x13, 0x10, 0x3, 0x2, 0x2, 0x2, 0x13, 0x11, 0x3, 0x2, 0x2, 0x2, 0x13, 
    0x12, 0x3, 0x2, 0x2, 0x2, 0x14, 0x5, 0x3, 0x2, 0x2, 0x2, 0x15, 0x16, 
    0x9, 0x2, 0x2, 0x2, 0x16, 0x7, 0x3, 0x2, 0x2, 0x2, 0x17, 0x1c, 0x5, 
    0xa, 0x6, 0x2, 0x18, 0x19, 0x7, 0xe, 0x2, 0x2, 0x19, 0x1b, 0x5, 0xa, 
    0x6, 0x2, 0x1a, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x1e, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x3, 0x2, 0x2, 0x2, 
    0x1d, 0x9, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1f, 
    0x20, 0x7, 0x10, 0x2, 0x2, 0x20, 0x21, 0x7, 0xf, 0x2, 0x2, 0x21, 0x22, 
    0x5, 0x4, 0x3, 0x2, 0x22, 0xb, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x7, 
    0x9, 0x2, 0x2, 0x24, 0x25, 0x5, 0x4, 0x3, 0x2, 0x25, 0x26, 0x7, 0xa, 
    0x2, 0x2, 0x26, 0xd, 0x3, 0x2, 0x2, 0x2, 0x4, 0x13, 0x1c, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

IDLParser::Initializer IDLParser::_init;
