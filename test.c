#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_word
{
	char *text;
	int start;
} t_word;

void *arrnew(int size)
{
	return malloc(sizeof(void *) * (size + 1));
}

t_word *test()
{
	t_word *arr = arrnew(1);
	arr[0] = (t_word){
		.text = strdup("Hello"),
		.start = 0,
	};

	// free(arr[0].text);
	// free(arr);
	return arr;
}

int main(void)
{
	t_word *arr = test();
	test();
	printf("%s \n", arr[0].text);

	return 0;
}