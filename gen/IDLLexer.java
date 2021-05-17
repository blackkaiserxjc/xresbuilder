// Generated from /home/alien/code/cpp/project/xresloader/src/core/IDL.g4 by ANTLR 4.9.1
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class IDLLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.9.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		BooleanLiteral=1, Bool=2, Int=3, Float=4, False_=5, String=6, LeftBracket=7, 
		RightBracket=8, LeftBrace=9, RightBrace=10, True_=11, Comma=12, Colon=13, 
		Identifier=14, Whitespace=15, Newline=16;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"BooleanLiteral", "Bool", "Int", "Float", "False_", "String", "LeftBracket", 
			"RightBracket", "LeftBrace", "RightBrace", "True_", "Comma", "Colon", 
			"Identifier", "IdentifierNondigit", "Nondigit", "Digit", "UniversalCharacterName", 
			"HexQuad", "HexadecimalDigit", "Whitespace", "Newline"
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


	public IDLLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "IDL.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\22\u0093\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\3\2\3\2\5\2\62"+
		"\n\2\3\3\3\3\3\3\3\3\3\3\3\4\3\4\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\5\3\6\3"+
		"\6\3\6\3\6\3\6\3\6\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\b\3\b\3\t\3\t\3\n\3\n"+
		"\3\13\3\13\3\f\3\f\3\f\3\f\3\f\3\r\3\r\3\16\3\16\3\17\3\17\3\17\7\17d"+
		"\n\17\f\17\16\17g\13\17\3\20\3\20\5\20k\n\20\3\21\3\21\3\22\3\22\3\23"+
		"\3\23\3\23\3\23\3\23\3\23\3\23\3\23\3\23\3\23\5\23{\n\23\3\24\3\24\3\24"+
		"\3\24\3\24\3\25\3\25\3\26\6\26\u0085\n\26\r\26\16\26\u0086\3\26\3\26\3"+
		"\27\3\27\5\27\u008d\n\27\3\27\5\27\u0090\n\27\3\27\3\27\2\2\30\3\3\5\4"+
		"\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\2!\2"+
		"#\2%\2\'\2)\2+\21-\22\3\2\6\5\2C\\aac|\3\2\62;\5\2\62;CHch\4\2\13\13\""+
		"\"\2\u0094\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2"+
		"\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27"+
		"\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2"+
		"\3\61\3\2\2\2\5\63\3\2\2\2\78\3\2\2\2\t<\3\2\2\2\13B\3\2\2\2\rH\3\2\2"+
		"\2\17O\3\2\2\2\21Q\3\2\2\2\23S\3\2\2\2\25U\3\2\2\2\27W\3\2\2\2\31\\\3"+
		"\2\2\2\33^\3\2\2\2\35`\3\2\2\2\37j\3\2\2\2!l\3\2\2\2#n\3\2\2\2%z\3\2\2"+
		"\2\'|\3\2\2\2)\u0081\3\2\2\2+\u0084\3\2\2\2-\u008f\3\2\2\2/\62\5\13\6"+
		"\2\60\62\5\27\f\2\61/\3\2\2\2\61\60\3\2\2\2\62\4\3\2\2\2\63\64\7d\2\2"+
		"\64\65\7q\2\2\65\66\7q\2\2\66\67\7n\2\2\67\6\3\2\2\289\7k\2\29:\7p\2\2"+
		":;\7v\2\2;\b\3\2\2\2<=\7h\2\2=>\7n\2\2>?\7q\2\2?@\7c\2\2@A\7v\2\2A\n\3"+
		"\2\2\2BC\7h\2\2CD\7c\2\2DE\7n\2\2EF\7u\2\2FG\7g\2\2G\f\3\2\2\2HI\7u\2"+
		"\2IJ\7v\2\2JK\7t\2\2KL\7k\2\2LM\7p\2\2MN\7i\2\2N\16\3\2\2\2OP\7]\2\2P"+
		"\20\3\2\2\2QR\7_\2\2R\22\3\2\2\2ST\7}\2\2T\24\3\2\2\2UV\7\177\2\2V\26"+
		"\3\2\2\2WX\7v\2\2XY\7t\2\2YZ\7w\2\2Z[\7g\2\2[\30\3\2\2\2\\]\7.\2\2]\32"+
		"\3\2\2\2^_\7<\2\2_\34\3\2\2\2`e\5\37\20\2ad\5\37\20\2bd\5#\22\2ca\3\2"+
		"\2\2cb\3\2\2\2dg\3\2\2\2ec\3\2\2\2ef\3\2\2\2f\36\3\2\2\2ge\3\2\2\2hk\5"+
		"!\21\2ik\5%\23\2jh\3\2\2\2ji\3\2\2\2k \3\2\2\2lm\t\2\2\2m\"\3\2\2\2no"+
		"\t\3\2\2o$\3\2\2\2pq\7^\2\2qr\7w\2\2rs\3\2\2\2s{\5\'\24\2tu\7^\2\2uv\7"+
		"W\2\2vw\3\2\2\2wx\5\'\24\2xy\5\'\24\2y{\3\2\2\2zp\3\2\2\2zt\3\2\2\2{&"+
		"\3\2\2\2|}\5)\25\2}~\5)\25\2~\177\5)\25\2\177\u0080\5)\25\2\u0080(\3\2"+
		"\2\2\u0081\u0082\t\4\2\2\u0082*\3\2\2\2\u0083\u0085\t\5\2\2\u0084\u0083"+
		"\3\2\2\2\u0085\u0086\3\2\2\2\u0086\u0084\3\2\2\2\u0086\u0087\3\2\2\2\u0087"+
		"\u0088\3\2\2\2\u0088\u0089\b\26\2\2\u0089,\3\2\2\2\u008a\u008c\7\17\2"+
		"\2\u008b\u008d\7\f\2\2\u008c\u008b\3\2\2\2\u008c\u008d\3\2\2\2\u008d\u0090"+
		"\3\2\2\2\u008e\u0090\7\f\2\2\u008f\u008a\3\2\2\2\u008f\u008e\3\2\2\2\u0090"+
		"\u0091\3\2\2\2\u0091\u0092\b\27\2\2\u0092.\3\2\2\2\13\2\61cejz\u0086\u008c"+
		"\u008f\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}