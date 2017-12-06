package expressions.binary;
import java.util.HashMap;
import expressions.SymbolicExpression;

public abstract class Binary extends SymbolicExpression {

  protected SymbolicExpression left;
  protected SymbolicExpression right;

  public Binary(SymbolicExpression left, SymbolicExpression right) {
    this.left = left;
    this.right = right;
  }
  /**
   * Returns the string representation of the binary expression.
   *
   * This method will put paranthesis when needed. For example, the expression
   * (5*a)+5 will be converted to 5*a+5 while (5+a)+5 will keep the parenthesis.
   *
   * @return The string representation of the binary expression.
   */
  public String toString() {

    String leftArgument  = (this.priority() > this.left.priority() && !this.left.isAtomic()) ? "(" + this.left + ")" : this.left.toString();
    String rightArgument = (this.priority() > this.right.priority() && !this.right.isAtomic()) ? "(" + this.right + ")" : this.right.toString();

    String result = leftArgument + this.getName() + rightArgument;

    return result;
  }

}
