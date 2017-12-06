import java.io.IOException;
import java.util.HashMap;
import symbolic.Parser;
import exceptions.*;
import expressions.*;
import expressions.unary.*;
import expressions.atom.*;
import expressions.command.*;

class ParserDriver {

  public static HashMap<String, SymbolicExpression> variables() {
    HashMap<String,SymbolicExpression> variables = new HashMap<String,SymbolicExpression>();
    variables.put("ans", new Constant(0));

    return variables;
  }

  public static void main(String[] args) {
    System.out.print("\033[2J\033[;H");
    System.out.println("Welcome to the Symbolic Calculator!");

    if (args.length > 0) {
      ParserDriver.didStartWithCommandLineArgument(args);
    } else {
      ParserDriver.didStartInInteractiveMode();
    }
  }

  public static void didStartWithCommandLineArgument(String[] args) {
    HashMap<String,SymbolicExpression> variables = ParserDriver.variables();

    for (String arg: args) {
      Parser parser = new Parser(arg);
      ParserDriver.run(parser, variables);
    }
  }

  public static void didStartInInteractiveMode() {
    HashMap<String,SymbolicExpression> variables = ParserDriver.variables();
    Parser parser = new Parser();

    while (ParserDriver.run(parser, variables));
  }

  public static boolean run(Parser parser, HashMap<String,SymbolicExpression> variables) {
    try {
      System.out.print("? ");
      SymbolicExpression expression = parser.start();

      if (expression == Quit.getInstance()) {
        System.out.println("Exiting program...");
        return false;
      } else if (expression == Clear.getInstance()) {
        System.out.println("Clearing variables...");
        variables = ParserDriver.variables();
      } else {
        System.out.println(expression.eval(variables));
      }

    } catch(SyntaxErrorException e) {
      System.out.print("Syntax Error: ");
      System.out.println(e.getMessage());
      parser.clear();
    } catch(IOException e) {
      System.err.println("IO Exception!");
    }

    return true;
  }

}
