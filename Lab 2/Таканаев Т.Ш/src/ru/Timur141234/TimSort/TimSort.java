package ru.Timur141234.TimSort;

import ru.Timur141234.TimSort.Structures.ArrayList;
import ru.Timur141234.TimSort.Structures.Stack;

/**
 *
 * @author MSI
 */
public class TimSort {

    public ArrayList<Integer> sort(ArrayList<Integer> array) {

        int minrun = minrun(array.size()); // Получаем minrun.
        ArrayList<ArrayList<Integer>> runs = splay(array, minrun); // Режем наш массив на minrun.

        return merge(runs);
    }

    private static int minrun(int n) { // Эффективные значения: [32-64]

        int r = 0;

        while (n >= 64) {

            r |= n & 1;
            n >>= 1;

        }

        return n + r;
    }

    private static ArrayList<ArrayList<Integer>> splay(ArrayList<Integer> array, int minrun) { // Разделить массив на массив runs.

        ArrayList<ArrayList<Integer>> runs = new ArrayList<>(array.size() / minrun);

        int pointer = 0;
        int indexRuns = 0;

        while (pointer < array.size()) {

            runs.append(new ArrayList<>(minrun));

            int value1 = array.get(pointer);
            runs.get(indexRuns).append(value1);

            if (pointer + 1 >= array.size()) {
                break;
            }

            pointer++;

            int value2 = array.get(pointer);

            runs.get(indexRuns).append(value2);

            boolean need = value1 > value2;

            if (need) { // Пытаемся находить строго убывающую последовательность.

                while (pointer + 1 < array.size()) {

                    pointer++;
                    value1 = value2;
                    value2 = array.get(pointer);

                    if (value1 <= value2) {

                        pointer--;
                        break;

                    }

                    runs.get(indexRuns).append(value2);

                }

                ArrayList<Integer> reverseList = runs.get(indexRuns);
                reverseList.reverse();
                runs.set(indexRuns, reverseList);

            } else { // В противном случае ищем нестрого убывающую.

                while (pointer + 1 < array.size()) {

                    pointer++;
                    value1 = value2;
                    value2 = array.get(pointer);

                    if (value1 > value2) {

                        pointer--;
                        break;

                    }

                    runs.get(indexRuns).append(value2);
                }

            }

            while (pointer + 1 < array.size() && runs.get(indexRuns).size() < minrun) { // Добавляем остальное.

                pointer++;
                runs.get(indexRuns).append(array.get(pointer));

            }

            indexRuns++;
            pointer++;
        }

        for (int i = 0; i < runs.size(); i++) { // Каждую из них сортируем сортировкой вставками.
            sortInsert(runs.get(i));
        }

        return runs;
    }

    private static void sortInsert(ArrayList<Integer> array) { // Сортировка вставками.

        for (int left = 0; left < array.size(); left++) {

            int value = array.get(left); // Вытаскиваем значение элемента.
            int i = left - 1; // Перемещаемся по элементам, которые перед вытащенным элементом.

            for (; i >= 0; i--) {

                if (value < array.get(i)) { // Если вытащили значение меньшее — передвигаем больший элемент дальше.

                    array.set(i + 1, array.get(i));

                } else { // Если вытащенный элемент больше — останавливаемся.
                    break;
                }
            }

            array.set(i + 1, value); // В освободившееся место вставляем вытащенное значение.

        }

    }

