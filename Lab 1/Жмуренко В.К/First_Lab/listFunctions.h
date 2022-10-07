#pragma once

struct box				// ��������� �������� ������������ ������
{
	char Inf;
	box* Adr;
};

class List
{
	box* Head;
	unsigned Size;

public:
	
	// �����������
	List(); 
	
	// ������, ���������� � ����������� �������
	void CreateList(unsigned Lenght);	// �������� ������������ ������
	box* addressGetter();	// ��������� ������ ������ �������� ��������
	void dataInserting(char data);	// ���� ������ � ������� ������� ������
	void sizeOfList(box* Beg);	// �������, ���������� ������ ������
	void newItem(unsigned Index);	// ���������� ������ �������� � ������
	box* getItem(unsigned Index);	// ��������� ������ ������������� �������� �� �������
	unsigned IndexforData(char data); // ��������� ������� �� �������� ������ ��������
	void DeleteItem(unsigned Index);	// ������� ������� �� �������
	bool isListDataNotEmpty();	// �������� ������ �� ������� ������ � ���
	void DeleteList();	// ������� ������ � ����������� ������
};

class ArrayList
{
	char* arr;
	unsigned arraySize;

public:
	
	// ����������� � ����������
	ArrayList(unsigned size);
	~ArrayList();

	// ������, ���������� � ������������ ��������
	char * getItem(unsigned Index); // ��������� � �������� �� ��� �������
	void addData(unsigned Index, char data); // ������ �������� �� �������
	void deleteItem(unsigned Index); // �������� �������� �������� �� �������
	unsigned IndexforData(char data); // ��������� ������� �� �������� ��������
};