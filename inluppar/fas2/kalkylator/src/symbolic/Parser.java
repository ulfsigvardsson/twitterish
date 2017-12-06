package symbolic;

import java.io.StreamTokenizer;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.StringReader;
import java.nio.charset.StandardCharsets;
import java.util.Locale;
import java.io.IOException;
import java.util.TreeSet;
import exceptions.*;
import expressions.*;
import expressions.atom.*;
import expressions.binary.*;
import expressions.command.*;
import expressions.unary.*;
import java.util.TreeMap;

public class Parser {
  /**
   * The stream tokenizer.
   */
  private StreamTokenizer tokenizer;
  /**
   * The symbol marking the end.
   *
   * This differs depending on the input stream.
   */
  private int endSymbol;
  /**
   * The set of functions available for the parser.
   */
  private TreeSet<String> unaries  = new TreeSet<String>();
  /**
   * The set of commands available fot the parser.
   */
  private TreeSet<String> commands = new TreeSet<String>();
  /**
   * Creates a Parser that builds an expression.
   *
   * Invoking this method will set the input stream to be the standard input stream.
   */
  public Parser() {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in, StandardCharsets.UTF_8));
    this.tokenizer = new StreamTokenizer(in);
    this.endSymbol = StreamTokenizer.TT_EOL;
    this.setUp();
  }
  /**
   * Creates a Parser that builds an expression based on the specified string.
   *
   * Invoking this method will set the input stream to be the specified string.
   *
   * @param  String inputString   The string to parse.
   */
  public Parser(String inputString) {
    BufferedReader in = new BufferedReader(new StringReader(inputString));
    this.tokenizer = new StreamTokenizer(in);
    this.endSymbol = StreamTokenizer.TT_EOF;
    this.setUp();
  }
  /**
   * Set up method.
   */
  private void setUp() {
    this.tokenizer.ordinaryChar('-');
    this.tokenizer.ordinaryChar('/');
    this.tokenizer.eolIsSignificant(true);

    this.unaries.add("cos");
    this.unaries.add("sin");
    this.unaries.add("log");
    this.unaries.add("exp");

    this.commands.add("quit");
    this.commands.add("vars");
    this.commands.add("clear");
  }
  /**
   * Clears input stream for the parser.
   */
  public boolean clear() {
    try {
      while (this.currentToken() != this.endSymbol) {
        this.consumeToken();
      }

      return true;
    } catch (IOException e) {
      System.out.println("IO Error!");
    }

    return false;
  }
  /**
   * Starts the parser and waits for input from the user.
   *
   * @return A symbolic expression built from input by the user.
   *
   * @throws IOException If an I/O error occurs.
   */
  public SymbolicExpression start() throws IOException {
    SymbolicExpression expression = null;

    while (this.consumeToken() != this.endSymbol) {
      expression = this.statement();

      if (this.currentToken() != this.endSymbol && this.currentTokenIsACommand() == false) {
        this.didGetSyntaxError();
      }
    }

    if (expression == null) {
      throw new SyntaxErrorException("Expected expression");
    }

    return expression;
  }
  /**
   * Parses a statement.
   *
   * @return A symbolic expression.
   * @throws IOException If an I/O error occurs.
   */
  public SymbolicExpression statement() throws IOException {
    if (this.currentTokenIsACommand()) {
      this.pushBack(); // Fulfix för att test av command() ska funka
      return this.command();
    }

    this.pushBack();

    return this.assignment();
  }
  /**
   * Parses a command.
   *
   * @return A symbolic expression.
   * @throws IOException If an I/O error occurs.
   */
  public SymbolicExpression command() throws IOException {
    this.consumeToken();
    String command = this.readString();

    if (command.equalsIgnoreCase("quit")) {
      return Quit.getInstance();
    } else if (command.equalsIgnoreCase("clear")) {
      return Clear.getInstance();
    } else {
      return new Vars();
    }
  }
  /**
   * Parses an assignment.
   *
   * @return A symbolic expression.
   * @throws IOException If an I/O error occurs.
   */
  public SymbolicExpression assignment() throws IOException {
    SymbolicExpression expression = this.expression();

    while (this.consumeToken() == '=') {
      this.consumeToken();
      expression = new Assignment(expression, this.identifier());
    }

    this.pushBack();

    return expression;
  }
  /**
   * Parses an expression.
   *
   * @return A symbolic expression.
   * @throws IOException If an I/O error occurs.
   */
  public SymbolicExpression expression() throws IOException {
    SymbolicExpression expression = this.term();
    int[] tokens = {'+', '-'};

    this.consumeToken();

    while (this.currentTokenIs(tokens)) {
      if (this.currentTokenIs('+')) {
        expression = new Addition(expression, this.term());
      } else {
        expression = new Subtraction(expression, this.term());
      }

      this.consumeToken();
    }

    this.pushBack();

    return expression;
  }
  /**
   * Parses a term.
   *
   * @return A symbolic expression.
   * @throws IOException If an I/O error occurs.
   */
  public SymbolicExpression term() throws IOException {
    SymbolicExpression expression = this.factor();
    int[] tokens = {'*', '/'};

    this.consumeToken();

    while (this.currentTokenIs(tokens)) {
      if (this.currentTokenIs('*')) {
        expression = new Multiplication(expression, this.factor());
      } else {
        expression = new Division(expression, this.factor());
      }

      this.consumeToken();
    }

    this.pushBack();

    return expression;
  }
  /**
   * Parses a factor.
   *
   * @return A symbolic expression.
   * @throws IOException If an I/O error occurs.
   */
  public SymbolicExpression factor() throws IOException {
    return this.primary();
  }
  /**
   * Parses a primary.
   *
   * @return A symbolic expression.
   * @throws IOException If an I/O error occurs.
   */
  public SymbolicExpression primary() throws IOException {
    SymbolicExpression expression = null;

    this.consumeToken();

    if (this.currentTokenIsNumber()) {
      expression = this.number();
    } else if (this.currentTokenIsAUnary()) {
        expression = this.unary();
    } else if (this.currentTokenIsWord()) {
        expression = this.identifier();
    } else if (this.currentTokenIs('(')) {
      expression = this.assignment();

      if (this.consumeToken() != ')') throw new SyntaxErrorException("expected ')'");

    } else {
      if (this.currentToken() == this.endSymbol) {
        this.pushBack();
      } else {
        this.didGetSyntaxError();
      }
    }

    return expression;
  }
  /**
   * Parses a unary.
   *
   * @return A symbolic expression.
   * @throws IOException If an I/O error occurs.
   */
  public SymbolicExpression unary() throws IOException {
    if (this.currentTokenIsWord()) {
      if (this.readString().equalsIgnoreCase("cos")) {
        return new Cos(this.primary());
      } else if (this.readString().equalsIgnoreCase("sin")) {
        return new Sin(this.primary());
      } else if (this.readString().equalsIgnoreCase("log")) {
        return new Log(this.primary());
      } else if (this.readString().equalsIgnoreCase("exp")) {
        return new Exp(this.primary());
      }
    } else if (this.currentTokenIs('-')) {
      return new Negation(this.primary());
    }

    throw new SyntaxErrorException("Unknown function");
  }
  /**
   * Parses a number.
   *
   * @return A symbolic expression.
   * @throws IOException If an I/O error occurs.
   */
  private SymbolicExpression number() throws IOException {
    if (this.currentTokenIsNumber()) {
      return new Constant(this.readNumber());
    }

    throw new SyntaxErrorException("Excepted a number");
  }
  /**
   * Parses an identifier.
   *
   * @return A symbolic expression.
   * @throws IOException If an I/O error occurs.
   */
  private SymbolicExpression identifier() throws IOException {
    if (this.currentTokenIsWord()) {
      return new Variable(this.readString());
    }

    throw new SyntaxErrorException("Excepted an identifier");
  }
  /**
   * Checks if the current token is a word.
   *
   * @return True if the token is a word, otherwise false.
   * @throws IOException If an I/O error occurs.
   */
  private boolean currentTokenIsWord() throws IOException {
    return this.currentToken() == StreamTokenizer.TT_WORD;
  }
  /**
   * Checks if the current token is a number.
   *
   * @return True if the token is a number, otherwise false.
   * @throws IOException If an I/O error occurs.
   */
  private boolean currentTokenIsNumber() throws IOException {
    return this.currentToken() == StreamTokenizer.TT_NUMBER;
  }
  /**
   * Checks if the current token is a word.
   *
   * @return True if the token is a word, otherwise false.
   * @throws IOException If an I/O error occurs.
   */
  private boolean currentTokenIsACommand() throws IOException {
    return (this.currentTokenIsWord() &&
    this.commands.contains(this.readString().toLowerCase(Locale.ROOT)));
  }
  /**
   * Checks if the current token is a unary operation.
   *
   * @return True if the token is a unary operation, otherwise false.
   * @throws IOException If an I/O error occurs.
   */
  private boolean currentTokenIsAUnary() throws IOException {
    return (this.currentTokenIsWord()
         && this.unaries.contains(this.readString().toLowerCase(Locale.ROOT))
         || this.currentTokenIs('-'));
  }
  /**
   * Checks if the current token is the chars specified.
   *
   * @see currentTokenIs
   *
   * @return True if the token is the specified chars, otherwise false.
   * @throws IOException If an I/O error occurs.
   */
  private boolean currentTokenIs(int[] tokens) throws IOException {
    for (int token: tokens) {
      if (this.currentTokenIs(token)) {
        return true;
      }
    }

    return false;
  }
  /**
   * Checks if the current token is the char specified.
   *
   * @return True if the token is the specified char, otherwise false.
   * @throws IOException If an I/O error occurs.
   */
  private boolean currentTokenIs(int token) throws IOException {
    return this.currentToken() == token;
  }
  /**
   * Consumes and returns a token from the stream.
   *
   * @return The token consumed.
   * @throws IOException If an I/O error occurs.
   */
  private int consumeToken() throws IOException {
    return this.tokenizer.nextToken();
  }
  /**
   * Causes the next call to consumeToken() to return the current token.
   *
   * @throws IOException If an I/O error occurs.
   */
  private void pushBack() throws IOException {
    this.tokenizer.pushBack();
  }
  /**
   * Returns the current word token, but does not go to the next token.
   *
   * @return The current word token, or null if the current token is not a word.
   * @throws IOException If an I/O error occurs.
   */
  private String readString() throws IOException {
    return this.tokenizer.sval;
  }
  /**
   * Returns the current number token, but does not go to the next token.
   *
   * @return The current number token, or null if the current token is not a number.
   * @throws IOException If an I/O error occurs.
   */
  private double readNumber() throws IOException {
    return this.tokenizer.nval;
  }
  /**
   * Returns the type of the token. If the type of the token is a character, the returned value will be that character converted to an integer.
   *
   * @return The type of the current token.
   * @throws IOException If an I/O error occurs.
   */
  private int currentToken() throws IOException {
    return this.tokenizer.ttype;
  }

  private void didGetSyntaxError() throws IOException {
    if (this.currentTokenIsWord()) {
      throw new SyntaxErrorException("Unexpected '" + this.readString() + "'");
    } else if (this.currentTokenIsNumber()) {
      throw new SyntaxErrorException("Unexpected '" + this.readNumber() + "'");
    } else {
      throw new SyntaxErrorException("Unexpected '" + String.valueOf((char)this.currentToken()) + "'");
    }
  }

}
