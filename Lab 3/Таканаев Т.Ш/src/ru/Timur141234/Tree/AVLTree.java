package ru.Timur141234.Tree;

public class AVLTree {
    public BinaryTree root = null;

    private static BinaryTree insert(int x, BinaryTree n) {
        if (n == null) { // если дерево пустое то новый элемент то что нам нужно
            return new BinaryTree(null, null, x);
        }
        if (x < n.value) { // ну тут дерево поиска, если меньше текущей вершины влево вставляем
            n.left = insert(x, n.left);
        } else if (x > n.value) { // иначе вправо
            n.right = insert(x, n.right);
        }
        return correctBin(n); // корректируем avl дерево
    }

    private static boolean exists(int x, BinaryTree n) {
        if (x == n.value) { // текущий то что мы ищем
            return true;
        }
        if (x < n.value) { // ищем слева
            return n.left != null && exists(x, n.left);
        } else { // ищем справа
            return n.right != null && exists(x, n.right);
        }

    }

    private static BinaryTree delete(int x, BinaryTree n) {
        if (n == null) { // если ничего нет ничего не удаляем
            return null;
        }
        if (x < n.value) { // ищем слева
            n.left = delete(x, n.left);
        } else if (x > n.value) { // ищем справа
            n.right = delete(x, n.right);
        } else if (n.left == null || n.right == null) { // если текущий и нет слева или справа сыновей
            if (n.right == null && n.left != null) {  // тут вроде понятно
                n = n.left;
            } else if (n.right != null) {
                n = n.right;
            } else {
                n = null;
            }
        } else {
            BinaryTree s = next(x, n.right); // берем правое поддерево и привязываем
            if (s != null) {
                n.value = s.value;
                n.right = correctBin(delete(s.value, n.right)); // корректируем
            }
        }
        return correctBin(n); // корректируем

    }

    private static void dfs_lnr(BinaryTree n, StringBuilder stringBuilder) { // дфс в порядке лево текущая вершина право
        if (n != null) {
            if (n.left != null) {
                dfs_lnr(n.left, stringBuilder);
            }
            stringBuilder.append(n.value).append(" ");
            if (n.right != null) {
                dfs_lnr(n.right, stringBuilder);
            }
        }
    }

    private static void dfs_nlr(BinaryTree n, StringBuilder stringBuilder) { // дфс в порядке текущая вершина лево право
        if (n != null) {
            stringBuilder.append(n.value).append(" ");
            if (n.left != null) {
                dfs_lnr(n.left, stringBuilder);
            }
            if (n.right != null) {
                dfs_lnr(n.right, stringBuilder);
            }
        }
    }

    private static void dfs_lrn(BinaryTree n, StringBuilder stringBuilder) { // дфс в порядке текущая лево право вершина
        if (n != null) {
            if (n.left != null) {
                dfs_lnr(n.left, stringBuilder);
            }
            if (n.right != null) {
                dfs_lnr(n.right, stringBuilder);
            }
            stringBuilder.append(n.value).append(" ");
        }
    }

    public void dfs_nlr_iterator(BinaryTree top, StringBuilder stringBuilder) { // итеративный дфс
        Stack stack = new Stack(1024);
        while (top != null || !stack.isEmpty()) {
            if (!stack.isEmpty()) {
                top = stack.popElement();
            }
            while (top != null) {
                stringBuilder.append(top.value).append(" ");
                if (top.right != null) stack.pushElement(top.right);
                top = top.left;
            }
        }
    }

    private static BinaryTree next(int x, BinaryTree n) { // все деревья после x
        BinaryTree next = null;
        while (n != null) {
            if (x < n.value) {
                next = n;
                n = n.left;
            } else {
                n = n.right;
            }
        }
        return next;

    }

    private static BinaryTree lSRotation(BinaryTree n) { // мало левое вращение
        BinaryTree t = n.right;
        n.right = t.left;
        t.left = n;
        upd(n);
        upd(t);
        return t;
    }

    private static BinaryTree rSRotation(BinaryTree n) { // малое правое вращение
        BinaryTree t = n.left;
        n.left = t.right;
        t.right = n;
        upd(n);
        upd(t);
        return t;
    }

    private static BinaryTree lBRotation(BinaryTree n) { // большое левое вращение
        n.right = rSRotation(n.right);
        return lSRotation(n);

    }

    private static BinaryTree rBRotation(BinaryTree n) { // большое правое вращение
        n.left = lSRotation(n.left);
        return rSRotation(n);

    }

    private static BinaryTree correctBin(BinaryTree n) {
        if (n != null) {
            upd(n);
            // вычисляем баланс фактор и относительного него поворачиваем
            int l = n.left != null ? n.left.d : 3; // для левой
            int r = n.right != null ? n.right.d : 3; // для правой
            int lc = (n.left != null && n.left.right != null) ? n.left.right.d : 3; // для правой из левого сына
            int rc = (n.right != null && n.right.left != null) ? n.right.left.d : 3; // для левого из правого сына
            if (n.d == -2) {
                if (r == 0 || r == -1) {
                    return lSRotation(n);
                }
                if (r == 1 && (rc == 0 || rc == 1)) {
                    return lBRotation(n);
                }
            }
            if (n.d == 2) {
                if (l == 0 || l == 1) {
                    return rSRotation(n);
                }
                if (l == -1 && (lc == -1 || lc == 0)) {
                    return rBRotation(n);
                }
            }
        }
        return n;
    }

    private static void upd(BinaryTree n) {
        if (n != null) {
            // вычисляем новую высоту и баланс
            n.c = Math.max((n.left != null ? n.left.c : 0), (n.right != null ? n.right.c : 0)) + 1;
            n.d = (n.left != null ? n.left.c : 0) - (n.right != null ? n.right.c : 0);
        }
    }

    // все методы не храня текущей ноды для удобства

    public void dfs_lnr() {
        StringBuilder builder = new StringBuilder();
        dfs_lnr(root, builder);
        System.out.println(builder);
    }

    public void dfs_nlr() {
        StringBuilder builder = new StringBuilder();
        dfs_nlr(root, builder);
        System.out.println(builder);
    }

    public void dfs_nlr_iterator() {
        StringBuilder builder = new StringBuilder();
        dfs_nlr_iterator(root, builder);
        System.out.println(builder);
    }

    public void dfs_lrn() {
        StringBuilder builder = new StringBuilder();
        dfs_lrn(root, builder);
        System.out.println(builder);
    }

    public void bfs() {
        StringBuilder builder = new StringBuilder();
        LinkedList queue = new LinkedList();
        queue.addHead(root);
        while (queue.getSize() != 0) {
            BinaryTree current = queue.deleteTail();
            if (current == null) {
                continue;
            }
            builder.append(current.value).append(" ");
            queue.addTail(current.left);
            queue.addTail(current.right);
        }
        System.out.println(builder);
    }

    public boolean find(int x) {
        return exists(x, root);
    }

    public void insert(int x) {
        if (root == null) {
            root = new BinaryTree(null, null, x);
        } else {
            root = insert(x, root);
        }
    }

    public void delete(int x) {
        root = delete(x, root);
    }
}