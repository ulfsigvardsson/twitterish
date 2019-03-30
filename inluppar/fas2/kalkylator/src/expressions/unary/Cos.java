package expressions.unary;
import java.util.HashMap;
import expressions.SymbolicExpression;
import symbolic.Symbolic;

public class Cos extends Unary {

  public Cos(SymbolicExpression argument) {
    super(argument);
    this.name = "Cos";
  }

  public String getName() {
    return this.name;
  }

  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    SymbolicExpression result = Symbolic.cos(this.argument.eval(variables));
    variables.put("ans", result);
    
    return result;
  }

}
