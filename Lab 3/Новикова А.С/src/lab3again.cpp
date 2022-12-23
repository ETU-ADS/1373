#include "binaryTree.h"
#include "AVLTree.h"
#include "stack.h"
#include "queue.h"
#include <fstream>

int main()
{
	std::string filename;
	std::cout << "Enter the name of the file: ";
	std::getline(std::cin, filename);

	if (filename == "")
	{
		system("pause");
		return 0;
	}
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "Failed to open file." << std::endl;
		system("pause");
		return 0;
	}
	std::string str;
	std::getline(file, str);
	file.close();

	BinaryTree tree;
	tree.parcing(str);

	int toMenu = 5;
	bool flag = true;

	do
	{
		system("cls");

		std::cout << "Current tree:\n";
		tree.print();
		std::cout << std::endl;

		int choice = 5;
		std::cout << "*-*-*-*-MENU-*-*-*-*\n1.Print the tree\n2.Insert an element\n3.Clear the tree\n4.Make an AVL tree\nYour choice: ";
		std::cin >> choice;
		while (!(choice >= 1 && choice <= 4))
		{
			std::cout << "Wrong number! Try again: ";
			std::cin >> choice;
		}
		switch (choice)
		{
		case 1:
		{
			std::cout << tree;
			break;
		}
		case 2:
		{
			int value = 0;
			std::cout << "Enter the element you want to insert: ";
			std::cin >> value;
			tree.insert(value);
			break;
		}
		case 3:
		{
			tree.clear();
			break;
		}
		case 4:
		{
			flag = false;
			toMenu = 2;
			break;
		}
		}
		if (flag == true)
		{
			std::cout << "\nDo you want to go back to the menu?\n1.Yes\n2.No\nYour choice: ";
			std::cin >> toMenu;
		}
	} while (toMenu == 1 && flag == true);

	if (flag == false)
	{
		AVLTree avltree;
		tree.createAVL(&avltree, tree.getRoot());

		do
		{
			system("cls");

			std::cout << "Current tree:\n";
			avltree.print();
			std::cout << std::endl;

			int choice = 5;
			std::cout << "*-*-*-*-MENU-*-*-*-*\n1.Insert an element\n2.Remove an element\n3.Find an element\n4.Preorder print\n5.Inorder print\n6.Postorder print\n7.BFS print\n8.Clear the tree\nYour choice: ";
			std::cin >> choice;
			while (!(choice >= 1 && choice <= 8))
			{
				std::cout << "Wrong number! Try again: ";
				std::cin >> choice;
			}
			switch (choice)
			{
			case 1:
			{
				int value = 0;
				std::cout << "Enter the element you want to insert: ";
				std::cin >> value;
				avltree.insert(value);
				break;
			}
			case 2:
			{
				int value = 0;
				std::cout << "Enter the element you want to remove: ";
				std::cin >> value;
				avltree.remove(value);
				break;
			}
			case 3:
			{
				int value = 0;
				std::cout << "Enter the element you want to find: ";
				std::cin >> value;
				avltree.find(value);
				break;
			}
			case 4:
			{
				avltree.preorderDFS();
				break;
			}
			case 5:
			{
				avltree.inorderDFS();
				break;
			}
			case 6:
			{
				avltree.postorderDFS();
				break;
			}
			case 7:
			{
				avltree.BFS();
				break;
			}
			case 8:
			{
				avltree.clear();
				break;
			}
			}
			std::cout << "\nDo you want to go back to the menu?\n1.Yes\n2.No\nYour choice: ";
			std::cin >> toMenu;
		} while (toMenu == 1);
	}
	system("cls");
	std::cout << "Thanks for using the program!" << std::endl;

	system("pause");
	return 0;
}