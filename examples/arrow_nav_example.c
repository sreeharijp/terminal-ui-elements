#include "../lib/arrow_nav_menu.h"

//gcc -o arrow_nav_example ../examples/arrow_nav_example.c ../lib/arrow_nav_menu.c


int main()
{

	char prompt[][30] = {"Hi", "Hello", "Bye"};
	printf("\x1b[2J");
	printf("Option Selected: %s\n", prompt[arrow_key_navigate(prompt, 2, 0, 0) - 1]);

}