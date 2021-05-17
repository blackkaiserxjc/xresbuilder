// Generated from /home/alien/code/cpp/project/xresloader/src/core/IDL.g4 by ANTLR 4.9.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class IDLParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.9.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		BooleanLiteral=1, Bool=2, Int=3, Float=4, False_=5, String=6, LeftBracket=7, 
		RightBracket=8, LeftBrace=9, RightBrace=10, True_=11, Comma=12, Colon=13, 
		Identifier=14, Whitespace=15, Newline=16;
	public static final int
		RULE_program = 0, RULE_statement = 1, RULE_pod = 2, RULE_object = 3, RULE_field = 4, 
		RULE_array = 5;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "statement", "pod", "object", "field", "array"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, "'bool'", "'int'", "'float'", "'false'", "'string'", "'['", 
			"']'", "'{'", "'}'", "'true'", "','", "':'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "BooleanLiteral", "Bool", "Int", "Float", "False_", "String", "LeftBracket", 
			"RightBracket", "LeftBrace", "RightBrace", "True_", "Comma", "Colon", 
			"Identifier", "Whitespace", "Newline"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "IDL.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public IDLParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class ProgramContext extends ParserRuleContext {
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLListener ) ((IDLListener)listener).enterProgram(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLListener ) ((IDLListener)listener).exitProgram(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLVisitor ) return ((IDLVisitor<? extends T>)visitor).visitProgram(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(12);
			statement();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StatementContext extends ParserRuleContext {
		public PodContext pod() {
			return getRuleContext(PodContext.class,0);
		}
		public ObjectContext object() {
			return getRuleContext(ObjectContext.class,0);
		}
		public ArrayContext array() {
			return getRuleContext(ArrayContext.class,0);
		}
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLListener ) ((IDLListener)listener).enterStatement(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLListener ) ((IDLListener)listener).exitStatement(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLVisitor ) return ((IDLVisitor<? extends T>)visitor).visitStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_statement);
		try {
			setState(17);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case Bool:
			case Int:
			case Float:
			case String:
				enterOuterAlt(_localctx, 1);
				{
				setState(14);
				pod();
				}
				break;
			case Identifier:
				enterOuterAlt(_localctx, 2);
				{
				setState(15);
				object();
				}
				break;
			case LeftBracket:
				enterOuterAlt(_localctx, 3);
				{
				setState(16);
				array();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PodContext extends ParserRuleContext {
		public TerminalNode Bool() { return getToken(IDLParser.Bool, 0); }
		public TerminalNode Int() { return getToken(IDLParser.Int, 0); }
		public TerminalNode Float() { return getToken(IDLParser.Float, 0); }
		public TerminalNode String() { return getToken(IDLParser.String, 0); }
		public PodContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pod; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLListener ) ((IDLListener)listener).enterPod(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLListener ) ((IDLListener)listener).exitPod(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLVisitor ) return ((IDLVisitor<? extends T>)visitor).visitPod(this);
			else return visitor.visitChildren(this);
		}
	}

	public final PodContext pod() throws RecognitionException {
		PodContext _localctx = new PodContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_pod);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(19);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << Bool) | (1L << Int) | (1L << Float) | (1L << String))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ObjectContext extends ParserRuleContext {
		public List<FieldContext> field() {
			return getRuleContexts(FieldContext.class);
		}
		public FieldContext field(int i) {
			return getRuleContext(FieldContext.class,i);
		}
		public List<TerminalNode> Comma() { return getTokens(IDLParser.Comma); }
		public TerminalNode Comma(int i) {
			return getToken(IDLParser.Comma, i);
		}
		public ObjectContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_object; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLListener ) ((IDLListener)listener).enterObject(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLListener ) ((IDLListener)listener).exitObject(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLVisitor ) return ((IDLVisitor<? extends T>)visitor).visitObject(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ObjectContext object() throws RecognitionException {
		ObjectContext _localctx = new ObjectContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_object);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(21);
			field();
			setState(26);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,1,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(22);
					match(Comma);
					setState(23);
					field();
					}
					} 
				}
				setState(28);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,1,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FieldContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(IDLParser.Identifier, 0); }
		public TerminalNode Colon() { return getToken(IDLParser.Colon, 0); }
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public FieldContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_field; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLListener ) ((IDLListener)listener).enterField(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLListener ) ((IDLListener)listener).exitField(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLVisitor ) return ((IDLVisitor<? extends T>)visitor).visitField(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FieldContext field() throws RecognitionException {
		FieldContext _localctx = new FieldContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_field);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(29);
			match(Identifier);
			setState(30);
			match(Colon);
			setState(31);
			statement();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ArrayContext extends ParserRuleContext {
		public TerminalNode LeftBracket() { return getToken(IDLParser.LeftBracket, 0); }
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public TerminalNode RightBracket() { return getToken(IDLParser.RightBracket, 0); }
		public ArrayContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_array; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof IDLListener ) ((IDLListener)listener).enterArray(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof IDLListener ) ((IDLListener)listener).exitArray(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof IDLVisitor ) return ((IDLVisitor<? extends T>)visitor).visitArray(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ArrayContext array() throws RecognitionException {
		ArrayContext _localctx = new ArrayContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_array);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(33);
			match(LeftBracket);
			setState(34);
			statement();
			setState(35);
			match(RightBracket);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\22(\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\3\2\3\2\3\3\3\3\3\3\5\3\24\n\3\3\4"+
		"\3\4\3\5\3\5\3\5\7\5\33\n\5\f\5\16\5\36\13\5\3\6\3\6\3\6\3\6\3\7\3\7\3"+
		"\7\3\7\3\7\2\2\b\2\4\6\b\n\f\2\3\4\2\4\6\b\b\2$\2\16\3\2\2\2\4\23\3\2"+
		"\2\2\6\25\3\2\2\2\b\27\3\2\2\2\n\37\3\2\2\2\f#\3\2\2\2\16\17\5\4\3\2\17"+
		"\3\3\2\2\2\20\24\5\6\4\2\21\24\5\b\5\2\22\24\5\f\7\2\23\20\3\2\2\2\23"+
		"\21\3\2\2\2\23\22\3\2\2\2\24\5\3\2\2\2\25\26\t\2\2\2\26\7\3\2\2\2\27\34"+
		"\5\n\6\2\30\31\7\16\2\2\31\33\5\n\6\2\32\30\3\2\2\2\33\36\3\2\2\2\34\32"+
		"\3\2\2\2\34\35\3\2\2\2\35\t\3\2\2\2\36\34\3\2\2\2\37 \7\20\2\2 !\7\17"+
		"\2\2!\"\5\4\3\2\"\13\3\2\2\2#$\7\t\2\2$%\5\4\3\2%&\7\n\2\2&\r\3\2\2\2"+
		"\4\23\34";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}