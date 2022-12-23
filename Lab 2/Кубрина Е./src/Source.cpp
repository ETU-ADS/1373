#include "Header.h"


int main() {
	int N; //ðàçìåð ìàññèâà
	int minrun;
	srand(time(0));
	cout << "Enter the size of the array: ";
	cin >> N;
	_vector <int> mas(N);
	for (int i = 0; i < N; i++) {
		mas[i] = rand() % 100 + 1;
	}//
	printArr(mas);
	
	/*int cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 1) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 2) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 3) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 4) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 5) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 6) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 7) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 8) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 9) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	cout << endl;*/
	minrun = GetMinrun(N);
	//minrun = 5;

	cout << "\nMinRun: " << minrun << endl;
	//InsertionSort(mas);
	
	TimSort(mas, minrun);
	printArr(mas);
	/*for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 1) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 2) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 3) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 4) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 5) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 6) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 7) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 8) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	for (int i = 0; i < mas.getSize(); i++) {
		if (mas[i] == 9) { cnt++; }
	}
	cout << cnt << " ";
	cnt = 0;
	cout << endl;*/
	system("pause");
	return 0;
}

int GetMinrun(int n) {
	int r = 0;
	while (n >= 64) {
		r |= n & 1;
		n >>= 1;
	}
	return n + r;
}

void TimSort(_vector <int> &mas, int minrun) {
	_Pos pos;
	_Pos temp1;
	_Pos temp2;
	pos.start = 0;
	pos.finish = 1;
	stack <_Pos> st;

	for (int i = 1; i < mas.getSize(); i++) {
		
		if (i == mas.getSize() - 1) {
			InsertionSort(mas, pos);
			st.push(pos);
			if (st.getSize() >= 3) {
				checkSt(mas, st, temp1, temp2);
			}
		}

		if (mas[i] < mas[i - 1]) {
			findRev(mas, pos, i);
			reverseRun(mas, pos, i);
			
			if ((pos.finish - pos.start >= minrun - 1) || (pos.finish == mas.getSize()-1)) {
				
				InsertionSort(mas,pos);
				st.push(pos);
				if (st.getSize() >= 3) {
					checkSt(mas, st, temp1, temp2);
					
				}
				pos.start = pos.finish+1;
				pos.finish++;
				i++;
			}
			pos.finish++;
		}
		else if (mas[i] >= mas[i - 1]) {
			
			pos.finish++;
		}



	}

	if ((st.peak()).start == 0 && (st.peak()).finish == mas.getSize() - 1) {
		return;
	}
	while (!st.is_empty()) {
		checkSt(mas, st, temp1, temp2);
		temp1.start = (st.peak()).start;
		temp1.finish = (st.pop()).finish;
		Merge(mas, st.pop(), temp1);
	}

}


void findRev(_vector<int> &mas, _Pos &pos, int i) {
	for (int j = pos.start+1; j < mas.getSize(); j++) {
		if (mas[j] <= mas[j - 1]) {
			pos.finish++;
		}
	}
}

void checkSt(_vector<int> &mas, stack<_Pos> &st, _Pos &temp1, _Pos &temp2) {
	while (st.getSize() >= 3 && checkÑond(st) != 0) {
		switch (checkÑond(st))
		{
		case 1:
			temp1.start = (st.peak()).start;
			temp1.finish = (st.peak()).finish;
			st.pop();
			temp2.start = (st.peak()).start;
			Merge(mas, st.pop(), temp1);
			temp1.start = temp2.start;
			st.push(temp1);
			break;
		case 2:
			temp1.start = (st.peak()).start;
			temp1.finish = (st.peak()).finish;
			st.pop();

			temp2.start = (st.peak()).start;
			temp2.finish = (st.peak()).finish;
			st.pop();

			Merge(mas, st.peak(), temp2);
			temp2.start = (st.pop()).start;
			st.push(temp2);
			st.push(temp1);

			break;
		}
	}
}
void printArr(_vector <int> &mas) {
	cout << "Your array:" << endl;
	for (int i = 0; i < mas.getSize(); i++) {
		cout << mas[i] << " ";
	}
	cout << endl;
}
void printArrPiece(_vector <int>& mas, _Pos pos) {
	cout << "Piece:" << endl;
	for (int j = pos.start; j < pos.finish + 1; j++) {
		cout << mas[j] << " ";
	}
	cout << endl;
}
void InsertionSort(_vector <int> &mas, _Pos pos) {
	int temp;

	for (int i = pos.start+1, j; i < pos.finish + 1; i++) {
		j = i;
		while (j > pos.start && mas[j] < mas[j - 1]) {
			temp = mas[j];
			mas[j] = mas[j - 1];
			mas[j - 1] = temp;
			j--;
		}
		
	}
	
}



