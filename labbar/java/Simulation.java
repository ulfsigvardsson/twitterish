import java.util.Random;

public class Simulation {
    private Store store;
    private int time;
    private int intensity;
    private int maxGroceries;
    private int thresholdForNewRegister;
    private int numberOfCustomersServed;
    private int maxWaitTime;
    private int totalWaitingTime;
    private int averageWaitingTime;

    public Simulation(final int numberOfRegisters, final int intensity, final int maxGroceries, final int thresholdForNewRegister) {
        this.store = new Store(numberOfRegisters);
        this.time = 0;
        this.intensity = intensity;
        this.maxGroceries = maxGroceries;
        this.thresholdForNewRegister = thresholdForNewRegister;
        this.totalWaitingTime = 0;
        this.averageWaitingTime = 0;
    }

    void step() {
        Random rand = new Random();
        
        if(rand.nextInt(100) < this.intensity) {
            Customer c;
            int newGroceries = rand.nextInt(maxGroceries);
            if(rand.nextInt(10) > 8) {
                c = new Senior(this.time, newGroceries);
                
            }
            else {
                c = new Customer(this.time, newGroceries);
            }
            this.store.newCustomer(c);                
        }

        if(queuesTooLong()) {
            this.store.openNewRegister();
        }
        
        this.time++;
        this.store.step();

        Queue done = this.store.getDoneCustomers();
        this.numberOfCustomersServed += done.getLength();
        this.totalWaitingTime += done.waitTimeQueue(this.time);
        setAverageWaitingTime();
        
    }

    private void setAverageWaitingTime() {
        try {
            this.averageWaitingTime = this.totalWaitingTime/this.numberOfCustomersServed;
        }
        catch(ArithmeticException e) {
            this.averageWaitingTime = this.totalWaitingTime;
        }
    
    
    }
    protected boolean queuesTooLong() {
        return this.store.getAverageQueueLength() > this.thresholdForNewRegister;
    }

    public int getTime() {
        return this.time;
    }

    public String toString() {
        return this.store.toString() +
            "Number of customers served: " + this.numberOfCustomersServed +
            "\nAverage waiting time: " + this.averageWaitingTime;
    }

}
