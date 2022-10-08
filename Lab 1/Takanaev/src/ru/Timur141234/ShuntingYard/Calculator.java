package ru.Timur141234.ShuntingYard;

import java.util.HashMap;
import java.util.StringTokenizer;
import ru.Timur141234.Structures.ArrayList.ArrayList;
import ru.Timur141234.Structures.DynamicStack.Stack;

/**
 *
 * @author Timur Takanaev
 */
public class Calculator {

    private final ArrayList<String> list;
    private final HashMap<String, Action> signsSetting = new HashMap<>();

    public Calculator(String expression) {

        // Для каждой операции прописываем ее в формате <знак, приоритет операции, лямбда-функция операции, ассоциативность>
        this.signsSetting.put("-", new Action(1, (a, b) -> a - b, Action.Associative.LEFT));
        this.signsSetting.put("+", new Action(1, (a, b) -> a + b, Action.Associative.LEFT));
        this.signsSetting.put("*", new Action(2, (a, b) -> a * b, Action.Associative.LEFT));
        this.signsSetting.put("/", new Action(2, (a, b) -> a / b, Action.Associative.LEFT));
        this.signsSetting.put("^", new Action(3, (a, b) -> Math.pow(a, b), Action.Associative.RIGHT));
        this.signsSetting.put("cos", new Action(6, (a, b) -> Math.cos(b), Action.Associative.NONE));
        this.signsSetting.put("sin", new Action(6, (a, b) -> Math.sin(b), Action.Associative.NONE));

        this.list = toPostfixArray(expression);
    }

    private boolean check(Stack<String> stack, Action act) {

        if (stack.isEmpty()) {

            return false;

        }

        Action zeroAct = new Action(0, (a, b) -> 0, Action.Associative.NONE);

        int peekValue = this.signsSetting.getOrDefault(stack.peek(), zeroAct).getPriority();

        return ((act.getAssociative() == Action.Associative.LEFT) && (peekValue >= act.getPriority())
                || (act.getAssociative() != Action.Associative.LEFT) && (peekValue > act.getPriority()));
    }

    private ArrayList<String> toPostfixArray(String expression) {

        StringTokenizer tokenizer = new StringTokenizer(expression);

        ArrayList<String> prefixNatation = new ArrayList<>(1024);

        Stack<String> stack = new Stack<>(1024);

        while (tokenizer.hasMoreTokens()) {

            String token = tokenizer.nextToken();

            if (isNumeric(token)) { // Если число, то добавим в list.

                prefixNatation.append(token);

            } else if (this.signsSetting.containsKey(token)) { //  Если функция.

                while (check(stack, this.signsSetting.get(token))) { // Если операция в стеке имеет больший приоритет, то убираем ее в массив.

                    prefixNatation.append(stack.pop());

                }

                stack.push(token); // Добавляем нашу операцию в стек

            } else if (token.equals("(")) {

                stack.push("(");

            } else if (token.equals(")")) {

                while (!stack.isEmpty() && !(stack.peek().equals("("))) { // Продвигаем в массив операции до закрывающейся скобки.

                    prefixNatation.append(stack.pop());

                }

                if (stack.isEmpty()) {

                    throw new ArithmeticException("Нет открывающейся скобки (Скобочное выражение задано неверно)");

                }

                stack.pop();

            } else {

                throw new ArithmeticException("Нельзя обработать данный токен " + token);

            }
        }

        while (stack.getSize() != 0) {

            if (stack.peek().equals("(")) {

                throw new ArithmeticException("Нет закрывающейся скобки (Скобочное выражение задано неверно)");
            }

            prefixNatation.append(stack.pop());

        }

        return prefixNatation;
    }

    public void postfix() {
        list.print();
    }

    private static boolean isNumeric(String strNum) {

        if (strNum == null) {

            return false;

        }

        try {

            Double.parseDouble(strNum);

        } catch (NumberFormatException ex) {
            return false;
        }

        return true;
    }

}
