package ru.Timur141234.ShuntingYard;

/**
 *
 * @author Timur Takanaev
 */
public class Action {

    private final int priority;
    private final OperatorBinary lambdaFunc;
    private final Associative associative;

    public enum Associative {

        LEFT,
        RIGHT,
        NONE
    }

    public Action(int priority, OperatorBinary func, Associative associative) {

        this.priority = priority;
        this.lambdaFunc = func;
        this.associative = associative;

    }

    public int getPriority() {
        return priority;
    }

    public OperatorBinary getLambdaFunc() {
        return lambdaFunc;
    }

    public Associative getAssociative() {
        return associative;
    }

}
