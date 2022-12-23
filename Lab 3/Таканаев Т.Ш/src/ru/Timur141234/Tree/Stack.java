package ru.Timur141234.Tree;

/**
 *
 * @author Timur Takanaev
 */
public class Stack {

    private BinaryTree array[]; // Массив, хранящий данные.
    private int top; // Индекс элемента, находящегося в вершине стека.
    private int capacity; // Вместимость стека.

    public Stack(int size) {

        array = new BinaryTree[size];
        top = -1;
        capacity = size;

    }

    public void pushElement(BinaryTree value) {

        if (!isFull()) {

            System.out.println("Добавляем " + value);

            top++;
            array[top] = value;

        } else {
            System.out.println("В стеке больше нет места!");
            System.exit(0);
        }

    }

    public BinaryTree popElement() {

        if (isEmpty()) {
            System.out.println("В стеке отсутствуют какие-либо элементы!");
            System.exit(0);
        }

        BinaryTree value = array[top];

        System.out.println("Удаляем " + value);

        array[top] = new BinaryTree(null, null, 0);
        top--;

        return value;
    }

    public BinaryTree peekElement() {

        if (isEmpty()) {

            System.out.println("В стеке отсутствуют какие-либо элементы!");
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
