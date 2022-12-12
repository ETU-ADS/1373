package ru.Timur141234;

import java.util.Scanner;
import ru.Timur141234.ShuntingYard.Calculator;

/**
 *
 * @author Timur Takanaev
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        System.out.println("Введите выражение: ");

        Scanner scanner = new Scanner(System.in);

        String expression = scanner.nextLine();

        Calculator calculator = new Calculator(expression);
        calculator.postfix();

    }

}
