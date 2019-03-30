package expressions.unary;
import java.util.HashMap;
import expressions.SymbolicExpression;
import symbolic.Symbolic;

public class Log extends Unary {

  public Log(SymbolicExpression argument) {
    super(argument);
    this.name = "Log";
  }

  public String getName() {
    return this.name;
  }

  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    SymbolicExpression result = Symbolic.log(this.argument.eval(variables));
    variables.put("ans", result);

    return result;
  }

}
