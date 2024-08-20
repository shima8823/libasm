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

void test_write() {
	char	*buf = "42tokyo\n";
	int		invalid_fd = 10;
	
	errno = 0;
	printf("%zd\n", write(STDOUT_FILENO, buf, strlen(buf)));
	errno = 0;
	printf("%zd\n", ft_write(STDOUT_FILENO, buf, strlen(buf)));

	errno = 0;
	printf("%zd\n", write(invalid_fd, buf, strlen(buf)));
	printf("%d\n", errno);
	printf("%s\n", strerror(errno));
	errno = 0;
	printf("%zd\n", ft_write(invalid_fd, buf, strlen(buf)));
	printf("%d\n", errno);
	printf("%s\n", strerror(errno));
	
}

int main() {
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
}