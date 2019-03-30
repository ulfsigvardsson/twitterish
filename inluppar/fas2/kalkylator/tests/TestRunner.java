import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;
import org.junit.Test;

public class TestRunner {
    @Test
    public void run() {
        System.out.println("\n");
        Result result = JUnitCore.runClasses(TestSuite.class);

        for (Failure failure : result.getFailures()) {
            System.out.println(failure.toString());
        }
		
        if (result.wasSuccessful()) {
            System.out.println("\nAll tests passed!");
        }
    }
}  	
