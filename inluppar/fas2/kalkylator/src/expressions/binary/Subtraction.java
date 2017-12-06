package expressions.binary;
import java.util.HashMap;
import expressions.SymbolicExpression;
import symbolic.Symbolic;

public class Subtraction extends Binary {

  private final int priority = 1;

  public Subtraction(SymbolicExpression left, SymbolicExpression right) {
    super(left, right);
    this.name = "-";
  }

  public String getName() {
    return this.name;
  }

  public int priority() {
    return this.priority;
  }

  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    SymbolicExpression result = Symbolic.sub(this.left.eval(variables), this.right.eval(variables));
    variables.put("ans", result);

    return result;
  }

}
