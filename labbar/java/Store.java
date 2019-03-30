public class Store implements Steppable {
    private Register registers[];

    public Store(int numberOfRegisters) {
        this.registers = new Register[numberOfRegisters];

        for(int i = 0; i < numberOfRegisters; i++) {
            registers[i] = new Register();
        }
        registers[0].open();
    }
    
    public Store() {
        this(3);
    }
    
    // Returnerar snittkölängden för alla öppna kassor i affären
    public int getAverageQueueLength() {
        int total = 0;
        int openRegisters = 0;
        
        for(Register r : this.registers) {
            if(r.isOpen()) {
                total += r.getQueueLength();
                openRegisters++;
            }
        }
        return total/openRegisters;
    }

    // Placerar en ny kund i den kortaste kön
    public void newCustomer(Customer c) {
        Register register = this.getShortestQueue();
        register.addToQueue(c);
    }

    // Returnerar den öppna kassan med kortast kö
    private Register getShortestQueue() {
        Register shortest = this.registers[0];
        for(Register r : this.registers) {
            if(r.isOpen() && r.getQueueLength() < shortest.getQueueLength()) {
                shortest = r;
            } 
        }
        return shortest;
    }

    // Stegar fram affären ett steg i tiden
    public void step() {
        for(Register r : this.registers) {
            if(r.isOpen())
                r.step(); 
        } 
    }

    // Öppnar en ny kassa om det finns stängda kassor
    public void openNewRegister() {
        for(Register r : this.registers) {
            if(!r.isOpen()) {
                r.open();
                return;
            }
        }
    }

    // Plockar bort alla kunder som är färdiga från kassaköerna och returnerar dem i en ny kö
    public Queue getDoneCustomers() {
        Queue result = new Queue();
        
        for(Register r : this.registers) {
            if( r.currentCustomerIsDone()) {
                Customer customer = r.removeCurrentCustomer();
                result.enqueue(customer);
            }
        }
        return result;
    }

    public String toString() {
        String result = ""; 
        for(Register r : this.registers) {
            result += r.toString() + "\n"; 
        }
        return result;
    }
}