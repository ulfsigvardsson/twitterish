package expressions.unary;
import java.util.HashMap;
import expressions.SymbolicExpression;
import symbolic.Symbolic;

public class Sin extends Unary {

  public Sin(SymbolicExpression argument) {
    super(argument);
    this.name = "Sin";
  }

  public String getName() {
    return this.name;
  }

  public SymbolicExpression eval(HashMap<String, SymbolicExpression> variables) {
    SymbolicExpression result = Symbolic.sin(this.argument.eval(variables));
    variables.put("ans", result);

    return result;
  }

}
