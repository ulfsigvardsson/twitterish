import org.junit.Test;
import static org.junit.Assert.*;

public class TestCustomer {

    @Test 
    public void testNewCustomer() {
        Customer customer = new Customer(1, 10);
        assertEquals(customer.remainingGroceries(), 10);
    }
}
