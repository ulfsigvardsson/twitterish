public class Register implements Steppable {
    private boolean open;
    private Queue queue;

    public Register() {
        this.open = false;
        this.queue = new Queue();
    }

    public void open(){
        this.open = true;
    }

    public void close() {
        this.open = false;
    }

    public boolean isOpen() {
        return this.open;
    }

    public void  step() {
        if(this.hasCustomers()) {
            Customer c = this.queue.first();
            c.serve(); 
        }
    } 

    public boolean hasCustomers() {
        return this.queue.getLength() > 0;
    }

    public boolean currentCustomerIsDone() {
        if(this.hasCustomers()) {
            return this.queue.first().isDone();
        }
        else {
            return false;
        }
    }

    public void addToQueue(Customer c) {
        this.queue.enqueue(c);
    }

    public Customer removeCurrentCustomer() {
        return this.queue.dequeue();
    }

    public Customer getCurrentCustomer() {
        return this.queue.first();
    }

    public int getQueueLength() {
        return this.queue.getLength();
    }

    public String toString() {
        if (this.isOpen()) {
            return this.queue.toString();
        }
        else {
            return "x [ ]";
        }
    }

}
