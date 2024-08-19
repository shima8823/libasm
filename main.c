#include "main.h"

void test_strlen() {
	char *buf = "42tokyo\n";
	printf("%zu\n", strlen(buf));
	printf("%zu\n", ft_strlen(buf));
}

void test_strcpy() {
	char dest[10];
	char *src = "42tokyo\n";
	printf("%s", strcpy(dest, src));
	printf("%s", ft_strcpy(dest, src));
}

void test_strcmp() {
	char *s1 = "42tokyo\n";
	char *s2 = "42paris\n";
	printf("%d\n", strcmp(s1, s2));
	printf("%d\n", ft_strcmp(s1, s2));

	printf("%d\n", strcmp(s1, s1));
	printf("%d\n", ft_strcmp(s1, s1));
}

int main() {
	test_strlen();
	test_strcpy();
	test_strcmp();
}