#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

struct BinNode {
	int data;
	struct BinNode* left;
	struct BinNode* right;
	int brackets;
	BinNode(int val)
	{
		data = val;
		left = right = NULL;
	}
};

BinNode* generateBinaryTree(string s, int* start)
{
	if (s.size() == 0 || *start >= s.size())
		return NULL;
    if(s[*start] == '(' )
        *start = *start + 1;
//    else{
//        cout<<"WRONG BRACKETS"<<endl;
//        return NULL;
//    }
 // 845
	int num = 0;
	while (*start < s.size() && s[*start] != ' '
		&& s[*start] != ')') {
		int num_here = (int)(s[*start] - '0');

		if(s[*start+1] == ' ' && s[*start+2] != '(')
        {
            cout<<"WRONG LINE"<<endl;
            exit(1);
        }
		if(isdigit(num_here) == true || num_here<0 || num_here>9){
            cout<<"WRONG LINE"<<endl;
            exit(1);
        }
		num = num * 10 + num_here;
		*start = *start + 1;
	}

//    if(s[*start+1] != ' ' || s[*start+1] != ')')//after num
//        {
//            cout<<"WRONG LINE"<<endl;
//            exit(1);
//        }
    *start = *start + 1;//space
	struct BinNode* root = NULL;
	if(num > 0)
        root = new BinNode(num);

	// left
	if (*start < s.size() && s[*start] == '(') {
		*start = *start + 1;
		root->left = generateBinaryTree(s, start);
        if(*start < s.size() && s[*start] ==' ')
            *start = *start + 1;
	}
	if (*start < s.size() && s[*start] == ')')
	{
        *start = *start + 1;
        if(*start < s.size() && s[*start] ==' ')
            *start = *start + 1;
        return root;
	}
	// right
	if (*start < s.size() && s[*start] == '(') {
		*start = *start + 1;
		root->right = generateBinaryTree(s, start);
        if( *start < s.size() && s[*start] ==' ')
            *start = *start + 1;
	}
	if (*start < s.size() && s[*start] == ')'){
		*start = *start + 1;
        if(*start < s.size() && s[*start] ==' ')
            *start = *start + 1;
	}
	return root;
}


void preorder(string prefix, BinNode* root, bool isLeft)
{
    if (root != nullptr)
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "L--");
        cout << root->data << endl;
        preorder(prefix + (isLeft ? "|   " : "    "), root->right, true);
        preorder(prefix + (isLeft ? "|   " : "    "), root->left, false);
    }
}

class Node
{
	public:
        int key;
        Node *left;
        Node *right;
        int height;
};

int height(Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b)
{
	return (a > b)? a : b;
}

Node* newNode(int key)
{
	Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;

	return(node);
}

Node *rightRotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left),
					height(y->right)) + 1;
	x->height = max(height(x->left),
					height(x->right)) + 1;

	// Return new root
	return x;
}

Node *leftRotate(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left),
					height(x->right)) + 1;
	y->height = max(height(y->left),
					height(y->right)) + 1;

	// Return new root
	return y;
}

