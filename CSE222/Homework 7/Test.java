import HW7.*;
import java.util.Scanner;

/**
* Main
*/
public class Test{
	public static void main( String args[] ){
        System.out.println("\n\n**************** WELCOME ****************\n");
        String choice;
        do{
            System.out.println("\n1) Part1");
            System.out.println("2) Part2");
            System.out.println("3) Part3(works take a little longer, please wait)");
            System.out.println("0) Exit\n");
            System.out.print("-->Please select: ");

            Scanner scanner = new Scanner(System.in);
            choice = scanner.nextLine();

            if( choice.equals("0") ){
                System.out.println("Goodbye!");
            } else if( choice.equals("1") ){
                Part1 part1 = new Part1();
                part1.test();
            } else if( choice.equals("2") ){
                Part2 part2 = new Part2();
                part2.test();
            } else if( choice.equals("3") ){
                Part3 part3 = new Part3();
                part3.part3();
            } else{
                System.out.println("Invalid input.");
            }
        } while( !choice.equals("0") );
    }
}