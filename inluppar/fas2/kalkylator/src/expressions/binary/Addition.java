package expressions.binary;
import java.util.HashMap;
import expressions.SymbolicExpression;
import symbolic.Symbolic;

public class Addition extends Binary {

  private final int priority = 1;

  public Addition(SymbolicExpression left, SymbolicExpression right) {
    super(left, right);
    this.name = "+";
  }

  public String getName() {
    return this.name;
  }

  public int priority() {
    return this.priority;
  }

  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    SymbolicExpression result = Symbolic.add(this.left.eval(variables), this.right.eval(variables));
    variables.put("ans", result);

    return result;
  }

}
