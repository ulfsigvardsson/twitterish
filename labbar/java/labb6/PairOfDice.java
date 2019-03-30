public class PairOfDice {
    private ColoredDie dieOne;
    private ColoredDie dieTwo;

    public PairOfDice() {
        dieOne = new ColoredDie("Red");
        dieTwo = new ColoredDie(); 
    }

    public int rollPair() {
        return dieOne.roll() + dieTwo.roll();
    }

    public int getDieOne() {
        return dieOne.get();
    } 

    public int getDieTwo() {
        return dieTwo.get();
    }

    public String toString() {
        return "dieOne: " + dieOne.color()+ " " + dieOne.get() + " dieTwo: " + dieTwo.color() + " " + dieTwo.get();
    }
}
