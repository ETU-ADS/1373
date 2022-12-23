package ru.Timur141234.Tree;

import java.util.ArrayList;

public class BinaryTreeBracketsParser {
    private int startIndex = 0;
    private int bracketsCnt = 0;


    BinaryTree BinaryTreeBracketsParserConvert(String s) {
        this.startIndex = 0; // Чтобы не было рекурсии придумал хранить последний индекс на котором мы были (обнуляем)
        this.bracketsCnt = 1;
        // Ну а вдруг кто-то еще раз запустит а там какое-то старое значение
        if (s.length() < 2) { // () empty?
            throw new RuntimeException("It's bad brackets string");
        }
        BinaryTree ans = BinaryTreeBracketsParserRecursion(s); // запускаем рекурсию для строки
        if (this.bracketsCnt != 0) {
            throw new RuntimeException("It's bad brackets string");
        }
        if (this.startIndex + 1 != s.length()) {
            throw new RuntimeException("It's bad brackets string");
        }
        return ans;
    }

    private BinaryTree BinaryTreeBracketsParserRecursion(String s) { // обрабатывает строчку типа (a,(...),(...), ..)
        //где ... - такая же строчка того же типа что и обрабатывается
        int value = 0; // текущее значение
        ArrayList<BinaryTree> arrayOfTree = new ArrayList<>(); // массив сыновей
        boolean checker = false;
        this.startIndex += 1; // first ignore
        while (this.startIndex < s.length() && s.charAt(this.startIndex) != ')') { // Пока не конец или закрывающая скобка
            checker = add_symbol(s.charAt(this.startIndex));
            if (checker) {
                throw new RuntimeException("It's bad brackets string");
            }
            // ну если закрывающая мы ее обработали офк
            if (s.charAt(this.startIndex) == '(') { // если открывающая значит что пошла строчка типа суем в рекурсию
                // а так как она встретилась в данной строка значит она сын
                arrayOfTree.add(BinaryTreeBracketsParserRecursion(s));
            } else {
                if (Character.isDigit(s.charAt(this.startIndex))) { // если число значит то число которое есть в данной скобке (то есть значение)
                    value = value * 10 + (s.charAt(this.startIndex) - '0');
                } else {
                    throw new RuntimeException("Unknown symbol");
                }
            }
            this.startIndex += 1;
        }
        if (this.startIndex < s.length()) {
            checker = add_symbol(s.charAt(this.startIndex));
            if (checker) {
                throw new RuntimeException("It's bad brackets string");
            }
        }
        while (arrayOfTree.size() < 2) { // добавляем до двух ссыновей
            arrayOfTree.add(null);
        }
        if (arrayOfTree.size() > 2) {
            throw new RuntimeException("It's not a binary tree");
        }
        return new BinaryTree(arrayOfTree.get(0), arrayOfTree.get(1), value); // создаем дерево
    }

    private boolean add_symbol(char s) {
        if (s == '(') {
            this.bracketsCnt += 1;
        } else if (s == ')') {
            this.bracketsCnt -= 1;
        }
        return it_bad_brackets();
    }

    private boolean it_bad_brackets() {
        return this.bracketsCnt < 0;
    }
}