// Get Balance factor of node N
int getBalance(Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

Node* insert(Node* node, int key)
{
	if (node == NULL)
		return(newNode(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;

	node->height = 1 + max(height(node->left),
						height(node->right));


	int balance = getBalance(node);
	// If this node becomes unbalanced, then
	// there are 4 cases

	// Left Left Case
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}


Node* minValueNode(Node* node)
{
    Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

Node* deleteNode(Node* root, int deleteValue)
{

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if ( deleteValue < root->key )
        root->left = deleteNode(root->left, deleteValue);

    // If the key to be deleted is greater
    // than the root's key, then it lies
    // in right subtree
    else if( deleteValue > root->key )
        root->right = deleteNode(root->right, deleteValue);

    // if key is same as root's key, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child

        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            Node *temp;
            if(root->left == NULL)
                temp = root->right;
            else
                temp = root->left;

//            Node *temp = root->left ?
//                         root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of
                           // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);

            // Copy the inorder successor's
            // data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }


    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left),
                           height(root->right));

    int balance = getBalance(root);

    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* find(int x, Node* root)
{
    if (root == nullptr)
        return root;
    else if (root->key == x)
        return root;
    else if (x < root->key)
        return find(x, root->left);
    else
        return find(x, root->right);
}

void storeNodeValues(BinNode* root, vector<int> &node_values)
  {
    if(root!=NULL)
    {
      // in-order
      storeNodeValues(root->left, node_values);
      node_values.push_back(root->data);
      storeNodeValues(root->right, node_values);
    }
    return;
  }
  void preorderAvl(string prefix, Node *root, bool isLeft)
{
	if (root != nullptr)
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "L--");
        cout << root->key << endl;
        preorderAvl(prefix + (isLeft ? "|   " : "    "), root->right, true);
        preorderAvl(prefix + (isLeft ? "|   " : "    "), root->left, false);
    }
}

void traversal(Node *root, int c)
{
    if(c == 1){
        if (root == NULL)
            return;
        cout << root->key << " ";
        traversal(root->left,c);
        traversal(root->right,c);
    }
    if(c == 2){
        if (root == NULL)
            return;
        traversal(root->left,c);
        cout << root->key << " ";
        traversal(root->right,c);
    }
    if(c == 3){
        if (root == NULL)
            return;
        traversal(root->left,c);
        traversal(root->right,c);
        cout << root->key << " ";
    }
    if(c == 4){
        queue <Node*> q;
        q.push(root);
        Node* temp = root;
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            cout << temp->key << " ";
            if (temp->left != nullptr)
                q.push(temp->left);
            if (temp->right != nullptr)
                q.push(temp->right);
        }
    }
}

int main()
{
    ifstream file;
    file.open("file_brackets.txt");
    string s;
    if ( file.is_open() ) {
        getline(file, s);
        cout << s << endl;
    }
	//string s = "(4 (2 (3) (1 (77))) (6 (5)))";

	int bracketCount = 0;
	for (int i=0; i<s.length(); i++)
    {
        if(i+1<s.length()){
            if(s[i] == ')'){
                bracketCount-=1;
                if(s[i+1]!=' ' && s[i+1]!=')')
                    cout<<"WRONG LINE"<<endl;
            }
            else if(s[i] == '('){
                bracketCount+=1;
                if(isdigit(s.at(i+1))!=true)
                    cout<<"WRONG LINE (numbers)"<<endl;
            }
            else if(s[i] == ' '){
               if(s[i+1]!='(')
                    cout<<"WRONG LINE"<<endl;
            }
        }
        else{
            if(s[i] != ')')
                cout<<"WRONG LINE"<<endl;
            else
                bracketCount-=1;
        }
    }
    if(bracketCount!=0)
        cout<<"WRONG LINE!"<<endl;


	int start = 0;
	BinNode* root = generateBinaryTree(s, &start);

    cout<<"Binary tree"<<endl;
	preorder("",root, true);

	cout<<"AVL TREE"<<endl;
    vector<int> node_values;

    Node *avlRoot = NULL;
    storeNodeValues(root, node_values);
    for(int i=0 ; i<node_values.size() ; i++)
        avlRoot = insert(avlRoot, node_values[i]);
    preorderAvl("",avlRoot, true);

    int c = 0;
    while (true)
    {
        cout << "\nChoose function: 1 - traversal; 2 - add element; 3 - delete element; 4 - search element; 9 - exit "<<endl;
        cin >> c;
        if (c == 9)
            break;
        switch (c)
        {
        case 1:
        {
            cout << "1 - Direct; 2 - Centered; 3 - Reverse; 4 - Breadth first: "<<endl;
            cin >> c;
            if (c<1 || c>4)
            {
                cout << "Wrong number!" << endl;
                break;
            }
            traversal(avlRoot,c);
            break;
        }
        case 2:
        {
            cout << "Enter value to add: ";
            cin >> c;
            avlRoot = insert(avlRoot, c);
            preorderAvl("",avlRoot, false);
            break;
        }
        case 3:
        {
            cout << "Enter value to delete: ";
            cin >> c;
            avlRoot = deleteNode(avlRoot, c);
            preorderAvl("",avlRoot, false);
            break;
        }
        case 4:
        {
            cout << "Enter value to search: ";
            cin >> c;
            if (find(c, avlRoot) == nullptr)
                cout << c << " was not found!" <<endl;
            else
                cout << c << " was found!" <<endl;
            break;
        }
        default:
        {
            cout << "Wrong number!" << std::endl;
            break;
        }
        }
    }
	return 0;
}
