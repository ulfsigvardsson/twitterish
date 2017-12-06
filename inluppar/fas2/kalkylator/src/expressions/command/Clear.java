package expressions.command;
import expressions.SymbolicExpression;
import java.util.HashMap;

public class Clear extends Command {

  private static final Clear instance = new Clear();
  /**
   * Returns the shared Clear instance.
   * @return The shared Clear instance.
   */
  public static Clear getInstance() {
    return Clear.instance;
  }

  public Clear() {
    this.name = "Clear";
  }

  public String getName() {
    return this.name;
  }

  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    return this;
  }


}
