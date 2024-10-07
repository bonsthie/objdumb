#include "objdumb.h"
#include <stdio.h>

int main()
{
	char *result = scrap_url("https://www.felixcloutier.com/x86/");
	printf("%s\n", result);
}
