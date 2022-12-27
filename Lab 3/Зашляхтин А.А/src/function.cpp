#include "definition.h"

BinaryTree::BinaryTree()
{
    root = NULL;
}
BinaryTree::~BinaryTree()
{
    while (true)
    {
        if (root == NULL)
            break;
        if (root->leftChild != nullptr)
        {
            while (root->leftChild != nullptr)
            {
                root = root->leftChild;
            }
        }
        if (root->rightChild != nullptr)
        {
            while (root->rightChild != nullptr)
            {
                root = root->rightChild;
            }
        }
        if (root->leftChild == nullptr && root->rightChild == nullptr && root->parent != nullptr)
        {
            bool leftOrRight;
            element* t;
            t = root->parent;
            if (t->leftChild == root)
                leftOrRight = 1;
            if (t->rightChild == root)
                leftOrRight = 0;
            delete root;
            root = t;
            if (leftOrRight == 0)
                root->rightChild = nullptr;
            else
                root->leftChild = nullptr;

        }
        if (root->parent == nullptr)
        {
            delete root;
            break;
        }

    }
}
void BinaryTree::parsing(char* buffer, int& start, int size)
{
    if (buffer[start++] == '(')
    {
        if (buffer[start] != ')')
        {
            if (root == NULL)
            {
                root = new element;
                root->parent = nullptr;
                root->leftChild = nullptr;
                root->rightChild = nullptr;
                root->data = buffer[start++] - 48;
                if (buffer[start] != '(' && buffer[start] != ')')
                {
                    root->data *= 10;
                    root->data += buffer[start++] - 48;
                }
            }
            else
            {
                root->data = buffer[start++] - 48;
                if (buffer[start] != '(' && buffer[start] != ')')
                {
                    root->data *= 10;
                    root->data += buffer[start++] - 48;
                }
            }
                

        }
        else
        {
            ++start;
        }
        if (buffer[start] == '(' && buffer[++start] != ')')
        {
            --start;
            root->leftChild = new element;
            root->leftChild->leftChild = nullptr;
            root->leftChild->rightChild = nullptr;
            root->leftChild->parent = root;
            root = root->leftChild;
            parsing(buffer, start, size);
            ++start;
            root = root->parent;

        }
        if (buffer[start - 1] == '(' && buffer[start] == ')')
        {
            if (buffer[start + 1] == ')')
                ++start;
            ++start;
        }

        if (buffer[start] != ')')
        {
            if (buffer[start] == '(' && buffer[start + 1] != ')')
            {
                root->rightChild = new element;
                root->rightChild->leftChild = nullptr;
                root->rightChild->rightChild = nullptr;
                root->rightChild->parent = root;
                root = root->rightChild;
                parsing(buffer, start, size);
                ++start;
                root = root->parent;
            }
            else
            {
                if (buffer[start] == '0' || buffer[start] == '1' || buffer[start] == '2' || buffer[start] == '3'
                    || buffer[start] == '4' || buffer[start] == '5' || buffer[start] == '6'
                    || buffer[start] == '7' || buffer[start] == '8' || buffer[start] == '9')
                {
                    std::cout << "input error" << std::endl;
                    exit(-1);
                }
                else
                {
                    ++start;
                    ++start;
                }
            }
        }
    }
}
void BinaryTree::parsingTree(BinaryTree& test)
{
    char buffer[200];
    std::ifstream fin("text.txt");
    if (!fin.is_open())
    {
        std::cout << "error";
    }
    fin.getline(buffer, 200);
    fin.close();
    int start = 0;
    int count1 = 0;
    int count2 = 0;
    int size = 0;
    bool error = 0;
    for (int i = 0; i < 200; ++i)
    {
        if (buffer[i] == '(')
            ++count1;
        else if (buffer[i] == ')')
            ++count2;
        if (buffer[i] != '(' && buffer[i] != ')' && buffer[i] != '0' && buffer[i] != '1' && buffer[i] != '2' && buffer[i] != '3' && buffer[i] != '4' && buffer[i] != '5' && buffer[i] != '6' && buffer[i] != '7' && buffer[i] != '8' && buffer[i] != '9')
            error = 1;
        if (buffer[i] != '\0')
        {
            ++size;
        }
        else
        {
            --size;
            break;
        }

    }
    if (count1 != count2)
    {
        error = 1;
    }
    test.parsing(buffer, start, size);
    if (size != start)
    {
        std::cout << "input error" << std::endl;
        exit(-1);
    }
}
void BinaryTree::DFS(int store[], int& index)
{
    if (root != NULL)
    {
        std::cout << root->data << ' ';
        store[index++] = root->data;
    }
    if (root->leftChild != NULL)
    {
        root = root->leftChild;
        DFS(store, index);
        root = root->parent;
    }
    if (root->rightChild != NULL)
    {
        root = root->rightChild;
        DFS(store, index);
        root = root->parent;
    }
}

