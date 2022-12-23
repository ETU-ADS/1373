#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class RB_Tree {
private:
    class Node {
    public:
        int data = 0;
        char color = 'R';
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* root = nullptr;
    class MyStack {
    public:
        class MyNode {
        public:
            Node* data;
            MyNode* next = nullptr;
        };
        MyNode* head = nullptr;
        int size = 0;

        MyStack() {
        }
        ~MyStack() {
            MyNode* tmp = head;
            while (head != nullptr) {
                tmp = head->next;
                delete head;
                head = tmp;
            }
        }
        void push(Node* newData) {
            if (head == nullptr) {
                head = new MyNode;
                head->data = newData;
            }
            else {
                MyNode* tmp = head;
                head = new MyNode;
                head->data = newData;
                head->next = tmp;
            }
            size++;
        }
        Node* pop() {
            if (head != nullptr) {
                Node* tmp_node = head->data;
                MyNode* tmp = head->next;
                delete head;
                head = tmp;
                size--;
                return tmp_node;
            }
            else cout << "Error! Stack is empty" << endl;
            return nullptr;
        }
        Node* peak() {
            if (size == 0) {
                exit(0);
            }
            return head->data;
        }
    };
    class MyQueue {
    public:
        class MyNode {
        public:
            Node* data;
            MyNode* next = nullptr;
            MyNode* prev = nullptr;
        };
        MyNode* head = nullptr;
        MyNode* end = nullptr;
        int size = 0;

        MyQueue() {
        }
        ~MyQueue() {
            MyNode* tmp = head;
            while (head != nullptr) {
                tmp = head->next;
                delete head;
                head = tmp;
            }
        }
        void push(Node* node) {
            if (head == nullptr) {
                head = new MyNode;
                head->data = node;
                end = head;
            }
            else {
                end->next = new MyNode;
                end->next->prev = end;
                end = end->next;
                end->data = node;
            }
            size++;
        }
        Node* pop() {
            size--;
            if (size > 0) {
                Node* tmp = head->data;
                head = head->next;
                delete head->prev;
                head->prev = nullptr;
                return tmp;
            }
            if (size == 0) {
                Node* tmp = head->data;
                delete head;
                end = nullptr;
                head = nullptr;
                return tmp;
            }
            cout << "Error! Queue is empty\n";
            return nullptr;
        }
    };
    void print_node(Node* node) {
        cout << " " << node->data << node->color << " ";
        if (node->left != nullptr || node->right != nullptr) {
            cout << "(";
            if (node->left != nullptr) {
                print_node(node->left);
            }
            cout << ")(";
            if (node->right != nullptr) {
                print_node(node->right);
            }
            cout << ")";
        }
    }
    void print_node_sim(Node* node) {
        if (node->left != nullptr) {
            print_node_sim(node->left);
        }
        cout << node->data << " ";
        if (node->right != nullptr) {
            print_node_sim(node->right);
        }
    }
    void print_node_obr(Node* node) {
        if (node->left != nullptr) {
            print_node_obr(node->left);
        }
        if (node->right != nullptr) {
            print_node_obr(node->right);
        }
        cout << node->data << " ";
    }
    void print_node_iter(Node* node) {
        MyStack stack;
        stack.push(node);
        while (stack.size != 0) {
            Node* tmp = stack.pop();
            cout << tmp->data << " ";
            if (tmp->right != nullptr) {
                stack.push(tmp->right);
            }
            if (tmp->left != nullptr) {
                stack.push(tmp->left);
            }
        }
    }
    void print_node_width(Node* node) {
        MyQueue que;
        que.push(node);
        while (que.size != 0) {
            Node* tmp = que.pop();
            cout << tmp->data << " ";
            if (tmp->left != nullptr) {
                que.push(tmp->left);
            }
            if (tmp->right != nullptr) {
                que.push(tmp->right);
            }
        }
    }
    void delete_node(Node* node) {
        if (node->left != nullptr) {
            delete_node(node->left);
        }
        if (node->right != nullptr) {
            delete_node(node->right);
        }
        delete node;
    }
    void left_turn(Node* node) {
        if (node == root) {
            root = node->right;
        }
        else {
            if (node == node->parent->left) {
                node->parent->left = node->right;
            }
            else {
                node->parent->right = node->right;
            }
        }
        node->right->parent = node->parent;
        node->parent = node->right;
        node->right = node->parent->left;
        node->parent->left = node;
        if (node->right != nullptr) {
            node->right->parent = node;
        }
    }
    void right_turn(Node* node) {
        if (node == root) {
            root = node->left;
        }
        else {
            if (node == node->parent->left) {
                node->parent->left = node->left;
            }
            else {
                node->parent->right = node->left;
            }
        }
        node->left->parent = node->parent;
        node->parent = node->left;
        node->left = node->parent->right;
        node->parent->right = node;
        if (node->left != nullptr) {
            node->left->parent = node;
        }
    }
    void check(Node* node) {
        Node* grand = nullptr;
        Node* uncle = nullptr;
        Node* father = nullptr;
        if (node == root) {
            node->color = 'B';
        }
        if (node->parent != nullptr) {
            father = node->parent;
        }
        if (father != nullptr && father->parent != nullptr) {
            grand = node->parent->parent;
            if (node->parent->data < grand->data) {
                uncle = grand->right;
            }
            else {
                uncle = grand->left;
            }
        }
        if (grand != nullptr && father->color == 'R') {
            if (uncle != nullptr && uncle->color == 'R') {
                father->color = 'B';
                uncle->color = 'B';
                if (grand != root) {
                    grand->color = 'R';
                }
                check(grand);
            }
            else if (father->data >= grand->data && node->data < father->data) {
                right_turn(father);
                left_turn(grand);
                grand->color = 'R';
                node->color = 'B';
                check(father);
            }
            else if (father->data < grand->data && node->data >= father->data) {
                left_turn(father);
                right_turn(grand);
                grand->color = 'R';
                node->color = 'B';
                check(father);
            }
            else if (father->data >= grand->data && node->data >= father->data) {
                left_turn(grand);
                grand->color = 'R';
                father->color = 'B';
                check(node);
            }
            else if (father->data < grand->data && node->data < father->data) {
                right_turn(grand);
                grand->color = 'R';
                father->color = 'B';
                check(node);
            }
        }
    }
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
        if (u->left != v) {
            if (u->left != nullptr) {
                u->left->parent = v;
            }
            v->left = u->left;
        }
        if (u->right != v) {
            if (u->right != nullptr) {
                u->right->parent = v;
            }
            v->right = u->right;
        }
    }
    void del_check(Node* node) {
        Node* brother = nullptr;
        if (node != root) {
            if (node == node->parent->left) {
                brother = node->parent->right;
            }
            else {
                brother = node->parent->left;
            }
        }
        while (brother != nullptr && node != root && node->color == 'B') {
            if (brother != nullptr) {
                if (brother->color == 'R') {
                    if (brother == node->parent->right) {
                        brother->color = 'B';
                        node->parent->color = 'R';
                        left_turn(node->parent);
                        brother = node->parent->right;
                    }
                    else {
                        brother->color = 'B';
                        node->parent->color = 'R';
                        right_turn(node->parent);
                        brother = node->parent->left;
                    }
                }
                if (brother != nullptr && (brother->left == nullptr || brother->left->color == 'B') && (brother->right == nullptr || brother->right->color == 'B')) {
                    brother->color = 'R';
                    node = node->parent;
                }
                else if (brother != nullptr) {
                    if ((brother->right == nullptr || brother->right->color == 'B') && brother->left != nullptr && brother->left->color == 'R') {
                        brother->left->color = 'B';
                        brother->color = 'R';
                        right_turn(brother);
                        if (node == node->parent->left) {
                            brother = node->parent->right;
                        }
                        else {
                            brother = node->parent->left;
                        }
                    }
                    if (brother->right != nullptr && brother->right->color == 'R') {
                        if (brother == node->parent->right) {
                            brother->color = node->parent->color;
                            node->parent->color = 'B';
                            if (brother->right != nullptr) {
                                brother->right->color = 'B';
                            }
                            left_turn(node->parent);
                            node = root;
                        }
                        else {
                            brother->color = node->parent->color;
                            node->parent->color = 'B';
                            if (brother->left != nullptr) {
                                brother->left->color = 'B';
                            }
                            right_turn(node->parent);
                            node = root;
                        }
                    }
                }

            }
        }
        node->color = 'B';
    }
