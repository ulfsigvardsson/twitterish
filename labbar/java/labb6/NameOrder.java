import java.util.Scanner;

public class NameOrder {
    private String first;
    private String second;

    public NameOrder(String a, String b) {
        if (a.compareTo(b) < 0) {
            first = a;
            second = b;
        }
        else {
            first = b;
            second = a;
        }
    }

    public String toString() {
        return  "First: " + first + ". Second: " + second;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Välj ett namn: ");
        String name1 = sc.next();
        System.out.print("Välj ett till namn: ");
        String name2 = sc.next();
        NameOrder n = new NameOrder(name1, name2);
        System.out.println(n);
    }

    
}