void reverseRun(_vector<int> &mas, _Pos pos, int i) {
	int temp;
	for (int j = i; j < (pos.finish+1)/2; j++) {
		temp = mas[j];
		mas[j] = mas[pos.finish - j];
		mas[pos.finish - j] = temp;
	}
}

int checkÑond(stack<_Pos> &st) {
	_Pos pos1;
	_Pos pos2;

	pos1.start = (st.peak()).start;
	pos1.finish = (st.peak()).finish;
	st.pop();
	pos2.start = (st.peak()).start;
	pos2.finish = (st.peak()).finish;
	st.pop();

	if ((pos1.finish - pos1.start) + (pos2.finish - pos2.start) <
		(st.peak()).finish - (st.peak()).start &&
		(pos2.finish - pos2.start) > (pos1.finish - pos1.start)) {
		st.push(pos2);
		st.push(pos1);
		return 0;
	}
	else {
		int res = findMin(pos1, st.peak());
		st.push(pos2);
		st.push(pos1);
		return res;
	}
	
}

int findMin(_Pos pos1, _Pos pos2) {
	if ((pos1.finish - pos1.start) <= pos2.finish - pos2.start) {
		return 1;
	}
	else if ((pos1.finish - pos1.start) > pos2.finish - pos2.start) {
		return 2;
	}
}


void Merge(_vector<int> &mas, _Pos pos1, _Pos pos2) {
	Gallop gl;
	int step = 2;
	int t;
	_vector<int> temp1(pos1.finish - pos1.start + 1);
	_vector<int> temp2(pos2.finish - pos2.start + 1);
	for (int i = 0; i < pos1.finish - pos1.start + 1; i++) {
		temp1[i] = mas[i + pos1.start];
	}
	
	for (int i = 0; i < pos2.finish - pos2.start + 1; i++) {
		temp2[i] = mas[i + pos2.start];
	}
	
	int i = 0, j = 0, k = pos1.start;
	while (i < temp1.getSize() && j < temp2.getSize()) {
		if (temp1[i] <= temp2[j]) {
			if (temp1[i] == temp2[j]) {
				mas[k] = temp2[j];
				j++;
				k++;
				gl.flag = true;
				gl.cnt = 1;
			}
			mas[k] = temp1[i];
			i++;
			k++;
			if (gl.flag == false) { 
				gl.cnt++;
				if (gl.cnt == 7) {
					step = 1;
					t = i;
					while (temp1[t+step] < temp2[j] && t+step< temp1.getSize()) {
						step++;
						t++;
					}
					if (temp1[t + step] < temp2[j] && t + step >= temp1.getSize()) {
						if (temp1[temp1.getSize() - 1] < temp2[j]) {
							while (i < temp1.getSize()) {
								mas[k] = temp1[i];
								i++;
								k++;
							}
							break;
						}
					}
					while (i < t) {
						mas[k] = temp1[i];
						i++;
						k++;
					}
					if (mas[k-1] == temp2[j]) {
						mas[k] = temp2[j];
						k++;
						j++;
					}
				}
			}
			else{ gl.flag = false; gl.cnt = 1;}
			
			
		}
		else {
			mas[k] = temp2[j];
			j++;
			k++;
			if (gl.flag == true) { 
				gl.cnt++; 
				if (gl.cnt == 7) {
					step = 1;
					t = j;
					while (temp2[t + step] < temp1[i] && t + step < temp2.getSize()) {
						step++;
						t++;
					}
					if (temp2[t + step] < temp1[i] && t + step >= temp2.getSize()) {
						if (temp2[temp2.getSize() - 1] < temp1[i]) {
							while (j < temp2.getSize()) {
								mas[k] = temp2[j];
								j++;
								k++;
							}
							break;
						}
					}
					while (j < t) {
						mas[k] = temp2[j];
						j++;
						k++;
					}
					if (mas[k - 1] == temp1[i]) {
						mas[k] = temp2[i];
						k++;
						i++;
					}
				}
			}
			else { gl.flag = true; gl.cnt = 1; }
		}
	}
	
	if (i != temp1.getSize() - 1) {
		while (i < temp1.getSize()) {
			mas[k] = temp1[i];
			k++;
			i++;
		}
	}
	else if (j != temp2.getSize() - 1) {
		while (j < temp2.getSize()) {
			mas[k] = temp2[j];
			k++;
			j++;
		}
	}
	

}

