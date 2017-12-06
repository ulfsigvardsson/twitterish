package expressions.unary;
import expressions.SymbolicExpression;

public abstract class Unary extends SymbolicExpression {

  protected SymbolicExpression argument;
  private final int priority = 4;

  public Unary(SymbolicExpression argument) {
    this.argument = argument;
  }
  /**
   * Returns the string representation of the unary expression.
   *
   * @return The string representation of the unary expression.
   */
  public String toString() {
    return this.getName() + "(" + this.argument.toString() + ")";
  }

  public int priority() {
    return this.priority;
  }

}
