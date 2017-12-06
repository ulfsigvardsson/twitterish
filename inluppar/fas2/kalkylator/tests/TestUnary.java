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

public class TestUnary {

    HashMap<String,SymbolicExpression> variables;
    static int count;
    static String name = "Unary";
   
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
    public void testCos() {
        Parser parser1 = new Parser("Cos(3)"); 
        
        try {
            SymbolicExpression e = parser1.start().eval(this.variables);
            SymbolicExpression r = new Constant(Math.cos(3));
            assertEquals(r.getValue(), e.getValue(), 0);
            
        } catch (Exception e) {
            System.out.println(e);
        
        }
    }

    @Test
    public void testSin() {
        Parser parser1 = new Parser("Sin(3)"); 
        Parser parser2 = new Parser("Sin(2*Sin(1))");         
        try {
            SymbolicExpression e1 = parser1.start().eval(this.variables);
            SymbolicExpression r1 = new Constant(Math.sin(3));
            assertEquals(r1.getValue(), e1.getValue(), 0);

            SymbolicExpression e2 = parser2.start().eval(this.variables);
            SymbolicExpression r2 = new Constant(Math.sin(2*Math.sin(1)));
            assertEquals(r2.getValue(), e2.getValue(), 0);
            
        } catch (Exception e) {
            System.out.println(e);
        
        }
    }

    @Test
    public void testNegation() {
        Parser parser = new Parser("-1"); 
        
        try {
            SymbolicExpression e = parser.start().eval(this.variables);
            SymbolicExpression r = new Negation(new Constant(1)).eval(this.variables);
            assertEquals(r.getValue(), e.getValue(), 0);
            
        } catch (Exception e) {
            System.out.println(e);        
        }
    }

    @Test
    public void testLog() {
        Parser parser = new Parser("Log(2)"); 
        
        try {
            SymbolicExpression e = parser.start().eval(this.variables);
            SymbolicExpression r = new Log(new Constant(2)).eval(this.variables);
            assertEquals(r.getValue(), e.getValue(), 0);
            
        } catch (Exception e) {
            System.out.println(e);        
        }    
    }

    @Test
    public void testExp() {
        Parser parser = new Parser("Exp(2)"); 
        
        try {
            SymbolicExpression e = parser.start().eval(this.variables);
            SymbolicExpression r = new Exp(new Constant(2)).eval(this.variables);
            assertEquals(r.getValue(), e.getValue(), 0);
            
        } catch (Exception e) {
            System.out.println(e);        
        }    
    }
}
