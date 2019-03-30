package expressions.unary;
import java.util.HashMap;
import expressions.SymbolicExpression;
import symbolic.Symbolic;

public class Exp extends Unary {

  public Exp(SymbolicExpression argument) {
    super(argument);
    this.name = "Exp";
  }

  public String getName() {
    return this.name;
  }

  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    SymbolicExpression result = Symbolic.exp(this.argument.eval(variables));
    variables.put("ans", result);

    return result;
  }

}
