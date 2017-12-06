package expressions.atom;
import java.util.HashMap;
import expressions.SymbolicExpression;
import symbolic.Symbolic;

public class Variable extends Atom {

  private SymbolicExpression expression;
  private String identifier;

  public Variable(String identifier) {
    this.name = identifier;
  }
  public String getName() {
    return this.name;
  }

  // public void setExpression(SymbolicExpression value) {
  //   this.expression = value;
  // }
  //
  // public SymbolicExpression getExpression() {
  //   return this.expression;
  // }
  /**
   * Evaluates the expression as much as possible.
   *
   * If a variable has been assigned a value, that value will be returned, otherwise
   * the variable will be returned.
   *
   * @param  HashMap<String,SymbolicExpression> variables     A list of variables.
   * @return The value of the variable.
   */
  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    if (variables.containsKey(this.name)) {
      SymbolicExpression expr = variables.get(this.name);

      if (expr != null) {
        return expr;
      }

      return this;
    }

    variables.put(this.name, this.expression);
    return this;
  }

  public String toString() {
    return this.getName();
  }

}
