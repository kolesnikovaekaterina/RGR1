#include "field.h"
#include <stdio.h>

using namespace std;

int main(void) {
	Field a;
	if (!a.read("map.txt"))
		return 1;
    a.print ();
    printf ("\n");
	a.way();
	if (!a.is_way())
		printf("Way is not exist\n");
	else {
		a.gen_way();
		a.print();
		printf("Answer> %d\n", a.length_way());
	}
	return 0;
}
