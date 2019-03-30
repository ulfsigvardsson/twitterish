public class Customer {
    private int bornTime;
    private int groceries;
    private int waitTime;
    
    public Customer(int bornTime, int groceries) {
        this.waitTime  = 0;
        this.bornTime  = bornTime;
        this.groceries = groceries;
    }

    public void serve() {
        if(this.groceries > 0) {
            this.groceries--;
        }
    }

    public int remainingGroceries() {
        return this.groceries;
    }

    public int getWaitTime(int time) {
        return time - this.bornTime;
    }

    public boolean isDone() {
        return this.groceries == 0;
    }

    public String toString() {
        return "  ["+groceries+"]";
    }

}

class Senior extends Customer{
    private boolean skip;
    
    public Senior(int bornTime, int groceries){
        super(bornTime, groceries); 
        this.skip = true;
    }

    //Overriding
    public void serve() {
        if(this.remainingGroceries() > 0) {
            if(this.skip == false) {
                super.serve();
            }
        }
        this.skip = !this.skip; 
    }

    public String toString() {
        return "  [P"+this.remainingGroceries()+"]";
    }
}









