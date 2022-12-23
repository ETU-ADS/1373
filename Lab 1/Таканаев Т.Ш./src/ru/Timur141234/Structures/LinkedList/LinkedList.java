package ru.Timur141234.Structures.LinkedList;

/**
 *
 * @author Timur Takanaev
 */
public class LinkedList {

    private Node head = null;

    {
        head = new Node();
    }

    public LinkedList() {

    }

    public void addHead(int value) {

        Node node = new Node(value);

        if (head.next != null) {

            node.next = head.next;

        }

        head.next = node;

    }

    public void addTail(int value) {

        Node node = new Node(value);
        Node ptr = head;

        while (ptr.next != null) {

            ptr = ptr.next;

        }

        ptr.next = node;

    }

    public void add(int index, int value) {

        if (index >= 0 && index <= getSize()) {

            int pos = 0;

            Node ptr = head;

            while (pos != index) {

                ptr = ptr.next;
                pos += 1;

            }

            Node node = new Node(value);

            node.next = ptr.next;
            ptr.next = node;

        }

    }

    public void deleteAt(int index) {

        if (index == 0) {

            head = head.next;

        } else {

            int pos = 0;

            Node node = head;
            Node temp;

            while (pos < index) {

                node = node.next;
                pos += 1;

            }

            if (node == null || node.next == null) {

                System.out.println("Вы не можете использовать этот индекс! Индекс: " + index);
                System.exit(0);

            }

            temp = node.next;
            node.next = temp.next;

        }

    }

    public void print() {

        Node ptr = head;

        while (ptr.next != null) {

            ptr = ptr.next;
            System.out.println("Элемент: " + ptr.data);

        }

    }

    public int getSize() {

        int size = 0;

        Node ptr = head;

        while (ptr.next != null) {

            ptr = ptr.next;
            size += 1;

        }

        return size;

    }

}
