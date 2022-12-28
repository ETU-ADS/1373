#include <iostream>
#include <string>
#include <queue>
#include <fstream> 

using namespace std;

struct treeNode {
	int field;
	struct treeNode* left;
	struct treeNode* right;
	int height;
};
struct steck
{
	int num;
	steck* next;
};
struct Trunk
{
	Trunk* prev;
	string str;

	Trunk(Trunk* prev, string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

void showTrunks(Trunk* p)
{
	if (p == nullptr)
	{
		return;
	}
	showTrunks(p->prev);
	cout << p->str;
}
//Прямой обход
void pre_print(treeNode* tree) {
	if (tree != NULL) {

		cout << tree->field << " ";
		pre_print(tree->left);
		pre_print(tree->right);
	}
	//else
		//cout << "\nДерево пусто!" << endl;
}
//Концевой обход
void in_print(treeNode* tree) {
	if (tree != NULL) {

		in_print(tree->left);
		cout << tree->field << " ";
		in_print(tree->right);
	}
	//else
		//cout << "\nДерево пусто!" << endl;
}
//Обратный обход
void post_print(treeNode* tree) {
	if (tree != NULL) {

		post_print(tree->left);
		post_print(tree->right);
		cout << tree->field << " ";
	}
	//else
		//cout << "\nДерево пусто!" << endl;
}
void draw(treeNode* tree)
{
	if (tree != NULL)
		cout << tree->field << " ";
}



void add_node(int x, treeNode*& tree)
{

	if (tree == NULL)
	{
		tree = new treeNode;
		tree->field = x;
		tree->left = tree->right = NULL;
		tree->height = 0;
	} 

		
	else if (tree->right != NULL && tree->left != NULL && tree->left->left != NULL
		&& tree->left->right != NULL && tree->right->right == NULL) add_node(x, tree->right);

	else if (tree->right != NULL && tree->left != NULL) add_node(x, tree->left);
	else if (tree->left != NULL && tree->right == NULL )
	{
		tree->right = new treeNode;
		tree->right->left = tree->right->right = NULL;
		tree->right->field = x;
	} 
	else
	{
		tree->left = new treeNode;
		tree->left->left = tree->left->right = NULL;
		tree->left->field = x;
	}
}

void delete_node(treeNode* tree)
{
	if (tree != NULL) {
		delete_node(tree->left);
		delete_node(tree->right);
		free (tree);
	}
}

void printTree(treeNode* tree, Trunk* prev, bool isleft)
{
	if (tree == NULL)
		return;

	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);

	printTree(tree->right, trunk, true);

	if (!prev) {
		trunk->str = "———";
	}
	else if (isleft)
	{
		trunk->str = ".———";
		prev_str = "   |";
	}
	else {
		trunk->str = "`———";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	cout << " " << tree->field << endl;

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

	printTree(tree->left, trunk, false);

}


void menu_start()

	{
		cout << "\n1 - Дерево\n";
		cout << "2 - Скобочная запись\n";
		cout << "3 - АВЛ-дерево\n";
		cout << "0 - Выход\n";
	}

void menu_AVL()
{
	cout << "\nАВЛ Дерево" << endl;

	cout << "1 - Вставить элементы" << endl;
	cout << "2 - Найти минимальный элемент" << endl;
	cout << "3 - Найти максимальный элемент" << endl;
	cout << "4 - Поиск по значению" << endl;
	cout << "5 - Удалить элемент" << endl;
	cout << "6 - Левосторонний обход" << endl;
	cout << "7 - Концевой обход" << endl;
	cout << "8 - Обраный обход и обход в ширину" << endl;
	cout << "9 - Показать высоту дерева" << endl;
	cout << "0 - Выход" << endl;
}

//Высота
int t_height(treeNode* p)
{
	int t;
	if (p == NULL)
	{
		return -1;
	}
	else
	{
		t = p->height;
		return t;
	}
}

treeNode* srl(treeNode*& p1)
{
	treeNode* p2;
	p2 = p1->left;
	p1->left = p2->right;
	p2->right = p1;
	p1->height = max(t_height(p1->left), t_height(p1->right)) + 1;
	p2->height = max(t_height(p2->left), p1->height) + 1;
	return p2;
}

treeNode* srr(treeNode*& p1)
{
	treeNode* p2;
	p2 = p1->right;
	p1->right = p2->left;
	p2->left = p1;
	p1->height = max(t_height(p1->left), t_height(p1->right)) + 1;
	p2->height = max(t_height(p2->right), p1->height) + 1;
	return p2;
}

treeNode* drl(treeNode*& p1)
{
	p1->left = srr(p1->left);
	return srl(p1);
}

treeNode* drr(treeNode*& p1)
{
	p1->right = srl(p1->right);
	return srr(p1);
}

// Добавление в АВЛ - дерево
void insert(int x, treeNode*& p)  
{
	if (p == NULL)
	{
		p = new treeNode;
		p->field = x;
		p->left = NULL;
		p->right = NULL;
		p->height = 0;
		if (p == NULL)
		{
			cout << "Out of Space\n" << endl;
		}
	}
	else
	{
		if (x < p->field)
		{
			insert(x, p->left);
			if ((t_height(p->left) - t_height(p->right)) == 2)
			{
				if (x < p->left->field)
				{
					p = srl(p);
				}
				else
				{
					p = drl(p);
				}
			}
		}
		else if (x > p->field)
		{
			insert(x, p->right);
			if ((t_height(p->right) - t_height(p->left)) == 2)
			{
				if (x > p->right->field)
				{
					p = srr(p);
				}
				else
				{
					p = drr(p);
				}
			}
		}
		else
		{
			cout << "Элемент существует\n" << endl;
		}
	}
	int m, n, d;
	m = t_height(p->left);
	n = t_height(p->right);
	d = max(m, n);
	p->height = d + 1;
}
// Найти наименьший корень
treeNode * findmin(treeNode *p)
{
	if (p == NULL)
	{
		cout << "В дереве нет элементов\n" << endl;
		return p;
	}
	else
	{
		while (p->left != NULL)
		{
			p = p->left;
			//return p;
		}
		return p;
	}
} 
//Найти наибольший корень
treeNode* findmax(treeNode* p)
{
	if (p == NULL)
	{
		cout << "В дереве нет элементов\n" << endl;
		return p;
	}
	else
	{
		while (p->right != NULL)
		{
			p = p->right;
			//return p;
		}
		return p;
	}
}
//Найти элемент
void find(int x, treeNode*& p)
{
	if (p == NULL)
	{
		system("CLS");
		cout << "Простите, но такого элемента нет\n" << endl;
	}
	else
	{
		if (x < p->field)
		{
			find(x, p->left);
		}
		else
		{
			if (x > p->field)
			{
				find(x, p->right);
			}
			else
			{
				system("CLS");
				cout << "Элемент, который вы искали есть в дереве!\n" << endl;
				cout << "Ваш элемент: " << p->field << endl;
			}
		}
	}
}
//Удаление минимального элемента
int deletemin(treeNode*& p)
{
	int c;
	cout << "Выбрано удаление минимального значения\n" << endl;
	if (p->left == NULL)
	{
		c = p->field;
		p = p->right;
		return c;
	}
	else
	{
		c = deletemin(p->left);
		return c;
	}
}
//Удаление элемента
void del(int x, treeNode*& p)
{
	treeNode* d;
	if (p == NULL)
	{
		cout << "Простите, но такого элемента нет\n" << endl;
	}
	else if (x < p->field)
	{
		del(x, p->left);
	}
	else if (x > p->field)
	{
		del(x, p->right);
	}
	else if ((p->left == NULL) && (p->right == NULL))
	{
		d = p;
		free(d);
		p = NULL;
		cout << "Элемент удален\n" << endl;
	}
	else if (p->left == NULL)
	{
		d = p;
		p = p->right;
		free(d);
		cout << "Элемент удален\n" << endl;
	}
	else if (p->right == NULL)
	{
		d = p;
		p = p->left;
		free(d);
		cout << "Элемент удален\n" << endl;
	}
	else
	{
		p->field = deletemin(p->right);
	}
}

int max(int val1, int val2)
{
	return ((val1 > val2) ? val1 : val2);
}

void breadth_print(treeNode* root)
{
	queue<treeNode*> q;
	q.push(root);
	treeNode* node;
	while (!q.empty()) {
		node = q.front();
		q.pop();
		draw(node);
		if (node->left)
			q.push(node->left);
		if (node->right)
			q.push(node->right);
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	
	int k = 0, l = 0, m = 0, num = 0;
	int choice, sol;
	string path = "Test.txt", str;
	char ch, line[60];

	menu_start();
	do
	{
		cout << "Ответ пользователя: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			treeNode* Tree = NULL;
			system("CLS");
			for (int i = 0; i < 10; i++)
				add_node(i, Tree);

			

			cout << endl << endl;
			printTree(Tree, nullptr, false);
			pre_print(Tree);
			delete_node(Tree);
			menu_start();
			break;
		}
		case 2:
		{
			system("CLS");
			treeNode* Tree = NULL;
			ifstream in;
			in.open(path);
			if (!in.is_open())
			{
				cout << "Ошибка открытия файла!" << endl << endl;
			}
			else
			{
				while (in.get(ch))
				{
					cout << ch;
					line[k++] = ch;
				}
			}
			in.close();
			cout << '\n';
			for (int i = 0; i < k; i++)
			{
				if (line[0] != '(')
					cout << "Ошибка выражения! Убедитесь что запись начинается с (...." << endl;
				if (line[i] == '(')
				{
					l++;
					m = l;
				}


				else if (line[i] >= '0' && line[i] <= '9')
				{
					str = str + line[i];
				}
				else if ((line[i] == ' ' || line[i] == ')') && str != "")
				{
					
					for (int i = 0; i < str.length(); i++)
					{
						num = num * 10 + str[i] - 0x30;
					}

					if (line[i] == ')')
					{
						l--;
					}
					if (Tree == NULL)
						add_node(num, Tree);
					else if (l > 1)
						add_node(num, Tree->left);
					else
						add_node(num, Tree->right);
					str = ""; num = 0;
					
				}
				else if (line[i] == ')')
				{
					l--;
				}
			}
			if (l != 0)
				cout << "\n\nОшибка выражения. Убедитесь в правильности..." << endl;
			else
			{ 
				printTree(Tree, nullptr, false);
				delete_node(Tree);
			}
			menu_start();
			break;
		}
		case 3:
		{

			treeNode* root = NULL, * min, *max;
			int a = -1, find_el, del_el;

			system("CLS");
			menu_AVL();
			do
			{
				cout << "Ответ пользователя: ";
				cin >> sol;

				switch (sol)
				{
				case 1:
					cout << "\nДобавление нового узла" << endl;
					cout << "0 - Прекратить ввод\n" << endl;
					cout << "Введите элемент: ";
					cin >> a;
					while (a != 0)
					{
						insert(a, root);
						cin >> a;
					}
					system("CLS");
					cout << "\nНовые элементы добавлены успешно\n" << endl;
					printTree(root, nullptr, false);
					menu_AVL();
					break;
				case 2:
					if (root != NULL)
					{
						min = findmin(root);
						system("CLS");
						cout << "\nМинимальный элемент в дереве: " << min->field << endl;
						printTree(root, nullptr, false);
						menu_AVL();
					}
					else
					{
						system("CLS");
						cout << "\nДерево пусто!" << endl;
						menu_AVL();
					}
					break;
				case 3:
					if (root != NULL)
					{
						max = findmax(root);
						system("CLS");
						cout << "\nМаксимальный элемент в дереве: " << max->field << endl;
						printTree(root, nullptr, false);
						menu_AVL();
					}
					else
					{
						system("CLS");
						cout << "\nДерево пусто!" << endl;
						menu_AVL();
					}
					break;
				case 4:
					
					if (root != NULL)
					{
						cout << "\nВведите искомый элемент: ";
						cin >> find_el;
						find(find_el, root);
						printTree(root, nullptr, false);
						menu_AVL();
					}
					else
					{
						system("CLS");
						cout << "\nДерево пусто!" << endl;
						menu_AVL();
					}
					
					break;
				case 5:
					if (root != NULL) 
					{
						cout << "\nКакой узел удалять? : ";
						cin >> del_el;
						del(del_el, root);
						system("CLS");
						in_print(root);
						cout << endl;
						printTree(root, nullptr, false);
						menu_AVL();
					}	
					else
					{
					system("CLS");
					cout << "\nДерево пусто!" << endl;
					menu_AVL();
					}
					
					break;
				case 6:
					system("CLS");
					cout << "\nЛевосторонний обход" << endl;
					pre_print(root);
					cout << endl;
					printTree(root, nullptr, false);
					menu_AVL();
					break;
				case 7:
					system("CLS");
					cout << "\nКонцевой обход" << endl;
					in_print(root);
					cout << endl;
					printTree(root, nullptr, false);
					menu_AVL();
					break;
				case 8:
					system("CLS");
					cout << "\nОбраный обход и обход в ширину" << endl;
					post_print(root);
					cout << endl;
					breadth_print(root);
					cout << endl;
					printTree(root, nullptr, false);
					menu_AVL();
					break;
				case 9:
					system("CLS");
					cout << "\nВысота\n" << endl;
					cout << "Дерево имеет высоту: " << t_height(root) << endl;
					printTree(root, nullptr, false);
					menu_AVL();

					break;
				case 0:
				{
					menu_start();
					break;
				}
				default: cout << "Некорректный ввод. Используйте цифры 1-9 для управления и 0 для выхода\n" << endl;

				}
			} while (sol != 0);
			system("CLS");
			menu_start();
			break;
		}
		case 0:
		{
			exit(0);
		}
		default: cout << "Некорректный ввод. Используйте цифры 1-3 для управления и 0 для выхода\n" << endl;
		}
	} while (choice != 0);

	return 0;
}