package expressions.command;
import expressions.SymbolicExpression;
import expressions.atom.Constant;
import java.util.HashMap;

public class Ans extends Command {

  private SymbolicExpression ans;

  public Ans() {
    this.name = "ans";
    this.ans = null;
  }

  public String getName() {
    return this.name;
  }

  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    this.ans = variables.get(this.getName());

    if (this.ans != null) {
      return this.ans;
    }

    return new Constant(0);
  }
  /**
   * Returns the string representation of Ans.
   *
   * This will be the last evaluated expression, or 0 if none.
   *
   * @return The last evaluated expression.
   */
  public String toString() {
    return this.ans.toString();
  }

}
