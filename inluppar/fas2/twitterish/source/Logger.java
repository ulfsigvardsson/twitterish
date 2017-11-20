import java.io.*;
import java.util.*;
import java.net.*;

public class Logger {
    private PrintWriter logger;

    public Logger(String path) {
        try {
            this.logger = new PrintWriter(path);            
        }
        catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
            e.printStackTrace();
        }

    }

    public void log(String msg){
        this.logger.println(msg);
    }

    public void logClose() {
        this.logger.close();
    }
}
