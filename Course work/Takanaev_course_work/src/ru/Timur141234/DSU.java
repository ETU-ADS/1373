package ru.Timur141234;

/**
 * @author Timur Takanaev
 */
public class DSU {

    private int[] parent;

    public DSU(int size) {

        parent = new int[size];

        for (int i = 0; i < size; i++) {
            add(i);
        }

    }

    private void add(int x) {
        parent[x] = x;
    }

    public int getSet(int x) {
        return x == parent[x] ? x : (parent[x] = getSet(parent[x]));
    }

    public void union(int left, int right) {

        left = getSet(left);
        right = getSet(right);

        if (getSet(left) != getSet(right)) {
            parent[left] = right;
        }

    }

}
