package ru.Timur141234;

/**
 * @author Timur Takanaev
 */
class Timsort {

    public ArrayList<Edge> sort(ArrayList<Edge> array) {
        int minrun = minrun(array.size()); // получаем minrun
//        System.err.println("minrun " + minrun);
        ArrayList<ArrayList<Edge>> runs = splay(array, minrun); // режем наш массив на minrun
//        System.err.println("Runs!");
//        for (List<Integer> run : runs) {
//            for (int to : run) {
//                System.err.print(to);
//                System.err.print(" ");
//            }
//            System.err.println();
//        }
//        System.err.println("Merge!");
        return merge(runs);
    }

    private static int minrun(int n) { // умные дядьки посчитали что эффективны значения где-то [32-64] вот алгортим
        int r = 0;
        while (n >= 64) {
            r |= n & 1;
            n >>= 1;
        }
        return n + r;
    }

    private static ArrayList<ArrayList<Edge>> splay(ArrayList<Edge> array, int minrun) { // разделить массив на массив runs
        //где минимальный размер run >= minrun (последний не в счет)
        ArrayList<ArrayList<Edge>> runs = new ArrayList<>(array.size() / minrun);
        int pointer = 0;
        int indexRuns = 0;
        while (pointer < array.size()) {
            runs.append(new ArrayList<>(minrun));
            Edge value1 = array.get(pointer);
            runs.get(indexRuns).append(value1);
            if (pointer + 1 >= array.size()) {
                break;
            }
            pointer++;
            Edge value2 = array.get(pointer);
            runs.get(indexRuns).append(value2);
            boolean need = value1.value > value2.value;
            if (need) { // пытаемся находить строго убывающую последовательность
                while (pointer + 1 < array.size()) {
                    pointer++;
                    value1 = value2;
                    value2 = array.get(pointer);
                    if (value1.value <= value2.value) {
                        pointer--;
                        break;
                    }
                    runs.get(indexRuns).append(value2);
                }
                ArrayList<Edge> reverseList = runs.get(indexRuns);
                reverseList.reverse();
                runs.set(indexRuns, reverseList);
            } else { // не строго убывающую
                while (pointer + 1 < array.size()) {
                    pointer++;
                    value1 = value2;
                    value2 = array.get(pointer);
                    if (value1.value > value2.value) {
                        pointer--;
                        break;
                    }
                    runs.get(indexRuns).append(value2);
                }
            }
            while (pointer + 1 < array.size() && runs.get(indexRuns).size() < minrun) { // добавляем остальное
                pointer++;
                runs.get(indexRuns).append(array.get(pointer));
            }
            indexRuns++;
            pointer++;
        }
        for (int i = 0; i < runs.size(); i++) { // ну и каждую из них сортируем
            sortInsert(runs.get(i));
        }
        return runs;
    }

    private static void sortInsert(ArrayList<Edge> array) { // сортировка вставками
        for (int left = 0; left < array.size(); left++) {
            // Вытаскиваем значение элемента
            Edge value = array.get(left);
            // Перемещаемся по элементам, которые перед вытащенным элементом
            int i = left - 1;
            for (; i >= 0; i--) {
                // Если вытащили значение меньшее — передвигаем больший элемент дальше
                if (value.value < array.get(i).value) {
                    array.set(i + 1, array.get(i));
                } else {
                    // Если вытащенный элемент больше — останавливаемся
                    break;
                }
            }
            // В освободившееся место вставляем вытащенное значение
            array.set(i + 1, value);
        }
    }

    private static ArrayList<Edge> merge(ArrayList<ArrayList<Edge>> runs) {
        // нам надо объединять списки примерно одинаковых размеров чтобы было быстро поэтому используем умный алгоритм
        // со стеком, который будет смотреть на размеры runs
        // подробнее про его эффективность можно прочитать на neerc.itmo (тут сложно в двух словах)
        Stack<ArrayList<Edge>> stack = new Stack<>(runs.size());
        for (int i = 0; i < runs.size(); i++) {
            ArrayList<Edge> x = runs.get(i);
            stack.push(x);
            if (stack.size() > 2) {
                x = stack.pop();
                ArrayList<Edge> y = stack.pop();
                ArrayList<Edge> z = stack.pop();
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
                ArrayList<Edge> y = stack.pop();
                if (y.size() <= x.size()) {
                    stack.push(mergeRuns(x, y));
                } else {
                    stack.push(x);
                    stack.push(y);
                }
            }
        }
        while (stack.size() != 1) {
            ArrayList<Edge> x = stack.pop();
            ArrayList<Edge> y = stack.pop();
            stack.push(mergeRuns(x, y));
        }
        return stack.pop();
    }

    private static ArrayList<Edge> mergeRuns(ArrayList<Edge> left, ArrayList<Edge> right) { // объедиенение двух run
        int leftPointer = 0;
        int leftCounter = 0;
        int rightPointer = 0;
        int rightCounter = 0;
        ArrayList<Edge> ans = new ArrayList<>(left.size() + right.size());
        while (leftPointer < left.size() && rightPointer < right.size()) {
            if (left.get(leftPointer).value > right.get(rightPointer).value) { // если элемент со списка справа меньше берем его
                ans.append(right.get(rightPointer)); // если со списка справа значение меньше чем слева
                rightPointer++; // переставляем указатель на следующий
                rightCounter++; // счетчик для галопа
                // galloping mode for right
                leftCounter = 0;
                if (rightCounter >= 7) { // старт режима галопа в JAVA SDK 7 равен 7 поэтому
                    int toRight = binarySearch(right, rightPointer, left.get(leftPointer).value); // чтобы не сравнивать дальше O(n^2)
                    // предпологаем что последующие отсортированы, чтобы проверить это ищем бинарным поиском границу)
                    for (int fromRight = rightPointer; fromRight < toRight; fromRight++) {
                        ans.append(right.get(rightPointer)); // добавляем до этой границы
                        rightPointer++;
                    }
                    rightCounter = 0;
                }
            } else { // иначе тоже самое что с правым, только с левым
                ans.append(left.get(leftPointer));
                leftPointer++;
                leftCounter++;
                // galloping mode for left
                rightCounter = 0;
                if (leftCounter >= 7) {
                    int toLeft = binarySearch(left, leftPointer, right.get(rightPointer).value);
                    for (int fromLeft = leftPointer; fromLeft < toLeft; fromLeft++) {
                        ans.append(left.get(leftPointer));
                        leftPointer++;
                    }
                }
            }
        }
        while (leftPointer < left.size()) { // остатки тоже в массив
            ans.append(left.get(leftPointer));
            leftPointer++;
        }
        while (rightPointer < right.size()) { // остатки тоже в массив
            ans.append(right.get(rightPointer));
            rightPointer++;
        }
        return ans; // наш объедиеннный список
    }

    private static int binarySearch(ArrayList<Edge> arr, int left, int value) { // обычный бинарный поиск
        int right = arr.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr.get(mid).value > value) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return right + 1;
    }
}
