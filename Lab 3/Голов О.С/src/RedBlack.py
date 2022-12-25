class Node:
    def __init__(self, val, parent=None):
        self.val = val
        self.is_red = False
        self.p = parent
        self.left_tree = None
        self.right_tree = None


class RBTree:
    def __init__(self):
        self.root = None


def dfs1(tree: Node):
    array = []
    visited = []

    while tree is not None:
        # if tree in visited:
        if tree not in visited:
            visited.append(tree)
            array.append((int(tree.val), tree.is_red))
        if tree.left_tree is not None and tree.left_tree not in visited:
            tree = tree.left_tree
        elif tree.right_tree is not None and tree.right_tree not in visited:
            tree = tree.right_tree
        else:
            tree = tree.p

    return array


def dfs2(tree: Node):
    array = []
    visited = []
    while len(visited) > 0 or tree is not None:
        if tree is not None:
            visited.append(tree)
            tree = tree.left_tree
        else:
            tree = visited.pop(-1)
            array.append((tree.val, tree.is_red))
            tree = tree.right_tree
    return array


def dfs3(tree: Node):
    array = []
    visited = []
    last = None
    while len(visited) > 0 or tree is not None:
        if tree is not None:
            visited.append(tree)
            tree = tree.left_tree
        else:
            peek = visited[-1]
            if peek.right_tree is not None and last != peek.right_tree:
                tree = peek.right_tree
            else:
                array.append((peek.val, peek.is_red))
                last = visited.pop(-1)
    return array


def bfs(t):
    tree = t.root
    array = []
    visited = [tree]
    while len(visited) > 0:
        tree = visited.pop(0)
        array.append((tree.val, tree.is_red))
        if tree.left_tree is not None:
            visited.append(tree.left_tree)
        if tree.right_tree is not None:
            visited.append(tree.right_tree)
    return array


def search(t: RBTree, value):
    x = t.root
    while x is not None:
        if value < x.val:
            x = x.left_tree
        elif value > x.val:
            x = x.right_tree
        elif value == x.val:
            return x
    return None


def left_rotate(t: RBTree, x: Node):
    y = x.right_tree
    x.right_tree = y.left_tree
    if y.left_tree is not None:
        y.left_tree.p = x
    y.p = x.p
    if x.p is None:
        t.root = y
    elif x == x.p.left_tree:
        x.p.left_tree = y
    else:
        x.p.right_tree = y
    y.left_tree = x
    x.p = y


def right_rotate(t: RBTree, x: Node):
    y = x.left_tree
    x.left_tree = y.right_tree
    if y.right_tree is not None:
        y.right_tree.p = x
    y.p = x.p
    if x.p is None:
        t.root = y
    elif x == x.p.right_tree:
        x.p.right_tree = y
    else:
        x.p.left_tree = y
    y.right_tree = x
    x.p = y


def insertRB(t: RBTree, z: Node):
    y = None
    x = t.root
    while x is not None:
        y = x
        if z.val < x.val:
            x = x.left_tree
        else:
            x = x.right_tree
    z.p = y
    if y is None:
        t.root = z
    elif z.val < y.val:
        y.left_tree = z
    else:
        y.right_tree = z
    z.left_tree = None
    z.right_tree = None
    z.is_red = True
    insert_fixup(t, z)


def insert_fixup(t, z):
    while z.p is not None and z.p.is_red is True:
        if z.p == z.p.p.left_tree:
            y = z.p.p.right_tree
            if y is not None and y.is_red:
                z.p.is_red = False
                y.is_red = False
                z.p.p.is_red = True
                z = z.p.p
            else:
                if z == z.p.right_tree:
                    z = z.p
                    left_rotate(t, z)
                z.p.is_red = False
                z.p.p.is_red = True
                right_rotate(t, z.p.p)
        else:
            y = z.p.p.left_tree
            if y is not None and y.is_red:
                z.p.is_red = False
                y.is_red = False
                z.p.p.is_red = True
                z = z.p.p
            else:
                if z == z.p.left_tree:
                    z = z.p
                    right_rotate(t, z)
                z.p.is_red = False
                z.p.p.is_red = True
                left_rotate(t, z.p.p)
    t.root.is_red = False


def trasplant(t: RBTree, u: Node, v: Node):
    if u.p is None:
        t.root = v
    elif u == u.p.left_tree:
        u.p.left_tree = v
    else:
        u.p.right_tree = v
    if v is not None:
        v.p = u.p


def delete_RB(t, k):
    z = search(t, k)
    if z is None:
        print(f'''{k} not in this tree''')
        return
    y = z
    ocolor_is_red = y.is_red
    if z.left_tree is None:
        x = z.right_tree
        trasplant(t, z, z.right_tree)
    elif z.right_tree is None:
        x = z.left_tree
        trasplant(t, z, z.left_tree)
    else:
        y = z.right_tree
        while y.left_tree is not None:
            y = y.left_tree
        ocolor_is_red = y.is_red
        x = y.right_tree
        if y.p == z:
            x.p = y
        else:

            trasplant(t, y, y.right_tree)
            y.right_tree = z.right_tree
            y.right_tree.parent = y
        trasplant(t, z, y)
        y.left_tree = z.left_tree
        y.left_tree.p = y
        y.is_red = z.is_red
    if x is not None:
        if not ocolor_is_red:
            print('f')
            delete_fixup(t, x)


def delete_fixup(t, x):
    while x != t.root and x.is_red is False:
        if x == x.p.left_tree:
            w = x.p.right_tree
            # type 1
            if w.is_red:
                w.is_red = False
                x.p.is_red = True
                left_rotate(t, x.p)
                w = x.p.right_tree
            # type 2
            if w.left_tree.is_red is False and w.right_tree.is_red is False:
                w.is_red = True
                x = x.p
            else:  # type 3
                if not w.right_tree.is_red:
                    w.left_tree.is_red = False
                    w.is_red = True
                    right_rotate(t, w)
                    w = x.p.right_tree
                # type 4
                w.is_red = x.p.is_red
                x.p.is_red = False
                w.right_tree.is_red = False
                left_rotate(t, x.p)
                x = t.root
        else:
            w = x.p.left_tree
            # type 1
            if w.is_red:
                w.is_red = False
                x.p.is_red = True
                right_rotate(t, x.p)
                w = x.p.left_tree
            # type 2
            if w.right_tree.is_red is False and w.left_tree.is_red is False:
                w.is_red = True
                x = x.p
            else:  # type 3
                if not w.left_tree.is_red:
                    w.right_tree.is_red = False
                    w.is_red = True
                    left_rotate(t, w)
                    w = x.p.left_tree
                # type 4
                w.is_red = x.p.is_red
                x.p.is_red = False
                w.left_tree.is_red = False
                right_rotate(t, x.p)
                x = t.root
    x.is_red = False
