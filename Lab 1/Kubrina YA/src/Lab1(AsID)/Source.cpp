#include "Header.h"
void SortStation(string math);
int what_sim(char t);
int _prior(char t);
bool checkExp(string math);
int main() {

	/*
	_List list(3, 5);
	list.printList();
	cout << endl << "----------------" << endl;
	list.printNode(1);
	cout << endl << "--------" << endl;
	cout << list.getSize();
	cout << endl << "--------" << endl;
	cout << list.is_empty();
	cout << endl << "--------" << endl;
	_List list1;
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

	*/
	//////////////////////////

	/*
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
	*/

	/*
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
	//cin >> math;
	getline(cin ,math);
	SortStation(math);
	cout << endl;
	system("pause");
	return 0;
}

bool checkExp(string math) {
	for (int i = 0; i < math.size(); i++) {
		if (math[i] == 's') {
			if (i + 2 <= math.size()) {
				if (math[i + 1] != 'i' || math[i + 2] != 'n') {
					cout << "Error: input fail";
					return false;
				}
			}
			else {
				return false;
			}
			i += 2;
		}
		else if (math[i] == 'c') {
			if (i + 2 <= math.size()) {
				if (math[i + 1] != 'o' || math[i + 2] != 's') {
					cout << "Error: input fail";
					return false;
				}
			}
			else {
				return false;
			}
			i += 2;
		}
		else {
			if (!(math[i] <= '9' && math[i] >= '0' || math[i] == '+'
				|| math[i] == '-' || math[i] == '*' || math[i] == '/' || math[i] == '^'
				|| math[i] == '(' || math[i] == ')')) {
				cout << "Error: input fail";
				return false;
			}
		}
		
	}
		
	return true;
}

void SortStation(string math) {
	while (true) {
		if (checkExp(math)) {
			queue<char> q;
			stack<char> st;
			for (int i = 0; i < math.size(); i++) {
				switch (what_sim(math[i])) {
				case symbol::num:
					q.push(math[i]);
					if (i + 1 != math.size()) {
						if (what_sim(math[i + 1]) != symbol::num) {
							q.push(' ');
						}
					}
					break;
				case symbol::skobka:
					if (math[i] == '(') {
						st.push(math[i]);
					}
					else {
						while (st.peak() != '(') {
							if (st.peak() == 's') {
								q.push(st.pop());
								q.push('i');
								q.push('n');
							}
							else if (st.peak() == 'c') {
								q.push(st.pop());
								q.push('o');
								q.push('s');
							}
							else {
								q.push(st.pop());
							}

						}
						st.pop();
					}
					break;
				case symbol::znak:
					if (!st.is_empty()) {
						if (st.peak() != '(') {
							if (_prior(math[i]) <= _prior(st.peak())) {
								if (st.peak() == 's') {
									q.push(st.pop());
									q.push('i');
									q.push('n');
								}
								else if (st.peak() == 'c') {
									q.push(st.pop());
									q.push('o');
									q.push('s');
								}
								else {
									q.push(st.pop());
								}
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
			while (!st.is_empty()) {
				if (st.peak() == 's') {
					q.push(st.pop());
					q.push('i');
					q.push('n');
				}
				else if (st.peak() == 'c') {
					q.push(st.pop());
					q.push('o');
					q.push('s');
				}
				else {
					q.push(st.pop());
				}

			}
			cout << "Prefix expression notation: ";
			while (!q.is_empty()) {
				cout << q.pop();
			}
			return;
		}
		else {
			cout << "\nTry again.\nEnter an infix notation for an expression: ";
			cin.clear();
			getline(cin, math);
			
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