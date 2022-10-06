#include "Header.h"
void SortStation(string math);
int what_sim(char t);
int _prior(char t);
bool checkSkob(string math);
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
	
	getline(cin ,math);
	SortStation(math);
	cout << endl;
	system("pause");
	return 0;
}

bool checkSkob(string math) {
	
	int cnt_s1 = 0, cnt_s2 = 0;
	for (int i = 0; i < math.size(); i++) {
		if (math[i] == '(') {
			cnt_s1++;
		}
		else if (math[i] == ')') {
			cnt_s2++;
		}
	}
	if (cnt_s1 == cnt_s2) { return true; }
	else { return false; }
}

void SortStation(string math) {
	while (true) {
		if (checkSkob(math)) {
			
			stack<char> st;
			cout << "Prefix expression notation: ";
			for (int i = 0; i < math.size(); i++) {
				switch (what_sim(math[i])) {
				case symbol::num:
					
					cout << math[i];
					if (i + 2 != math.size()) {
						if (what_sim(math[i + 1]) != symbol::num) {
							cout << " "; 
							
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
								cout << st.pop();
								cout << "i";
								cout << "n"<<" ";
								
							}
							else if (st.peak() == 'c') {
								cout << st.pop();
								cout << "o";
								cout << "s"<<" ";
								
							}
							else {
								cout << st.pop()<<" ";
								
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
									cout << st.pop();
									cout << "i";
									cout << "n"<<" ";
									
								}
								else if (st.peak() == 'c') {
									cout << st.pop();
									cout << "o";
									cout << "s"<<" ";
									
								}
								else {
									cout << st.pop()<<" ";
									
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
					cout << st.pop();
					cout << "i";
					cout << "n"<<" ";
					
				}
				else if (st.peak() == 'c') {
					cout << st.pop();
					cout << "o";
					cout << "s"<<" ";
					
				}
				else {
					cout << st.pop()<<" ";
					
				}
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