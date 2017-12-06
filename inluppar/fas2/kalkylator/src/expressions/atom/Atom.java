package expressions.atom;
import expressions.SymbolicExpression;
import symbolic.Symbolic;

public abstract class Atom extends SymbolicExpression {

  public boolean isAtomic() {
    return true;
  }
  /**
   * Returns the string representation of the atomic expression.
   *
   * Invoking this method on constants will return the string representation
   * of the constant, while a variable returns its identifier.
   *
   * @return The string representation of the atomic expression.
   */
  public String toString() {
    if (this.isConstant()) {
      return "" + this.getValue();
    }

    return this.getName();
  }

}
