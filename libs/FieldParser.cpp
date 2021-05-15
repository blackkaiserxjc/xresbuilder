
// Generated from Field.g4 by ANTLR 4.9.1


#include "FieldVisitor.h"

#include "FieldParser.h"


using namespace antlrcpp;
using namespace antlr4;

FieldParser::FieldParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

FieldParser::~FieldParser() {
  delete _interpreter;
}

std::string FieldParser::getGrammarFileName() const {
  return "Field.g4";
}

const std::vector<std::string>& FieldParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& FieldParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgContext ------------------------------------------------------------------

FieldParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

FieldParser::StatementContext* FieldParser::ProgContext::statement() {
  return getRuleContext<FieldParser::StatementContext>(0);
}


size_t FieldParser::ProgContext::getRuleIndex() const {
  return FieldParser::RuleProg;
}


antlrcpp::Any FieldParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FieldVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

FieldParser::ProgContext* FieldParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, FieldParser::RuleProg);

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

FieldParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

FieldParser::PodContext* FieldParser::StatementContext::pod() {
  return getRuleContext<FieldParser::PodContext>(0);
}

FieldParser::ObjectContext* FieldParser::StatementContext::object() {
  return getRuleContext<FieldParser::ObjectContext>(0);
}

FieldParser::ArrayContext* FieldParser::StatementContext::array() {
  return getRuleContext<FieldParser::ArrayContext>(0);
}


size_t FieldParser::StatementContext::getRuleIndex() const {
  return FieldParser::RuleStatement;
}


antlrcpp::Any FieldParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FieldVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

FieldParser::StatementContext* FieldParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, FieldParser::RuleStatement);

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
      case FieldParser::Bool:
      case FieldParser::Int:
      case FieldParser::Float:
      case FieldParser::String: {
        enterOuterAlt(_localctx, 1);
        setState(14);
        pod();
        break;
      }

      case FieldParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(15);
        object();
        break;
      }

      case FieldParser::LeftBracket: {
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

FieldParser::PodContext::PodContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FieldParser::PodContext::Bool() {
  return getToken(FieldParser::Bool, 0);
}

tree::TerminalNode* FieldParser::PodContext::Int() {
  return getToken(FieldParser::Int, 0);
}

tree::TerminalNode* FieldParser::PodContext::Float() {
  return getToken(FieldParser::Float, 0);
}

tree::TerminalNode* FieldParser::PodContext::String() {
  return getToken(FieldParser::String, 0);
}


size_t FieldParser::PodContext::getRuleIndex() const {
  return FieldParser::RulePod;
}


antlrcpp::Any FieldParser::PodContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FieldVisitor*>(visitor))
    return parserVisitor->visitPod(this);
  else
    return visitor->visitChildren(this);
}

FieldParser::PodContext* FieldParser::pod() {
  PodContext *_localctx = _tracker.createInstance<PodContext>(_ctx, getState());
  enterRule(_localctx, 4, FieldParser::RulePod);
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
      ((1ULL << _la) & ((1ULL << FieldParser::Bool)
      | (1ULL << FieldParser::Int)
      | (1ULL << FieldParser::Float)
      | (1ULL << FieldParser::String))) != 0))) {
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

FieldParser::ObjectContext::ObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<FieldParser::FieldContext *> FieldParser::ObjectContext::field() {
  return getRuleContexts<FieldParser::FieldContext>();
}

FieldParser::FieldContext* FieldParser::ObjectContext::field(size_t i) {
  return getRuleContext<FieldParser::FieldContext>(i);
}

std::vector<tree::TerminalNode *> FieldParser::ObjectContext::Comma() {
  return getTokens(FieldParser::Comma);
}

tree::TerminalNode* FieldParser::ObjectContext::Comma(size_t i) {
  return getToken(FieldParser::Comma, i);
}


size_t FieldParser::ObjectContext::getRuleIndex() const {
  return FieldParser::RuleObject;
}


antlrcpp::Any FieldParser::ObjectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FieldVisitor*>(visitor))
    return parserVisitor->visitObject(this);
  else
    return visitor->visitChildren(this);
}

FieldParser::ObjectContext* FieldParser::object() {
  ObjectContext *_localctx = _tracker.createInstance<ObjectContext>(_ctx, getState());
  enterRule(_localctx, 6, FieldParser::RuleObject);

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
        match(FieldParser::Comma);
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

FieldParser::FieldContext::FieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FieldParser::FieldContext::Identifier() {
  return getToken(FieldParser::Identifier, 0);
}

tree::TerminalNode* FieldParser::FieldContext::Colon() {
  return getToken(FieldParser::Colon, 0);
}

FieldParser::StatementContext* FieldParser::FieldContext::statement() {
  return getRuleContext<FieldParser::StatementContext>(0);
}


size_t FieldParser::FieldContext::getRuleIndex() const {
  return FieldParser::RuleField;
}


antlrcpp::Any FieldParser::FieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FieldVisitor*>(visitor))
    return parserVisitor->visitField(this);
  else
    return visitor->visitChildren(this);
}

FieldParser::FieldContext* FieldParser::field() {
  FieldContext *_localctx = _tracker.createInstance<FieldContext>(_ctx, getState());
  enterRule(_localctx, 8, FieldParser::RuleField);

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
    match(FieldParser::Identifier);
    setState(30);
    match(FieldParser::Colon);
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

FieldParser::ArrayContext::ArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FieldParser::ArrayContext::LeftBracket() {
  return getToken(FieldParser::LeftBracket, 0);
}

FieldParser::StatementContext* FieldParser::ArrayContext::statement() {
  return getRuleContext<FieldParser::StatementContext>(0);
}

tree::TerminalNode* FieldParser::ArrayContext::RightBracket() {
  return getToken(FieldParser::RightBracket, 0);
}


size_t FieldParser::ArrayContext::getRuleIndex() const {
  return FieldParser::RuleArray;
}


antlrcpp::Any FieldParser::ArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FieldVisitor*>(visitor))
    return parserVisitor->visitArray(this);
  else
    return visitor->visitChildren(this);
}

FieldParser::ArrayContext* FieldParser::array() {
  ArrayContext *_localctx = _tracker.createInstance<ArrayContext>(_ctx, getState());
  enterRule(_localctx, 10, FieldParser::RuleArray);

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
    match(FieldParser::LeftBracket);
    setState(34);
    statement();
    setState(35);
    match(FieldParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> FieldParser::_decisionToDFA;
atn::PredictionContextCache FieldParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN FieldParser::_atn;
std::vector<uint16_t> FieldParser::_serializedATN;

std::vector<std::string> FieldParser::_ruleNames = {
  "prog", "statement", "pod", "object", "field", "array"
};

std::vector<std::string> FieldParser::_literalNames = {
  "", "", "'bool'", "'int'", "'float'", "'false'", "'string'", "'['", "']'", 
  "'{'", "'}'", "'true'", "','", "':'"
};

std::vector<std::string> FieldParser::_symbolicNames = {
  "", "BooleanLiteral", "Bool", "Int", "Float", "False_", "String", "LeftBracket", 
  "RightBracket", "LeftBrace", "RightBrace", "True_", "Comma", "Colon", 
  "Identifier", "Whitespace", "Newline"
};

dfa::Vocabulary FieldParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> FieldParser::_tokenNames;

FieldParser::Initializer::Initializer() {
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

FieldParser::Initializer FieldParser::_init;
