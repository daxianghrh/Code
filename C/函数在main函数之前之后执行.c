#include <stdio.h>

__attribute((destructor)) void after_main()
{
	printf("%s\n", __FUNCTION__);
}

__attribute((constructor)) void before_main() {
    printf("%s\n", __FUNCTION__);
}

int main(int argc, char **argv)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}
