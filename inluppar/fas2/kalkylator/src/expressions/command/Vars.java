package expressions.command;
import expressions.SymbolicExpression;
import java.util.HashMap;
import java.util.Iterator;

public class Vars extends Command {

  String vars;

  public Vars() {
    this.name = "Vars";
    this.vars = "";
  }

  public String getName() {
    return this.name;
  }

  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    Iterator<HashMap.Entry<String, SymbolicExpression>> iterator = variables.entrySet().iterator();

    while (iterator.hasNext()) {
      HashMap.Entry<String, SymbolicExpression> entry = iterator.next();
      String key = entry.getKey();
      SymbolicExpression value = entry.getValue();

      this.vars += key + " = ";
      this.vars += (value != null)      ? value : "NaN";
      this.vars += (iterator.hasNext()) ? ", "  : "";

    }

    return this;
  }

  public String toString() {
    return "{ " + this.vars + " }";
  }

}
