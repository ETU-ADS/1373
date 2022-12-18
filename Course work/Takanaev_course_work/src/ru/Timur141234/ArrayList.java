package ru.Timur141234;

/**
 * @author Timur Takanaev
 */
public class ArrayList<T> extends Object {

    private T[] array; // Массив, хранящий данные.
    private int size; // Вместимость динамического списка.

    public ArrayList(int capacity) {

        this.array = (T[]) new Object[capacity];
        size = 0;

    }

    public int size() {
        return size;
    }

    public void add(int index, T value) {

        if (index < 0 || index > size) {

            System.err.println("Вы не можете использовать этот индекс! Индекс: " + index);
            System.exit(0);

        }

        if (size == array.length) {

            resize(2 * array.length);

        }

        for (int i = size - 1; i >= index; i--) {

            array[i + 1] = array[i];

        }

        array[index] = value;
        size += 1;
    }

    public void set(int index, T value) {

        if (index < 0 || index > size) {

            System.err.println("Вы не можете использовать этот индекс! Индекс: " + index);
            System.exit(0);

        }

        array[index] = value;
    }

    public static <T> void swap(T[] a, int i, int j) {

        T t = a[i];
        a[i] = a[j];
        a[j] = t;

    }

    public void reverse() {

        int start = 0;

        while (start * 2 < size - 1) {

            swap(array, start, size - 1 - start);
            start += 1;

        }

    }

    public void append(T value) {
        add(size, value);
    }

    public T get(int index) {

        if (index < 0 || index >= size) {

            System.err.println("Вы не можете использовать этот индекс! Индекс: " + index);
            System.exit(0);

        }

        return array[index];
    }

    public void delete(int index) {

        if (index < 0 || index >= size) {

            System.err.println("Вы не можете использовать этот индекс! Индекс: " + index);
            System.exit(0);

        }

        for (int i = index + 1; i < size; i++) {

            array[i - 1] = array[i];

        }

        size -= 1;
    }

    public void print() {

        for (int i = 0; i < size; i += 1) {

            System.out.println("Элемент: " + array[i]);

        }

    }

    private void resize(int capacity) {

        T[] arr = (T[]) new Object[capacity];
        System.arraycopy(array, 0, arr, 0, size);
        array = arr;

    }

}
