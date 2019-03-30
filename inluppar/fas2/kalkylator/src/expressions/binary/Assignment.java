package expressions.binary;
import java.util.HashMap;
import expressions.SymbolicExpression;
import symbolic.Symbolic;

public class Assignment extends Binary {

  private final int priority = 3;

  public Assignment(SymbolicExpression left, SymbolicExpression right) {
    super(left, right);
    this.name = "=";
  }

  public String getName() {
    return this.name;
  }

  public int priority() {
    return this.priority;
  }

  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    SymbolicExpression expr = this.left.eval(variables);
    variables.put(this.right.getName(), expr);

    return expr;
  }

}
