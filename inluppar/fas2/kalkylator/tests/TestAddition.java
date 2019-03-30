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
import expressions.unary.*;
import expressions.atom.*;
import expressions.command.*;

public class TestAddition {
    HashMap<String,SymbolicExpression> variables;
    static int count;
    static String name = "Addition";
    
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
    public void testAdd() {
        Parser parser1 = new Parser("Sin(3)+Cos(4)"); 
        
        try {
            SymbolicExpression e = parser1.start().eval(this.variables);
            SymbolicExpression r = new Constant(Math.sin(3)+Math.cos(4));

            assertEquals(r.getValue(), e.getValue(), 0);

        } catch (Exception e) {
            System.out.println(e);
        }
    }
    
    @Test
    public void testAddNegative() {
        Parser parser1 = new Parser("1+(-1)"); 
        Parser parser2 = new Parser("1+(-2)");
        try {
            SymbolicExpression e1 = parser1.start().eval(this.variables);
            SymbolicExpression e2 = parser2.start().eval(this.variables);

            SymbolicExpression r1 = new Constant(0);
            SymbolicExpression r2 = new Constant(-1);

            assertEquals(r1.getValue(), e1.getValue(), 0);
            assertEquals(r2.getValue(), e2.getValue(), 0);

        } catch (Exception e) {
            System.out.println(e);
        }
    }
    
    @Test
    public void testAddFromNegative() {
        Parser parser1 = new Parser("(-1)+1");
        Parser parser2 = new Parser("(-1)+2");
        try {
            SymbolicExpression e1 = parser1.start().eval(this.variables);
            SymbolicExpression e2 = parser2.start().eval(this.variables);

            SymbolicExpression r1 = new Constant(0);
            SymbolicExpression r2 = new Constant(1);

            assertEquals(r1.getValue(), e1.getValue(), 0);
            assertEquals(r2.getValue(), e2.getValue(), 0);

        } catch (Exception e) {
            System.out.println(e);
        }
    }

}
