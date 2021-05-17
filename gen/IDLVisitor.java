// Generated from /home/alien/code/cpp/project/xresloader/src/core/IDL.g4 by ANTLR 4.9.1
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link IDLParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface IDLVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link IDLParser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(IDLParser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStatement(IDLParser.StatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#pod}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPod(IDLParser.PodContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#object}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitObject(IDLParser.ObjectContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#field}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitField(IDLParser.FieldContext ctx);
	/**
	 * Visit a parse tree produced by {@link IDLParser#array}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArray(IDLParser.ArrayContext ctx);
}