
// Generated from Cell.g4 by ANTLR 4.9.1


#include "CellVisitor.h"

#include "CellParser.h"


using namespace antlrcpp;
using namespace antlr4;

CellParser::CellParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CellParser::~CellParser() {
  delete _interpreter;
}

std::string CellParser::getGrammarFileName() const {
  return "Cell.g4";
}

const std::vector<std::string>& CellParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CellParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

CellParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CellParser::StatementContext* CellParser::ProgramContext::statement() {
  return getRuleContext<CellParser::StatementContext>(0);
}


size_t CellParser::ProgramContext::getRuleIndex() const {
  return CellParser::RuleProgram;
}


antlrcpp::Any CellParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CellVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

CellParser::ProgramContext* CellParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, CellParser::RuleProgram);

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

CellParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CellParser::PodContext* CellParser::StatementContext::pod() {
  return getRuleContext<CellParser::PodContext>(0);
}

CellParser::ObjectContext* CellParser::StatementContext::object() {
  return getRuleContext<CellParser::ObjectContext>(0);
}

CellParser::ArrayContext* CellParser::StatementContext::array() {
  return getRuleContext<CellParser::ArrayContext>(0);
}


size_t CellParser::StatementContext::getRuleIndex() const {
  return CellParser::RuleStatement;
}


antlrcpp::Any CellParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CellVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

CellParser::StatementContext* CellParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, CellParser::RuleStatement);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(14);
      pod();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(15);
      object();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(16);
      array();
      break;
    }

    default:
      break;
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

CellParser::ObjectContext::ObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CellParser::FieldContext *> CellParser::ObjectContext::field() {
  return getRuleContexts<CellParser::FieldContext>();
}

CellParser::FieldContext* CellParser::ObjectContext::field(size_t i) {
  return getRuleContext<CellParser::FieldContext>(i);
}

std::vector<tree::TerminalNode *> CellParser::ObjectContext::Comma() {
  return getTokens(CellParser::Comma);
}

tree::TerminalNode* CellParser::ObjectContext::Comma(size_t i) {
  return getToken(CellParser::Comma, i);
}


size_t CellParser::ObjectContext::getRuleIndex() const {
  return CellParser::RuleObject;
}


antlrcpp::Any CellParser::ObjectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CellVisitor*>(visitor))
    return parserVisitor->visitObject(this);
  else
    return visitor->visitChildren(this);
}

CellParser::ObjectContext* CellParser::object() {
  ObjectContext *_localctx = _tracker.createInstance<ObjectContext>(_ctx, getState());
  enterRule(_localctx, 4, CellParser::RuleObject);
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
    field();
    setState(24);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CellParser::Comma) {
      setState(20);
      match(CellParser::Comma);
      setState(21);
      field();
      setState(26);
      _errHandler->sync(this);
      _la = _input->LA(1);
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

CellParser::FieldContext::FieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CellParser::PodContext* CellParser::FieldContext::pod() {
  return getRuleContext<CellParser::PodContext>(0);
}

CellParser::ArrayContext* CellParser::FieldContext::array() {
  return getRuleContext<CellParser::ArrayContext>(0);
}


size_t CellParser::FieldContext::getRuleIndex() const {
  return CellParser::RuleField;
}


antlrcpp::Any CellParser::FieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CellVisitor*>(visitor))
    return parserVisitor->visitField(this);
  else
    return visitor->visitChildren(this);
}

CellParser::FieldContext* CellParser::field() {
  FieldContext *_localctx = _tracker.createInstance<FieldContext>(_ctx, getState());
  enterRule(_localctx, 6, CellParser::RuleField);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(29);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CellParser::IntegerLiteral:
      case CellParser::FloatingLiteral:
      case CellParser::StringLiteral:
      case CellParser::BooleanLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(27);
        pod();
        break;
      }

      case CellParser::LeftBracket: {
        enterOuterAlt(_localctx, 2);
        setState(28);
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

CellParser::PodContext::PodContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CellParser::PodContext::BooleanLiteral() {
  return getToken(CellParser::BooleanLiteral, 0);
}

tree::TerminalNode* CellParser::PodContext::StringLiteral() {
  return getToken(CellParser::StringLiteral, 0);
}

tree::TerminalNode* CellParser::PodContext::IntegerLiteral() {
  return getToken(CellParser::IntegerLiteral, 0);
}

tree::TerminalNode* CellParser::PodContext::FloatingLiteral() {
  return getToken(CellParser::FloatingLiteral, 0);
}


size_t CellParser::PodContext::getRuleIndex() const {
  return CellParser::RulePod;
}


antlrcpp::Any CellParser::PodContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CellVisitor*>(visitor))
    return parserVisitor->visitPod(this);
  else
    return visitor->visitChildren(this);
}

