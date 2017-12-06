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
import java.lang.Math;
import java.io.IOException;
import java.util.HashMap;
import java.util.Arrays;
import java.util.Collection;

import expressions.*;
import symbolic.Parser;
import exceptions.*;
import expressions.binary.*;
import expressions.unary.*;
import expressions.atom.*;
import expressions.command.*;

public class TestDivision {

    HashMap<String,SymbolicExpression> variables;
    static int count;
    static String name = "Division";
   
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
        System.out.println(name+":\t"+count+" tester körda.");
    }
    
    @Test
    public void testDivide() {
        Parser parser1 = new Parser("4/3"); 
        
        try {
            SymbolicExpression e = parser1.start().eval(this.variables);
            SymbolicExpression r = new Constant(4.0/3.0);

            assertEquals(r.getValue(), e.getValue(), 0);

        } catch (Exception e) {
            System.out.println(e);
        }
    }

    @Test
    public void testDivideDoubleNegative() {
        Parser parser1 = new Parser("-4/(-3)"); 
        
        try {
            SymbolicExpression e = parser1.start().eval(this.variables);
            SymbolicExpression r = new Constant(-4.0/-3.0);

            assertEquals(r.getValue(), e.getValue(), 0);

        } catch (Exception e) {
            System.out.println(e);
        }
    }

    @Test
    public void testDivideNegative() {
        Parser parser1 = new Parser("4/(-3)"); 
        
        try {
            SymbolicExpression e = parser1.start().eval(this.variables);
            SymbolicExpression r = new Constant(4.0/-3.0);

            assertEquals(r.getValue(), e.getValue(), 0);

        } catch (Exception e) {
            System.out.println(e);
        }
    }
    /*
      @Test
      public void testDivideByZero() {
      Parser parser1 = new Parser("4/0"); 
        
      try {
      SymbolicExpression e = parser1.start().eval(this.variables);
      SymbolicExpression r = new Constant(1/0);

      assertEquals(r.getValue(), e.getValue(), 0);

      } catch (Exception e) {
      System.out.println(e);
      }
      }
    */
    @Test
    public void testDivideZero() {
        Parser parser1 = new Parser("0/2"); 
        
        try {
            SymbolicExpression e = parser1.start().eval(this.variables);
            SymbolicExpression r = new Constant(0);

            assertEquals(r.getValue(), e.getValue(), 0);

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