AVL::AVL()
{
    root = NULL;
}
AVL::~AVL()
{
    while (true)
    {
        if (root == NULL)
            break;
        if (root->left != nullptr)
        {
            while (root->left != nullptr)
            {
                root = root->left;
            }
        }
        if (root->right != nullptr)
        {
            while (root->right != nullptr)
            {
                root = root->right;
            }
        }
        if (root->left == nullptr && root->right == nullptr && root->parent != nullptr)
        {
            bool leftOrRight = 0;
            AVLtree* t;
            t = root->parent;
            if (t->left == root)
                leftOrRight = 1;
            if (t->right == root)
                leftOrRight = 0;
            delete root;
            root = t;
            if (leftOrRight == 0)
                root->right = nullptr;
            else
                root->left = nullptr;

        }
        if (root->parent == nullptr)
        {
            delete root;
            break;
        }

    }
}
AVLtree* AVL::returnroot()
{
    return root;
}
int AVL::balance(AVLtree* var)
{
    if (var->left == NULL && var->right == NULL)
        return 0;
    else if (var->left == NULL)
        return var->right->height;
    else if (var->right == NULL)
        return (0 - var->left->height);
    return var->right->height - var->left->height;
}
void AVL::RotateRight(AVLtree* rotating)
{
    AVLtree* temp = rotating->left;
    rotating->left = temp->right;
    if (temp->right != NULL)
        temp->right->parent = rotating;
    temp->parent = rotating->parent;
    if (rotating->parent == NULL)
        root = temp;
    else if (rotating == rotating->parent->right)
        rotating->parent->right = temp;
    else
        rotating->parent->left = temp;
    temp->right = rotating;
    rotating->parent = temp;
}
void AVL::RotateLeft(AVLtree* rotating)
{
    AVLtree* temp = rotating->right;
    rotating->right = temp->left;
    if (temp->left != NULL)
        temp->left->parent = rotating;
    temp->parent = rotating->parent;
    if (rotating->parent == NULL)
        root = temp;
    else if (rotating == rotating->parent->left)
        rotating->parent->left = temp;
    else
        rotating->parent->right = temp;
    temp->left = rotating;
    rotating->parent = temp;
}
void AVL::RotateLeftThenRight(AVLtree* rotating)
{
    RotateLeft(rotating->left);
    RotateRight(rotating);
}
void AVL::RotateRightThenLeft(AVLtree* rotating)
{
    RotateRight(rotating->right);
    RotateLeft(rotating);
}
int AVL::height(AVLtree* temp)
{
    if (temp)
    {
        int t1 = height(temp->left);
        int t2 = height(temp->right);
        if (t1 > t2)
        {
            temp->height = t1 + 1;
            return t1 + 1;
        }
        else
        {
            temp->height = t2 + 1;
            return t2 + 1;
        }
    }
    else
    {
        return 0;
    }
}
AVLtree* AVL::search(AVLtree* var, int value)
{
    AVLtree* temp = NULL;
    AVLtree* temp2 = var;
    while (temp2 != NULL && value != temp2->key)
    {
        temp = temp2;
        if (value < temp2->key)
            temp2 = temp2->left;
        else
            temp2 = temp2->right;
    }
    if (temp2 != NULL)
        temp = temp2;
    return temp;
}
void AVL::insert(AVLtree* var, int value)
{
    AVLtree* node = new AVLtree;
    node->key = value;
    AVLtree* temp = search(var, value);
    node->parent = temp;
    if (temp == NULL)
        root = node;
    else if (node->key < temp->key)
        temp->left = node;
    else
        temp->right = node;
}
void AVL::restoreBalance(AVLtree* var)
{
    int a = height(var);
    if (balance(var) < -1)
    {
        if (var->left->right == NULL)
            RotateRight(var);
        else if (var->left->left == NULL)
            RotateLeftThenRight(var);
        else if (var->left->left->height > var->left->right->height)
            RotateRight(var);
        else
            RotateLeftThenRight(var);
    }
    if (balance(var) > 1)
    {
        if (var->right->left == NULL)
            RotateLeft(var);
        else if (var->right->right == NULL)
            RotateRightThenLeft(var);
        else if (var->right->right->height > var->right->left->height)
            RotateLeft(var);
        else
            RotateRightThenLeft(var);
    }
}
void AVL::insertAVL(AVLtree* var, int value)
{
    insert(var, value);
    AVLtree* bal = var;
    while (bal != NULL) // проблема
    {
        restoreBalance(bal);
        if (bal->parent != NULL)
            bal = bal->parent;
        else
            break;
    }
    if(bal != NULL)
        bal = max(bal);
    while (bal != NULL) // проблема
    {
        restoreBalance(bal);
        if (bal->parent != NULL)
            bal = bal->parent;
        else
            break;
    }
    if (bal != NULL)
        bal = min(bal);
    while (bal != NULL) // проблема
    {
        restoreBalance(bal);
        bal = bal->parent;
    }
}
void AVL::restoreRoot(AVLtree* var)
{
    AVLtree* temp = var;
    while (var->parent != NULL)
    {
        var = var->parent;
    }
    root = temp;
}
AVLtree* AVL::min(AVLtree* var)
{
    AVLtree* temp = var;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}
