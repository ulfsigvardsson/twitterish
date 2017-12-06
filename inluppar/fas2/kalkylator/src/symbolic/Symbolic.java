package symbolic;

import expressions.*;
import expressions.atom.*;
import expressions.binary.*;
import expressions.command.*;
import expressions.unary.*;

/**
 * @class The Symbolic class consists of static methods evaluating different symbolic expressions.
 */
public class Symbolic {

    /**
     * Calculates, if possible, the sin of a symbolic expression.
     * @param arg The symbolic expression for wich to calculate the sin.
     * @return  If possible, the sin of arg wrapped in an instance of Constant.
     * Otherwise an instance of Sin with arg as argument.
     */  
    */
    public static SymbolicExpression sin(SymbolicExpression arg) {
        if (arg.isConstant()) {
            return new Constant(Math.sin(arg.getValue()));
        } else {
            return new Sin(arg);
        }
    }

    /**
     * Calculates, if possible, the cosine of a symbolic expression.
     * @param arg The symbolic expression for wich to calculate the cosine.
     * @return  If possible, the cosine of arg wrapped in an instance of Constant.
     * Otherwise an instance of Cos with arg as argument.
     */  
    public static SymbolicExpression cos(SymbolicExpression arg) {
        if (arg.isConstant()) {
            return new Constant(Math.cos(arg.getValue()));
        }

        return new Cos(arg);
    }

    /**
     * Calculates, if possible, the result of Euler's numberto the power of a symbolic expression.
     * @param arg The symbolic expression to use as the exponent.
     * @return  If possible, Euler's number raised to the power of arg, wrapped in an instance of Constant.
     * Otherwise an instance of Exp with arg as argument.
     */  
    public static SymbolicExpression exp(SymbolicExpression arg) {
        if (arg.isConstant()) {
            return new Constant(Math.exp(arg.getValue()));
        }

        return new Exp(arg);
    }

    /**
     * Calculates, if possible, the natural logarithm of a symbolic expression.
     * @param arg The symbolic expression for wich to calculate the natural logarithm.
     * @return  If possible, the natural logarithm of arg, wrapped in an instance of Constant.
     * Otherwise an instance of Log with arg as argument.
     */  
    public static SymbolicExpression log(SymbolicExpression arg) {
        if (arg.isConstant()) {
            return new Constant(Math.log(arg.getValue()));
        }

        return new Log(arg);
    }

    /**
     * Calculates, if possible, the negation of a symbolic expression.
     * @param arg The symbolic expression for wich to calculate the negation.
     * @return  If possible, the negation of arg, wrapped in an instance of Constant.
     * Otherwise an instance of Negation with arg as argument.
     */  
    public static SymbolicExpression negation(SymbolicExpression arg) {
        if (arg.isConstant()) {
            return new Constant(-(arg.getValue()));
        }

        return new Negation(arg);
    }

    /**
     * Calculates, if possible, the addition of two symbolic expressions.
     * @param left The symbolic expression to the left of the plus operand.
     * @param right The symbolic expression to the right of the plus operand.
         * @return  If possible, the sum of left and right, wrapped in an instance of Constant.
         * Otherwise an instance of Addition with left and right as arguments.
         */  
    public static SymbolicExpression add(SymbolicExpression left, SymbolicExpression right) {
        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() + right.getValue());
        }

        return new Addition(left, right);
    }

    /**
     * Calculates, if possible, the difference of two symbolic expressions.
     * @param left The symbolic expression to the left of the minus operand.
     * @param right The symbolic expression to the right of the minus operand.
     * @return  If possible, the difference of left and right, wrapped in an instance of Constant.
     * Otherwise an instance of Subtraction with left and right as arguments.
     */  
    public static SymbolicExpression sub(SymbolicExpression left, SymbolicExpression right) {
        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() - right.getValue());
        }

        return new Subtraction(left, right);
    }

    /**
     * Calculates, if possible, the product of two symbolic expressions.
     * @param left The symbolic expression to the left of the multiplication operand.
     * @param right The symbolic expression to the right of the multiplication operand.
     * @return  If possible, the product of left and right, wrapped in an instance of Constant.
     * Otherwise an instance of Multiplication with left and right as arguments.
     */  
    public static SymbolicExpression mult(SymbolicExpression left, SymbolicExpression right) {
        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() * right.getValue());
        }

        return new Multiplication(left, right);
    }

    /**
     * Calculates, if possible, the quotient of two symbolic expressions.
     * @param left The symbolic expression to the left of the division operand.
     * @param right The symbolic expression to the right of the division operand.
     * @return  If possible, the quotient of left and right, wrapped in an instance of Constant.
     * Otherwise an instance of Division with left and right as arguments.
     */  
    public static SymbolicExpression div(SymbolicExpression left, SymbolicExpression right) {
        if (left.isConstant() && right.isConstant()) {
            return new Constant(left.getValue() / right.getValue());
        }

        return new Division(left, right);
    }

}

