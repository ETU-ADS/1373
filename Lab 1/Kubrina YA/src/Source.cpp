#include "Header.h"
void SortStation(string math);
int what_sim(char t);
int _prior(char t);
int main() {

	/*
	_List <int>list(3, 5);
	list.printList();
	cout << endl << "----------------" << endl;
	list.printNode(1);
	cout << endl << "--------" << endl;
	cout << list.getSize();
	cout << endl << "--------" << endl;
	cout << list.is_empty();
	cout << endl << "--------" << endl;
	_List <int>list1;
	cout << list1.is_empty();
	cout << endl << "--------" << endl;
	list1.push_back(24);
	list1.printList();
	cout << endl << "--------" << endl;
	list.push_back(24);
	list.printList();
	cout << endl << "--------" << endl;
	list.push_front(1);
	list.printList();
	cout << endl << "--------" << endl;
	list.push(1, 100);
	list.printList();
	cout << endl << "--------" << endl;
	list.push(0, 200);
	list.printList();
	cout << endl << "--------" << endl;
	list.deleteNode(0);
	list.printList();
	cout << endl << "--------" << endl;
	list.deleteNode(1);
	list.printList();
	cout << endl << "--------" << endl;
	list.deleteNode(5);
	cout << endl;
	list.printList();
	cout << endl << "--------" << endl;
	list.deleteNode(4);
	list.printList();
	cout << endl << "--------" << endl;
	cout << list[0]->val <<endl;
	list.push_back(24);
	list.printList();
	cout << list.find(24)<<endl;

	
	//////////////////////////

	
	cout << "vector"<<endl;
	_vector <int> mas(10);
	mas[1] = 24;
	cout << mas[1] << endl;
	cout << endl << "--------------" << endl;
	cout << mas.getSize() << endl;
	cout << endl << "--------------" << endl;
	mas.push_back(5);
	cout << mas[10] << endl;
	cout << endl << "--------------" << endl;
	cout << mas.getCapacity() << endl;
	cout << endl << "--------------" << endl;
	_vector <int> arr;
	for (int i = 0; i < 6; i++) {
		arr.push_back(i);
		cout << arr[i] << " ";
	}
	cout << endl << arr.getSize() << " " << arr.getCapacity() << endl;
	cout << endl << "--------------" << endl;
	arr.push(24, 1);
	for (int i = 0; i < arr.getSize(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl << "--------------" << endl;
	arr.erase(0);
	int size = arr.getSize();
	for (int i = 0; i < arr.getSize(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl << arr.getSize() << " " << arr.getCapacity() << endl;
	cout << arr.find(77);

	cout << endl << "--------------" << endl;
	

	
	cout << "stack" << endl;
	stack<int> temp;
	temp.push(3);
	temp.push(23);
	temp.push(6);
	for (int i = 0; i < 3; i++) {
		cout << temp.peak()<<" ";
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		cout << temp.pop() << " ";
	}
	*/

	string math;
	cout << "Enter an infix notation for an expression: ";
	
	getline(cin ,math);
	SortStation(math);
	cout << endl;
	system("pause");
	return 0;
}

void SortStation(string math) {
	int cnt_skob = 0;

	stack<char> st;
	cout << "Prefix expression notation: ";


	for (int i = 0; i < math.size(); i++) {

		switch (what_sim(math[i])) {
		case symbol::num:
			cout << math[i];
			if (i + 1 != math.size()) {
				if (what_sim(math[i + 1]) != symbol::num) {
					cout << " ";
				}
			}
			else if (i + 1 == math.size()) {
				cout << " ";
			}
			break;
		case symbol::skobka:
			if (math[i] == '(') {
				st.push(math[i]);
				cnt_skob++;
			}
			else {
				if (cnt_skob <= 0) {
					cout << "\nError: the number of bkt.\n";
					return;
				}
				while (st.peak() != '(' && !st.is_empty()) {
					
					if (st.peak() == 's') {
						cout << st.pop();
						cout << "i";
						cout << "n" << " ";

					}
					else if (st.peak() == 'c') {
						cout << st.pop();
						cout << "o";
						cout << "s" << " ";

					}
					else {
						cout << st.pop() << " ";

					}
					
				}
				st.pop();
				cnt_skob--;
			}
			break;
		case symbol::znak:
			if (!st.is_empty()) {
				while (_prior(math[i]) <= _prior(st.peak())&& !st.is_empty()) {
					
					if (st.peak() != '(') {
						if (st.peak() == 's') {
							cout << st.pop();
							cout << "i";
							cout << "n" << " ";

						}
						else if (st.peak() == 'c') {
							cout << st.pop();
							cout << "o";
							cout << "s" << " ";

						}
						else {
							cout << st.pop() << " ";
						}
					}
					else {
						st.pop();
						break;
					}
				}
				
			}

			st.push(math[i]);

			break;
		case symbol::funk:
			st.push(math[i]);
			i += 2;

			break;
		}

		
	}



	if (cnt_skob != 0) {
		cout << "\nError:  the number of bkt.\n";
		return;
	}

	while (!st.is_empty()) {
		if (st.peak() == 's') {
			cout << st.pop();
			cout << "i";
			cout << "n" << " ";

		}
		else if (st.peak() == 'c') {
			cout << st.pop();
			cout << "o";
			cout << "s" << " ";

		}
		else {
			cout << st.pop() << " ";

		}

		
	}
	
}
int what_sim(char t) {
	if (t <= '9' && t >= '0') {
		return symbol::num;
	}
	else if (t == '+' || t == '-' || t == '*' || t == '/' || t == '^' ) {
		return symbol::znak;
	}
	else if (t=='(' || t == ')') {
		return symbol::skobka;
	}
	else if (t == 's' || t == 'c') {
		return symbol::funk;
	}

}

int _prior(char t) {
	switch (t) {
	case '+':
	case'-':
		return prior::first;
		break;
	case '*':
	case '/': return prior::second;
		break;
	case '^': return prior::third;
		break;
	case 'c':
	case 's': return prior::forth;
		break;
	}
}