AVLtree* AVL::max(AVLtree* var)
{
    AVLtree* temp = var;
    while (temp->right != NULL)
        temp = temp->right;
    return temp;
}
AVLtree* AVL::successor(AVLtree* var)
{
    if (var->right != NULL)
        return min(var->right);
    AVLtree* temp = var->parent;
    while (temp != NULL && var == temp->right)
    {
        var = temp;
        temp = temp->parent;
    }
    return temp;
}
void AVL::deleteElement(AVLtree* var, int value)
{
    AVLtree* temp2;
    AVLtree* temp3;
    AVLtree* temp = search(var, value);
    if (temp->key != value)
        std::cout << "Item was not found" << std::endl;
    if (temp->left == NULL || temp->right == NULL)
        temp2 = temp;
    else
        temp2 = successor(temp);
    if (temp2->left != NULL)
        temp3 = temp2->left;
    else
        temp3 = temp2->right;
    if (temp3 != NULL)
        temp3->parent = temp2->parent;
    if (temp2->parent == NULL)
        var = temp3;
    else if (temp2 == temp2->parent->left)
        temp2->parent->left = temp3;
    else
        temp2->parent->right = temp3;
    if (temp2 != temp)
    {
        temp->key = temp2->key;
        if (temp->right == temp2)
            temp->right = NULL;
    }
    AVLtree* bal = temp2->parent;
    temp2 = NULL;
    delete temp2;
    while (bal != NULL) // проблема
    {
        restoreBalance(bal);
        if (bal->parent != NULL)
            bal = bal->parent;
        else
            break;
    }
    if (bal != NULL)
        bal = max(bal);
    while (bal != NULL) // проблема
    {
        restoreBalance(bal);
        if (bal->parent != NULL)
            bal = bal->parent;
        else 
            break;
    }
    if(bal != NULL)
        bal = min(bal);
    while (bal != NULL) // проблема
    {
        restoreBalance(bal);
        bal = bal->parent;
    }

}