public:
    RB_Tree() {
    }
    RB_Tree(int new_data) {
        root = new Node;
        root->data = new_data;
    }
    ~RB_Tree() {
        if (root != nullptr) {
            delete_node(root);
            root = nullptr;
        }
    }
    void insert(int new_data) {
        if (root == nullptr) {
            root = new Node;
            root->data = new_data;
            root->color = 'B';
        }
        else {
            Node** node = &root;
            Node* tmp = *node;
            while ((*node) != nullptr) {
                if (new_data < (*node)->data) {
                    tmp = *node;
                    node = &(*node)->left;
                }
                else {
                    tmp = *node;
                    node = &(*node)->right;
                }
            }
            *node = new Node;
            (*node)->data = new_data;
            (*node)->parent = tmp;
            check(*node);
        }
    }
    void insert(int new_data, char new_color) {
        if (root == nullptr) {
            root = new Node;
            root->data = new_data;
            root->color = 'B';
        }
        else {
            Node** node = &root;
            Node* tmp = *node;
            while ((*node) != nullptr) {
                if (new_data < (*node)->data) {
                    tmp = *node;
                    node = &(*node)->left;
                }
                else {
                    tmp = *node;
                    node = &(*node)->right;
                }
            }
            *node = new Node;
            (*node)->data = new_data;
            (*node)->parent = tmp;
            (*node)->color = new_color;
            check(*node);
        }
    }
    void delete_n(int find_data) {
        Node* node = root;
        while (node != nullptr && node->data != find_data) {
            if (find_data < node->data) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        if (node == nullptr) {
            cout << "The element not found\n";
        }
        else {
            while ((node->left != nullptr && node->left->data == find_data) || (node->right != nullptr && node->right->data == find_data)) {
                if (node->left != nullptr && node->left->data == find_data) {
                    node = node->left;
                }
                else {
                    node = node->right;
                }
            }
            if (node->left == nullptr) {
                transplant(node, node->right);
                if (node->color=='B') del_check(node->right);
                delete node;
            }
            else if (node->right == nullptr) {
                transplant(node, node->left);
                if (node->color=='B') del_check(node->left);
                delete node;
            }
            else {
                Node* tmp = node->right;
                while (tmp->left != nullptr) {
                    tmp = tmp->left;
                }
                Node* tmp2 = tmp->parent;
                transplant(tmp, tmp->right);
                transplant(node, tmp);
                
                if (tmp2 != node) {
                    if (tmp2->left != nullptr) {
                        if (tmp2->color == 'B') del_check(tmp2->left);
                    }
                    else {
                        Node* nil = new Node;
                        nil->color = 'B';
                        nil->parent = tmp2;
                        tmp2->left = nil;
                        if (tmp->color == 'B') del_check(nil);
                        if (nil == nil->parent->left) {
                            nil->parent->left = nullptr;
                            delete nil;
                        }
                        else {
                            nil->parent->right = nullptr;
                            delete nil;
                        }
                    }
                }
                else {
                    if (tmp->right != nullptr) {
                        if (tmp->color == 'B') del_check(tmp->right);
                    }
                    else {
                        Node* nil = new Node;
                        nil->color = 'B';
                        nil->parent = tmp;
                        tmp->right = nil;
                        if (tmp->color == 'B') del_check(nil);
                        delete nil;
                        tmp->right = nullptr;
                    }
                }
                tmp->color = node->color;
                delete(node);
            }
        }
    }
    void find(int find_data) {
        Node* tmp = root;
        while (tmp != nullptr && tmp->data != find_data) {
            if (find_data < tmp->data) {
                tmp = tmp->left;
            }
            else {
                tmp = tmp->right;
            }
        }
        if (tmp != nullptr) {
            cout << "The element " << tmp->data << " found\n";
        }
        else {
            cout << "The element not found\n";
        }
    }
    void print_tree() {
        if (root != nullptr) {
            cout << "(";
            print_node(root);
            cout << ")\n\n";
        }
        else cout << "Tree is empty\n";
    }
    void print_tree_all() {
        if (root != nullptr) {
            cout << "Pre-order (";
            print_node(root);
            cout << ")\n";

            cout << "Pre-order iter (";
            print_node_iter(root);
            cout << ")\n";

            cout << "In-order (";
            print_node_sim(root);
            cout << ")\n";

            cout << "Post-order (";
            print_node_obr(root);
            cout << ")\n";

            cout << "Width (";
            print_node_width(root);
            cout << ")\n\n";
        }
        else cout << "Tree is empty\n";
    }
    void delete_tree() {
        if (root != nullptr) {
            delete_node(root);
            root = nullptr;
        }
        else cout << "Tree is empty\n";
    }
    void right_turn() {
        right_turn(root);
    }
    void left_turn() {
        left_turn(root);
    }
};

