import java.util.Scanner;

public class Die {
    private int numberOfSides;
    private int value;

    public Die() {
        this.numberOfSides = 6;
    }

    public Die(int numberOfSides) {
        if (numberOfSides > 0) {
            this.numberOfSides = numberOfSides;            
        }
        else {
            throw new IllegalArgumentException("Illegal number of sides for die: "+numberOfSides);
        } 

    }

    public int roll() {
        this.value = (int) (Math.random() * numberOfSides) + 1;
        return this.get();
    }

    public int get() {
        return value;
    }

    public String toString() {
        return "Die(" + value + ")";
    }

    boolean equals(Die otherDie) {
        return (this.value == otherDie.value && this.numberOfSides == otherDie.numberOfSides);
    }
    
    public static void main(String [] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Number of sides: ");
        int sides = sc.nextInt();
        Die d = new Die(sides);
        System.out.println("Alea iacta est: " + d.roll());
    }
}
