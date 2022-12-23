package ru.Timur141234;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;

/**
 * @author Timur Takanaev
 */
public class Main {

    public static void main(String[] args) throws FileNotFoundException {

        ArrayList<String> nameOfPeaks = new ArrayList<>(1024);
        Scanner input = new Scanner(new FileReader("./src/graph.txt"));
        String str = input.nextLine();

        for (String word : str.split(" ")) {

            if (word.length() > 0 && !Character.isSpaceChar(word.charAt(0))) {
                nameOfPeaks.append(word);
            }

        }

        // Считываем ребра.
        ArrayList<Edge> edges = new ArrayList<>(nameOfPeaks.size());

        for (int i = 0; i < nameOfPeaks.size(); i++) {

            for (int j = 0; j < nameOfPeaks.size(); j++) {

                int value = input.nextInt();

                if (value > 0) {
                    edges.append(new Edge(i, j, value));
                }

            }

        }

        Timsort sortMachine = new Timsort();
        edges = sortMachine.sort(edges); // Сортируем ребра.

        DSU dsu = new DSU(nameOfPeaks.size());
        ArrayList<Edge> edgesAnswer = new ArrayList<>(nameOfPeaks.size());

        // Kruskal
        for (int i = 0; i < edges.size(); i++) {

            int from = edges.get(i).from;
            int to = edges.get(i).to;
            int value = edges.get(i).value;

            if (dsu.getSet(from) != dsu.getSet(to)) { // Если не образуют цикл.

                edgesAnswer.append(new Edge(from, to, value)); // Добавляем это ребро.
                dsu.union(from, to); // Объединяем вершины в одну компоненту связанности.

            }

        }

        int answer = 0;
        for (int i = 0; i < edgesAnswer.size(); i++) {

            System.out.print(nameOfPeaks.get(edgesAnswer.get(i).from));
            System.out.print(" ");
            System.out.println(nameOfPeaks.get(edgesAnswer.get(i).to));
            answer += edgesAnswer.get(i).value;

        }

        System.out.println(answer);
    }
}
