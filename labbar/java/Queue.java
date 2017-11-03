public class Queue {
    private Node first;
    private Node last;
    private int length;
    
    public Queue() {
        first = null;
        last = null;
        length = 0;
    }

    protected class EmptyQueueException extends RuntimeException {}
    
    public int getLength() {
        return this.length;
    }

    
    public void enqueue(Customer c) {
        if(this.getLength() == 0) {
            this.first = new Node(c);
            this.last = this.first;
        }
        
        else {
            Node temp = this.last;
            this.last = new Node(c);
            temp.next = this.last;
        }
        this.length++;
    }
    
    public Customer dequeue() {
        if (this.getLength() < 1) {
            throw new EmptyQueueException();
        }
        else {
            Node result = this.first;
            this.first = result.next;
            this.length--;
            return result.element; 
        }
    }

    public Customer first() {
        return this.first.element; 
    }

    public boolean hasFirst() {
        return this.first != null;
    }

    
    public int waitTimeQueue(int time) {
        int result = 0;
        Node current = this.first;
        while(current != null && current.element != null) {
            result += current.element.getWaitTime(time);
            current = current.next;
        }
        return result;
    } 
    
    public String toString() {
        if(this.hasFirst()) {
            String result = "";
            if (this.hasFirst()) {
                Node current = this.first;
                result += this.first.element.toString(); 
                while (current.next != null) {
                    result += "@";
                    current=current.next;
                }   
            }
            return result;
        }
        else {
            return "  [F]";
        }
    }

    private class Node {
        private Customer element;
        private Node next;
        
        public Node(Customer element) {
            this.element = element;
            this.next = null;
        }
    }

}
