#include <stdio.h>

int main(int argc, const char *argv[])
{
	
	//signed int a = 0x80000000;
	//signed short int b = 0x80000000;
	//
	char ch[] = "abcde";
	char *cp = ch;
	printf("c = %c\n",*cp++);
	return 0;
}
