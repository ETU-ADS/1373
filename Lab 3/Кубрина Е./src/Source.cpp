#include "Header.h"



int main() {

	_Tree t;

	t.ReadTreeFromFile();
	cout << "Your tree: ";
	t.Print(t.getRoot());
	cout << endl<<"Your AVL-Tree: ";
	AVLTree al;
	al.CreateTree(&t);
	al.print();

	//пример работы программы с защиты лабораторной работы
	/*cout<<"\n\\\\\\\\\\\\\\\\\\\\\\"<<endl;
	for (int i = 16; i < 31; i++) {
		al.push(i);
	}
	cout << "Preorder: ";
	al.itPreOrder();
	cout << endl;
	cout << "Inorder: ";
	al.itInOrder();
	cout << endl;
	cout << "Postrder: ";
	al.itPostOrder();
	cout << endl;
	cout << "Levelrder: ";
	al.levelOrder();
	cout << endl;

	al.remote(8);
	al.remote(15);
	al.remote(2);
	al.remote(3);
	cout << endl;
	cout << "After emoving elements (8, 15, 2, 3)" << endl;
	al.itPreOrder();
	cout << endl;*/
	int k = 0;
	while (k!=8) {
		printMenu();
		cout << endl;
		cout << "Select operation: ";
		cin >> k;
		Menu(al, k);
	}

	system("pause");
	return 0;
}

//отрисовка меню
void printMenu() {
	cout << endl;
	cout << "1.Add element to AVL-Tree."<<endl;
	cout << "2.Remove element from tree."<<endl;
	cout << "3.Preorder (print AVL-Tree)."<<endl;
	cout << "4.Inorder (print AVL-Tree)."<<endl;
	cout << "5.Postorder (print AVL-Tree)."<<endl;
	cout << "6.Levelorder (print AVL-Tree)."<<endl;
	cout << "7.Exit."<<endl;
}

//меню
void Menu(AVLTree &al, int k) {
	int temp;
	switch (k)
	{
	case menu::Push:
		cout << "Enter element: ";
		cin >> temp;
		al.push(temp);
		break;
	case menu::Delete:
		cout << "Enter element: ";
		cin >> temp;
		al.remote(temp);
		break;
	case menu::Preorder:
		cout << "Preorder: ";
		al.itPreOrder();
		break;
	case menu::Inorder:
		cout << "Inorder: ";
		al.itInOrder();
		break;
	case menu::Postorder:
		cout << "Postrder: ";
		al.itPostOrder();
		break;
	case menu::Levelorder:
		cout << "Levelrder: ";
		al.levelOrder();
		break;
	case menu::Exit:
		cout << "Exit";
		exit(0);
		break;
	default:
		cout << "Error: Operation does not exist!"<<endl;
		cout << "Try again...";
		break;
	}
	cout << endl;
}