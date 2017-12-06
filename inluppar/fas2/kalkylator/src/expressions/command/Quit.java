package expressions.command;
import expressions.SymbolicExpression;
import java.util.HashMap;

public class Quit extends Command {

  private static final Quit instance = new Quit();
  /**
   * Returns the shared Clear instance.
   * @return The shared Clear instance.
   */
  public static Quit getInstance() {
    return Quit.instance;
  }

  public Quit() {
    this.name = "Quit";
  }

  public String getName() {
    return this.name;
  }

  public SymbolicExpression eval(HashMap<String,SymbolicExpression> variables) {
    return this;
  }


}
