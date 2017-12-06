package expressions;
import java.util.HashMap;

public abstract class SymbolicExpression {
  /**
   * The name of the expression.
   */
  protected String name;
  /**
   * Retrieves the name of the expression.
   *
   * @return The name of the expression.
   */
  public abstract String getName();
  /**
   * Evaluates the expression as much as possible.
   *
   * @param  HashMap<String,SymbolicExpression> variables     A list of variables.
   * @return The expression evaluated.
   */
  public abstract SymbolicExpression eval(HashMap<String,SymbolicExpression> variables);
  /**
   * Returns the value of the expression.
   *
   * Note that only Constants have a value.
   *
   * @return The value of the expression.
   */
  public double getValue() {
    return 0.0;
  }
  /**
   * Returns the priority of an expression.
   *
   * @return An expressions priority.
   */
  public int priority() {
    return 0;
  }
  /**
   * Checks if the expression is a constant.
   *
   * @return True if the expression is a constant, otherwise false.
   */
  public boolean isConstant() {
    return false;
  }
  /**
   * Checks if the expression is of atomic type.
   *
   * @return True if the expression is atomic, otherwise false.
   */
  public boolean isAtomic() {
    return false;
  }

}
