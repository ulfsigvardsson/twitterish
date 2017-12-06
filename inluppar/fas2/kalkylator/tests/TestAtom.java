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

public class TestAtom {
    
    HashMap<String,SymbolicExpression> variables;
    static int count;
    static String name = "Atom";
   
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
    public void testConstant() {
        Parser parser1 = new Parser("2"); 
        
        try {
            SymbolicExpression e = parser1.start().eval(this.variables);
            SymbolicExpression r = new Constant(2);
            assertEquals(r.getValue(), e.getValue(), 0);

        } catch (Exception e) {
            System.out.println(e); 
        }
    }

    @Test
    public void testVariable() {
        Parser parser1 = new Parser("a"); 
        
        try {
            SymbolicExpression e = parser1.start().eval(this.variables);
            SymbolicExpression r = new Variable("a").eval(this.variables);
            assertEquals(r.getValue(), e.getValue(), 0);
            
        } catch (Exception e) {
            System.out.println(e);
        
        }
    }
}