class Tree {
private:
    class Node {
    public:
        int data = 0;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* root = nullptr;

    void print_node(Node* node) {
        cout << node->data;
        if (node->left != nullptr || node->right != nullptr) {
            cout << "(";
            if (node->left != nullptr) {
                print_node(node->left);
            }
            cout << ")(";
            if (node->right != nullptr) {
                print_node(node->right);
            }
            cout << ")";
        }
    }
    void delete_node(Node* node) {
        if (node->left != nullptr) {
            delete_node(node->left);
        }
        if (node->right != nullptr) {
            delete_node(node->right);
        }
        delete node;
    }
    void read_node(Node** node, string str, bool& flag) {
        if (str != "()") {
            *node = new Node;
            int i = 1;
            while (str[i] == ' ')i++;
            if (str[i] != ')') {
                int new_data = str[i] - '0';
                i++;
                while (str[i] != '(' && str[i] != ' ' && str[i] != ')' && str[i] != '\0') {
                    new_data *= 10;
                    new_data += str[i] - '0';
                    i++;
                }
                (*node)->data = new_data;
                while (str[i] != ')' && str[i] != '\0' && str[i] != '(') {
                    i++;
                }
                if (str[i] != ')') {
                    string left, right;
                    int sum = 0;
                    while (str[i] != '(') i++;
                    left += str[i];
                    sum++;
                    i++;
                    while (sum != 0) {
                        if (str[i] == '(')sum++;
                        if (str[i] == ')')sum--;
                        left += str[i];
                        i++;
                    }
                    read_node(&(*node)->left, left, flag);

                    while (str[i] != '(' && str[i] != ')') {
                        i++;
                    }
                    if (str[i] != ')') {
                        right += str[i];
                        sum++;
                        i++;
                        while (sum != 0) {
                            if (str[i] == '(')sum++;
                            if (str[i] == ')')sum--;
                            right += str[i];
                            i++;
                        }
                        read_node(&(*node)->right, right, flag);
                    }
                    while (str[i] != '(' && str[i] != ')' && str[i] != '\0') {
                        i++;
                    }
                    if (str[i] == '(') {
                        flag = 1;
                    }
                }
            }
        }
    }
    void round(Node* node, RB_Tree* tree) {
        tree->insert(node->data);
        if (node->left != nullptr || node->right != nullptr) {
            if (node->left != nullptr) {
                round(node->left, tree);
            }
            if (node->right != nullptr) {
                round(node->right, tree);
            }
        }
    }
public:
    Tree() {
    }
    Tree(int new_data) {
        root = new Node;
        root->data = new_data;
    }
    ~Tree() {
        if (root != nullptr) {
            delete_node(root);
            root = nullptr;
        }
    }
    void create_RB_Tree(RB_Tree* tree) {
        if (root != nullptr) {
            round(root, tree);
        }
    }
    void read_tree(string str) {
        bool flag = 0;
        read_node(&root, str, flag);
        int num_op = 0;
        int num_cl = 0;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '(') {
                num_op++;
            }
            if (str[i] == ')') {
                num_cl++;
            }
        }
        if (num_op != num_cl) {
            cout << "Error! Wrong brackets!\n";
            delete_tree();
        }
        else if (flag == 1) {
            cout << "Error! This tree isn't binary\n";
            delete_tree();
        }
    }
    void print_tree() {
        if (root != nullptr) {
            cout << "(";
            print_node(root);
            cout << ")\n\n";
        }
        else cout << "Tree is empty\n";
    }
    void delete_tree() {
        if (root != nullptr) {
            delete_node(root);
            root = nullptr;
        }
        else cout << "Tree is empty\n";
    }
};

int main()
{
    string line;
    ifstream in("file.TXT");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            std::cout << line << std::endl;
        }
    }
    in.close();
    Tree tree1;
    tree1.read_tree(line);
    tree1.print_tree();

    RB_Tree tree;

    tree1.create_RB_Tree(&tree);
    tree.print_tree();

    int n;
    char b;
    while (true) {
        cout << "Choose the option:\n1.Insert the element\n2.Delete the element\n3.Find element\n4.Print tree all\n";
        cin >> n;
        if (n == 1) {
                cout << "Enter the element: ";
                cin >> n;
                tree.insert(n);
                tree.print_tree();
                cout << "\n\n";
        }
        else if (n == 2) {
            cout << "Enter the element: ";
            cin >> n;
            tree.delete_n(n);
            tree.print_tree();
            cout << "\n\n";
        }
        else if (n == 3) {
            cout << "Enter the element: ";
            cin >> n;
            tree.find(n);
            cout << "\n\n";
        }
        else if (n == 4) {
            tree.print_tree_all();
            cout << "\n\n";
        }
        else {
            cout << "Error! Choose the correct option\n";
        }
    }
}