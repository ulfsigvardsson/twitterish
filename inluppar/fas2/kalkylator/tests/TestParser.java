import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import org.junit.Test;
import org.junit.After;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.AfterClass;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameter;
import org.junit.runners.Parameterized.Parameters;

import java.io.IOException;
import java.util.HashMap;
import java.util.Arrays;
import java.util.Collection;

import expressions.*;
import symbolic.Parser;
import exceptions.*;
import expressions.unary.*;
import expressions.atom.*;
import expressions.command.*;

public class TestParser {
    HashMap<String,SymbolicExpression> variables;
    static int count;
    static String name = "Parser";

    @BeforeClass
    public static void beforeClass() {
        count = 0;
    }
    @Before
    public void setup() {
        this.variables = new HashMap<String,SymbolicExpression>();
    }

    @Before
    public void countUp() {
        count++;
    }

    @AfterClass
    public static void printCount() {
        System.out.println(name+":\t\t"+count+" tester körda.");
    }

    @Test
    public void testStart() {
        Parser parser = new Parser("1+1");

        try {
            SymbolicExpression e = parser.start().eval(this.variables);
            SymbolicExpression r = new Constant(1+1);

            assertEquals(r.getValue(), e.getValue(), 0);

        } catch (Exception e) {
            System.out.println(e);
        }
    }

    @Test
    public void testClear() {
        Parser parser = new Parser("1+1)");

        try {
            SymbolicExpression e = parser.start();
        } catch (SyntaxErrorException e) {
            assertTrue(parser.clear());
        } catch (IOException e) {
            System.out.println(e);
            assertTrue(false);
        }
    }

    @Test
    public void testUnexpectedParenthesis() {
        Parser parser = new Parser("1+1)");

        try {
            SymbolicExpression e = parser.start();
        } catch (SyntaxErrorException e) {
            assertEquals(e.getMessage(), "Unexpected ')'");
        } catch (IOException e) {
            System.out.println(e);
            assertTrue(false);
        }
    }

    @Test
    public void testUnexpectedToken() {
        Parser parser = new Parser("1**1+56");

        try {
            SymbolicExpression e = parser.start();
        } catch (SyntaxErrorException e) {
            assertEquals(e.getMessage(), "Unexpected '*'");
        } catch (IOException e) {
            System.out.println(e);
            assertTrue(false);
        }
    }

}
