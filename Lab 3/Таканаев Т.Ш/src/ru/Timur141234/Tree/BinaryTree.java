package ru.Timur141234.Tree;

public class BinaryTree { // Тут можно на дженерик но тогда пример бы был большим
    protected int d; // balance factor
    protected int c; // height
    protected BinaryTree left;
    protected BinaryTree right;
    protected int value;

    BinaryTree(BinaryTree left, BinaryTree right, int value) { // иницилизируем
        this.left = left;
        this.right = right;
        this.value = value;
    }

    public AVLTree getAVLTree() {
        AVLTree avlTree = new AVLTree();
        LinkedList queue = new LinkedList();
        queue.addHead(this);
        while (queue.getSize() != 0) {
            BinaryTree current = queue.deleteTail();
            if (current == null) {
                continue;
            }
            avlTree.insert(current.value);
            queue.addTail(current.left);
            queue.addTail(current.right);
        }
        return avlTree;
    }

    public void print() {
        if (this.left != null) this.left.print(); // Выводим лево если есть
        System.out.println(this.value);  // Выводим записанное число
        if (this.right != null) this.right.print(); // Выводим право если есть
    }
}