    private static ArrayList<Integer> merge(ArrayList<ArrayList<Integer>> runs) { // Слияние.

        Stack<ArrayList<Integer>> stack = new Stack<>(runs.size());

        for (int i = 0; i < runs.size(); i++) {

            ArrayList<Integer> x = runs.get(i);
            stack.push(x);

            if (stack.size() > 2) {

                x = stack.pop();

                ArrayList<Integer> y = stack.pop();
                ArrayList<Integer> z = stack.pop();

                boolean lastPop = true;

                while (!(stack.size() > 2 && z.size() > x.size() + y.size() && y.size() > x.size())) {

                    if (y.size() <= x.size()) {

                        stack.push(mergeRuns(x, y));
                        stack.push(z);

                        if (stack.size() == 2) {

                            lastPop = false;
                            break;

                        }

                        x = stack.pop();
                        y = stack.pop();
                        z = stack.pop();

                    }

                    if (z.size() <= x.size() + y.size()) {

                        if (x.size() > z.size()) {

                            stack.push(x);
                            stack.push(mergeRuns(y, z));

                        } else {

                            stack.push(mergeRuns(y, x));
                            stack.push(z);

                        }

                        if (stack.size() == 2) {

                            lastPop = false;
                            break;

                        }

                        x = stack.pop();
                        y = stack.pop();
                        z = stack.pop();

                    }
                }

                if (lastPop) {

                    stack.push(x);
                    stack.push(y);
                    stack.push(z);

                }
            }

            if (stack.size() == 2) {

                x = stack.pop();
                ArrayList<Integer> y = stack.pop();

                if (y.size() <= x.size()) {

                    stack.push(mergeRuns(x, y));

                } else {

                    stack.push(x);
                    stack.push(y);

                }
            }
        }

        while (stack.size() != 1) {

            ArrayList<Integer> x = stack.pop();
            ArrayList<Integer> y = stack.pop();
            stack.push(mergeRuns(x, y));

        }

        return stack.pop();
    }

    private static ArrayList<Integer> mergeRuns(ArrayList<Integer> left, ArrayList<Integer> right) { // Объедиенение двух run.

        int leftPointer = 0;
        int leftCounter = 0;
        int rightPointer = 0;
        int rightCounter = 0;

        ArrayList<Integer> ans = new ArrayList<>(left.size() + right.size());

        while (leftPointer < left.size() && rightPointer < right.size()) {

            if (left.get(leftPointer) > right.get(rightPointer)) { // Если элемент со списка справа меньше, то берем его.

                ans.append(right.get(rightPointer)); // Если со списка справа значение меньше, чем слева.
                rightPointer++; // Переставляем указатель на следующий.
                rightCounter++; // Счетчик для галопа.

                leftCounter = 0; // Режим Галопа для правой части.

                if (rightCounter >= 7) {

                    int toRight = binarySearch(right, rightPointer, left.get(leftPointer)); // Чтобы не сравнивать дальше O(n^2).

                    for (int fromRight = rightPointer; fromRight < toRight; fromRight++) { // Предпологаем, что последующие отсортированы, поэтому, чтобы проверить это, ищем бинарным поиском границу.

                        ans.append(right.get(rightPointer)); // Добавляем до этой границы.
                        rightPointer++;

                    }

                    rightCounter = 0;
                }

            } else {

                ans.append(left.get(leftPointer));
                leftPointer++;
                leftCounter++;

                rightCounter = 0; // Режим Галопа для левой части.

                if (leftCounter >= 7) {

                    int toLeft = binarySearch(left, leftPointer, right.get(rightPointer));

                    for (int fromLeft = leftPointer; fromLeft < toLeft; fromLeft++) {

                        ans.append(left.get(leftPointer));
                        leftPointer++;

                    }

                }

            }

        }

        while (leftPointer < left.size()) { // Остатки тоже помещаем в массив.

            ans.append(left.get(leftPointer));
            leftPointer++;

        }

        while (rightPointer < right.size()) { // Остатки тоже помещаем в массив.

            ans.append(right.get(rightPointer));
            rightPointer++;

        }

        return ans; // Наш объедиенный список.
    }

    private static int binarySearch(ArrayList<Integer> arr, int left, int value) { // Бинарный поиск.

        int right = arr.size() - 1;

        while (left <= right) {

            int mid = (left + right) / 2;

            if (arr.get(mid) > value) {

                right = mid - 1;

            } else {

                left = mid + 1;

            }

        }

        return right + 1;
    }

}