StackClass::StackClass()
{
    current = NULL;
    quantity = -1;
}
StackClass::~StackClass()
{
    while (current != NULL)
    {
        Stack* temp;
        temp = current->address;
        delete current;
        current = temp;
    }
}
bool StackClass::isEmpty()
{
    if (quantity >= 0)
        return 0;
    else if (quantity == -1)
        return 1;
}
AVLtree* StackClass::pop()
{
    AVLtree* tempAVL;
    Stack* temp;
    --quantity;
    temp = current->address;
    tempAVL = current->node;
    delete current;
    current = temp;
    return tempAVL;
} // problems!!!!!!!!
void StackClass::push(AVLtree* var)
{
    ++quantity;
    Stack* newElement = new Stack;
    newElement->address = current;
    current = newElement;
    current->node = var;
}
AVLtree* StackClass::peek()
{
    if (quantity == -1)
        return NULL;
    return current->node;
}
void visit(AVLtree* var)
{
    std::cout << var->key << ' ';
}
void directDFS(AVLtree* var)
{
    AVLtree* temp = var;
    if (temp == NULL)
        exit(0);
    StackClass stack;
    stack.push(temp);
    while (!stack.isEmpty())
    {
        temp = stack.pop();
        visit(temp);
        if (temp->right != NULL)
            stack.push(temp->right);
        if (temp->left != NULL)
            stack.push(temp->left);
    }
}
void centralizedDFS(AVLtree* var)
{
    AVLtree* temp = var;
    StackClass stack;
    while (!stack.isEmpty() || temp != NULL)
    {
        if (temp != NULL)
        {
            stack.push(temp);
            temp = temp->left;
        }
        else
        {
            temp = stack.pop();
            visit(temp);
            temp = temp->right;
        }
    }
}
void reverseDFS(AVLtree* var)
{
    AVLtree* temp = var;
    AVLtree* LastVisited = NULL;
    StackClass stack;
    while (!stack.isEmpty() || temp != NULL)
    {
        if (temp != NULL)
        {
            stack.push(temp);
            temp = temp->left;
        }
        else
        {
            AVLtree* peek = stack.peek();
            if (peek->right != NULL && LastVisited != peek->right)
                temp = peek->right;
            else
            {
                visit(peek);
                LastVisited = stack.pop();
            }
        }
    }
}

QueueClass::QueueClass()
{
    head = NULL;
    tail = NULL;
    quantity = 0;
}
QueueClass::~QueueClass()
{
    while (head != NULL)
    {
        Queue* temp;
        temp = head->prev;
        delete head;
        head = temp;
    }
}
bool QueueClass::isEmpty()
{
    if (quantity == 0)
        return 1;
    else
        return 0;
}
AVLtree* QueueClass::pop()
{
    AVLtree* tempAVL;
    Queue* temp;
    --quantity;
    tempAVL = head->node;
    temp = head;
    head = head->prev;
    delete temp;
    return tempAVL;

}
void QueueClass::push(AVLtree* var)
{
    ++quantity;
    Queue* newElement = new Queue;
    newElement->node = var;
    if (tail != NULL)
    {
        tail->prev = newElement;
        newElement->next = tail;
    }
    if (head == NULL)
        head = newElement;
    tail = newElement;
}
void BFS(AVLtree* var)
{
    AVLtree* temp = var;
    QueueClass queue;
    queue.push(temp);
    while (!queue.isEmpty())
    {
        temp = queue.pop();
        visit(temp);
        if (temp->left != NULL)
            queue.push(temp->left);
        if (temp->right != NULL)
            queue.push(temp->right);
    }
}