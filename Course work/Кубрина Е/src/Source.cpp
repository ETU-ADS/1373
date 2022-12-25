#include "Header.h"

int main() {
	setlocale(LC_ALL, "Rus");
	Kraskal A;

	A.load_from_file();
	A.setEdge();
	A.SortEdge();
	A.karscal();
	return 0;
}