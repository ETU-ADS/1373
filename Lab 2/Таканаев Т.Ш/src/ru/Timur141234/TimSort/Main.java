package ru.Timur141234.TimSort;

import java.security.SecureRandom;
import java.util.Scanner;
import ru.Timur141234.TimSort.Structures.ArrayList;

/**
 *
 * @author MSI
 */
public class Main {

    public static void main(String[] args) {

        TimSort timsort = new TimSort();
        Scanner sc = new Scanner(System.in);

        System.out.println("Введите количество элементов, которые будут получены с клавиатуры: ");

        int n = sc.nextInt();

        ArrayList<Integer> array = new ArrayList<>(n);

        for (int i = 0; i < n; i++) {

            int random = new SecureRandom().nextInt(100);

            System.out.println("Random: " + random);
            array.append(random);

        }

        ArrayList<Integer> answer = timsort.sort(array);

        for (int i = 0; i < answer.size(); i++) {

            System.out.print(answer.get(i));
            System.out.print(" ");

        }
    }

}
