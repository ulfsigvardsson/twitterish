package expressions.atom;
import java.util.HashMap;
import expressions.SymbolicExpression;
import symbolic.Symbolic;

public class Constant extends Atom {

  private double value;

  public Constant(double value) {
    this.name = "Constant";
    this.value = value;
  }

  public String getName() {
    return this.name;
  }
  /**
   * Evaluates the expression as much as possible.
   *
   * Note that constants cannot be evaluated further.
   *
   * @param  HashMap<String,SymbolicExpression> variables     A list of variables.
   * @return The constant.
   */
  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    return this;
  }

  public double getValue() {
    return this.value;
  }

  public boolean isConstant() {
    return true;
  }



}
