package ru.Timur141234.Structures.DynamicStack;

/**
 *
 * @author Timur Takanaev
 */
public class Stack<T> {

    private T[] array; // Массив, хранящий данные.
    private int top; // Индекс элемента, находящегося в вершине стека.
    private int capacity; // Вместимость стека.

    public Stack(int size) {

        this.array = (T[]) new Object[size];
        this.top = -1;
        this.capacity = size;

    }

    public void push(T value) {

        if (!isFull()) {

//            System.err.println("Добавляем " + value);
            top++;
            array[top] = value;

        } else {

            System.err.println("В стеке больше нет места!");
            System.exit(0);

        }

    }

    public T pop() {

        if (isEmpty()) {

            System.err.println("В стеке отсутствуют какие-либо элементы!");
            System.exit(0);

        }

        T value = array[top];

//        System.err.println("Удаляем " + value);
        array[top] = null;
        top--;

        return value;
    }

    public T peek() {

        if (isEmpty()) {

            System.err.println("В стеке отсутствуют какие-либо элементы!");
            System.exit(0);

        }

        return array[top];
    }

    public int getSize() {
        return top + 1;
    }

    public boolean isEmpty() {
        return getSize() == 0;
    }

    public boolean isFull() {
        return getSize() == capacity;
    }
}
