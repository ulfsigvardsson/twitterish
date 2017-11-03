public class Simulator{

    public static void main(String[] args) throws InterruptedException{
        int steps = 100;
        if(args.length < 4) {
            System.out.println("Fel antal argument.");
            return;
        }
        try{
            int numberOfRegisters = Integer.parseInt(args[0]);
            int intensity = Integer.parseInt(args[1]);
            int maxGroceries = Integer.parseInt(args[2]);
            int threshold = Integer.parseInt(args[3]);            
        }
        catch(NumberFormatException e) {
            System.out.println("Argument was not an integer");
            return;
        }


        Simulation s = new Simulation(4, 90, 15, 3); // TODO: Add parameters!
        for(int i = 0; i < steps; i++){
            System.out.print("\033[2J\033[;H");
            s.step();
            System.out.println(s);
            Thread.sleep(500);
        }
        System.out.println("");
        System.out.println("Simulation finished!");
    }
}
