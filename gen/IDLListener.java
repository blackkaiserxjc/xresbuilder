// Generated from /home/alien/code/cpp/project/xresloader/src/core/IDL.g4 by ANTLR 4.9.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link IDLParser}.
 */
public interface IDLListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link IDLParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(IDLParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(IDLParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(IDLParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(IDLParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#pod}.
	 * @param ctx the parse tree
	 */
	void enterPod(IDLParser.PodContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#pod}.
	 * @param ctx the parse tree
	 */
	void exitPod(IDLParser.PodContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#object}.
	 * @param ctx the parse tree
	 */
	void enterObject(IDLParser.ObjectContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#object}.
	 * @param ctx the parse tree
	 */
	void exitObject(IDLParser.ObjectContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#field}.
	 * @param ctx the parse tree
	 */
	void enterField(IDLParser.FieldContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#field}.
	 * @param ctx the parse tree
	 */
	void exitField(IDLParser.FieldContext ctx);
	/**
	 * Enter a parse tree produced by {@link IDLParser#array}.
	 * @param ctx the parse tree
	 */
	void enterArray(IDLParser.ArrayContext ctx);
	/**
	 * Exit a parse tree produced by {@link IDLParser#array}.
	 * @param ctx the parse tree
	 */
	void exitArray(IDLParser.ArrayContext ctx);
}