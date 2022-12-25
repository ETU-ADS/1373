package ru.Timur141234.Tree;

/**
 * @author MSI
 */
public class ArrayList<T> {

    private T[] array; // Массив, хранящий данные.
    private int size; // Вместимость динамического списка.

    public ArrayList(int capacity) {
        this.array = (T[]) new Object[capacity];
        size = 0;

    }

    public int getSize() {
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
//        System.out.println("This size");
//        System.out.println(size);
        for (int i = 0; i < size; i += 1) {
            System.out.println("Элемент: " + array[i]);
        }
    }

    private void resize(int capacity) {
        T[] arr = (T[]) new Object[capacity];
        System.arraycopy(array, 0, arr, 0, capacity);
        array = arr;

    }

}
