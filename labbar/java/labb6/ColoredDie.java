import java.util.Random;

public class ColoredDie extends Die {
    private String color;

    public ColoredDie() {
        super();
        Random random = new Random();
        int r = random.nextInt(3); 
        
        switch (r) {
        case 0:
            {
                this.color = "Red";
            }
        case 1:
            {
                this.color = "Blue";
            }
        case 2:
            {
                this.color = "Green";
            }
        }

    }

    public ColoredDie(String color) {
        super();
        this.color = color;
    }

    public ColoredDie(int numberOfSides, String color) {
        super(numberOfSides);
        this.color = color;
    }

    public String color() {
        return this.color;
    }
}