CellParser::PodContext* CellParser::pod() {
  PodContext *_localctx = _tracker.createInstance<PodContext>(_ctx, getState());
  enterRule(_localctx, 8, CellParser::RulePod);
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
    setState(31);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CellParser::IntegerLiteral)
      | (1ULL << CellParser::FloatingLiteral)
      | (1ULL << CellParser::StringLiteral)
      | (1ULL << CellParser::BooleanLiteral))) != 0))) {
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

//----------------- ArrayContext ------------------------------------------------------------------

CellParser::ArrayContext::ArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CellParser::ArrayContext::LeftBracket() {
  return getToken(CellParser::LeftBracket, 0);
}

std::vector<CellParser::StatementContext *> CellParser::ArrayContext::statement() {
  return getRuleContexts<CellParser::StatementContext>();
}

CellParser::StatementContext* CellParser::ArrayContext::statement(size_t i) {
  return getRuleContext<CellParser::StatementContext>(i);
}

tree::TerminalNode* CellParser::ArrayContext::RightBracket() {
  return getToken(CellParser::RightBracket, 0);
}

std::vector<tree::TerminalNode *> CellParser::ArrayContext::Semi() {
  return getTokens(CellParser::Semi);
}

tree::TerminalNode* CellParser::ArrayContext::Semi(size_t i) {
  return getToken(CellParser::Semi, i);
}


size_t CellParser::ArrayContext::getRuleIndex() const {
  return CellParser::RuleArray;
}


antlrcpp::Any CellParser::ArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CellVisitor*>(visitor))
    return parserVisitor->visitArray(this);
  else
    return visitor->visitChildren(this);
}

CellParser::ArrayContext* CellParser::array() {
  ArrayContext *_localctx = _tracker.createInstance<ArrayContext>(_ctx, getState());
  enterRule(_localctx, 10, CellParser::RuleArray);
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
    setState(33);
    match(CellParser::LeftBracket);
    setState(34);
    statement();
    setState(39);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CellParser::Semi) {
      setState(35);
      match(CellParser::Semi);
      setState(36);
      statement();
      setState(41);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(42);
    match(CellParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> CellParser::_decisionToDFA;
atn::PredictionContextCache CellParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CellParser::_atn;
std::vector<uint16_t> CellParser::_serializedATN;

std::vector<std::string> CellParser::_ruleNames = {
  "program", "statement", "object", "field", "pod", "array"
};

std::vector<std::string> CellParser::_literalNames = {
  "", "", "", "", "", "'['", "']'", "','", "';'"
};

std::vector<std::string> CellParser::_symbolicNames = {
  "", "IntegerLiteral", "FloatingLiteral", "StringLiteral", "BooleanLiteral", 
  "LeftBracket", "RightBracket", "Comma", "Semi", "False_", "True_", "Identifier", 
  "DecimalLiteral", "OctalLiteral", "HexadecimalLiteral", "BinaryLiteral", 
  "Whitespace", "Newline"
};

dfa::Vocabulary CellParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CellParser::_tokenNames;

CellParser::Initializer::Initializer() {
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
    0x3, 0x13, 0x2f, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x14, 0xa, 0x3, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x19, 0xa, 0x4, 0xc, 0x4, 0xe, 
    0x4, 0x1c, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x20, 0xa, 0x5, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x28, 
    0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x2b, 0xb, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x2, 0x2, 0x8, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0x2, 0x3, 0x3, 0x2, 
    0x3, 0x6, 0x2, 0x2d, 0x2, 0xe, 0x3, 0x2, 0x2, 0x2, 0x4, 0x13, 0x3, 0x2, 
    0x2, 0x2, 0x6, 0x15, 0x3, 0x2, 0x2, 0x2, 0x8, 0x1f, 0x3, 0x2, 0x2, 0x2, 
    0xa, 0x21, 0x3, 0x2, 0x2, 0x2, 0xc, 0x23, 0x3, 0x2, 0x2, 0x2, 0xe, 0xf, 
    0x5, 0x4, 0x3, 0x2, 0xf, 0x3, 0x3, 0x2, 0x2, 0x2, 0x10, 0x14, 0x5, 0xa, 
    0x6, 0x2, 0x11, 0x14, 0x5, 0x6, 0x4, 0x2, 0x12, 0x14, 0x5, 0xc, 0x7, 
    0x2, 0x13, 0x10, 0x3, 0x2, 0x2, 0x2, 0x13, 0x11, 0x3, 0x2, 0x2, 0x2, 
    0x13, 0x12, 0x3, 0x2, 0x2, 0x2, 0x14, 0x5, 0x3, 0x2, 0x2, 0x2, 0x15, 
    0x1a, 0x5, 0x8, 0x5, 0x2, 0x16, 0x17, 0x7, 0x9, 0x2, 0x2, 0x17, 0x19, 
    0x5, 0x8, 0x5, 0x2, 0x18, 0x16, 0x3, 0x2, 0x2, 0x2, 0x19, 0x1c, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0x1b, 0x7, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1a, 0x3, 0x2, 0x2, 
    0x2, 0x1d, 0x20, 0x5, 0xa, 0x6, 0x2, 0x1e, 0x20, 0x5, 0xc, 0x7, 0x2, 
    0x1f, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x20, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0x21, 0x22, 0x9, 0x2, 0x2, 0x2, 0x22, 0xb, 
    0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x7, 0x7, 0x2, 0x2, 0x24, 0x29, 0x5, 
    0x4, 0x3, 0x2, 0x25, 0x26, 0x7, 0xa, 0x2, 0x2, 0x26, 0x28, 0x5, 0x4, 
    0x3, 0x2, 0x27, 0x25, 0x3, 0x2, 0x2, 0x2, 0x28, 0x2b, 0x3, 0x2, 0x2, 
    0x2, 0x29, 0x27, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x3, 0x2, 0x2, 0x2, 
    0x2a, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x29, 0x3, 0x2, 0x2, 0x2, 0x2c, 
    0x2d, 0x7, 0x8, 0x2, 0x2, 0x2d, 0xd, 0x3, 0x2, 0x2, 0x2, 0x6, 0x13, 
    0x1a, 0x1f, 0x29, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

CellParser::Initializer CellParser::_init;
