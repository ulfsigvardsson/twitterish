package expressions.unary;
import java.util.HashMap;
import expressions.SymbolicExpression;
import symbolic.Symbolic;

public class Negation extends Unary {

  public Negation(SymbolicExpression argument) {
    super(argument);
    this.name = "-";
  }

  public String getName() {
    return this.name;
  }

  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    SymbolicExpression result = Symbolic.negation(this.argument.eval(variables));
    variables.put("ans", result);

    return result;
  }

}
