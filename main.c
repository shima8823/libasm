#include "main.h"

void test_strlen() {
	char *buf = "42tokyo\n";

	printf("%stest_stren%s\n", MAGENTA, WHITE);

	printf("TEST: buf = 42tokyo\\n\n");
	if (strlen(buf) == ft_strlen(buf)) {
		printf("%sPASS\n", GREEN);
	} else {
		printf("%sFAIL\n", RED);
	}
	printf("%s\n", WHITE);
}

void test_strcpy() {
	char src[] = "42tokyo";
	char dest1[10];
	char dest2[10];

	printf("%stest_strcpy%s\n", MAGENTA, WHITE);

	printf("TEST: src = 42tokyo\n");
	strcpy(dest1, src);
	ft_strcpy(dest2, src);

	if (strcmp(dest1, dest2) == 0) {
		printf("%sPASS\n", GREEN);
	} else {
		printf("%sFAIL\n", RED);
	}
	printf("%s\n", WHITE);
}

void test_strcmp() {
	char *s1 = "42tokyo\n";
	char *s2 = "42paris\n";

	printf("%stest_strcmp%s\n", MAGENTA, WHITE);

	printf("TEST: s1 = 42tokyo, s2 = 42paris\n");
	if (strcmp(s1, s2) == ft_strcmp(s1, s2)) {
		printf("%sPASS\n", GREEN);
	} else {
		printf("%sFAIL\n", RED);
	}
	printf("%s\n", WHITE);

	printf("TEST: s1 = 42tokyo, s2 = s1\n");
	if (strcmp(s1, s1) == ft_strcmp(s1, s1)) {
		printf("%sPASS\n", GREEN);
	} else {
		printf("%sFAIL\n", RED);
	}
	printf("%s\n", WHITE);
}

void test_write() {
	char	*buf = "42tokyo\n";
	int		invalid_fd = 10;
	ssize_t	r1, r2;
	int		e1, e2;

	printf("%stest_write%s\n", MAGENTA, WHITE);
	
	printf("TEST: standard: buf = 42tokyo\\n\n");
	errno = 0;
	r1 = write(STDOUT_FILENO, buf, strlen(buf));
	e1 = errno;

	errno = 0;
	r2 = ft_write(STDOUT_FILENO, buf, strlen(buf));
	e2 = errno;

	if (r1 == r2 && e1 == e2) {
		printf("%sPASS\n", GREEN);
	} else {
		printf("%sFAIL\n", RED);
	}
	printf("%s\n", WHITE);

	printf("TEST: invalidFD: buf = 42tokyo\\n\n");
	errno = 0;
	r1 = write(invalid_fd, buf, strlen(buf));
	e1 = errno;

	errno = 0;
	r2 = ft_write(invalid_fd, buf, strlen(buf));
	e2 = errno;

	if (r1 == r2 && e1 == e2) {
		printf("%sPASS\n", GREEN);
	} else {
		printf("%sFAIL\n", RED);
	}
	printf("%s\n", WHITE);
}

void compare_reads(const char *test_name, int fd, size_t count) {
	char buf_std[BUFFER_SIZE] = {0};
	char buf_ft[BUFFER_SIZE] = {0};
	ssize_t read_std, read_ft;
	int errno_std, errno_ft;

	// std
	errno = 0;
	read_std = read(fd, buf_std, count);
	errno_std = errno;

	if (fd != STDIN_FILENO) {
		lseek(fd, 0, SEEK_SET);
	}

	// ft
	errno = 0;
	read_ft = ft_read(fd, buf_ft, count);
	errno_ft = errno;

	// test
	printf("Test: %s\n", test_name);
	printf("Standard read: bytes=%zd, errno=%d, content='%.20s%s'\n",
			read_std, errno_std, buf_std, (strlen(buf_std) > 20 ? "..." : ""));
	printf("ft_read:       bytes=%zd, errno=%d, content='%.20s%s'\n",
			read_ft, errno_ft, buf_ft, (strlen(buf_ft) > 20 ? "..." : ""));
		
	if (read_std == read_ft && errno_std == errno_ft && (read_std <= 0 || memcmp(buf_std, buf_ft, read_std) == 0)) {
		printf("%sPASS\n", GREEN);
	} else {
		printf("%sFAIL\n", RED);
	}
	printf("%s\n", WHITE);
}

void test_read() {
	printf("%stest_write%s\n", MAGENTA, WHITE);

	int fd = open("test.txt", O_RDONLY);
	if (fd == -1) {
		perror("open failed");
		return;
	}

	compare_reads("standard file read", fd, BUFFER_SIZE);
	close(fd);
	compare_reads("Invalid file descriptor", -1, BUFFER_SIZE);
	compare_reads("NULL buffer", STDIN_FILENO, 0);
}

void compare_strdup(const char *test_str) {
	char *std_result, *ft_result;

	// std
	if (test_str == NULL)
		std_result = NULL;
	else
		std_result = strdup(test_str);
		
	// ft
	ft_result = ft_strdup(test_str);
		
	// test
	printf("Test string: \"%.20s%s\"\n", test_str, (test_str == NULL ? "" : (strlen(test_str) > 20 ? "..." : "")));
	printf("Standard strdup result: \"%.20s%s\"\n", std_result, (test_str == NULL ? "" : (strlen(std_result) > 20 ? "..." : "")));
	printf("ft_strdup result:       \"%.20s%s\"\n", ft_result, (test_str == NULL ? "" : (strlen(ft_result) > 20 ? "..." : "")));

	if (std_result == NULL && ft_result == NULL) {
		printf("%sPASS: Both functions returned NULL\n", GREEN);
	} else if (std_result == NULL || ft_result == NULL) {
		printf("%sFAIL: One function returned NULL, the other didn't\n", RED);
	} else if (strcmp(std_result, ft_result) == 0) {
		printf("%sPASS: Results match\n", GREEN);
	} else {
		printf("%sFAIL: Results don't match\n", RED);
	}
	free(std_result);
	free(ft_result);
	printf("%s\n", WHITE);
}

void test_strdup() {
	char buf[BUFFER_SIZE];
	
	printf("%stest_strdup%s\n", MAGENTA, WHITE);

	compare_strdup("Hello, World!");
	compare_strdup("");
	compare_strdup("A");
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1) {
		perror("open failed");
		return;
	}
	if (read(fd, buf, BUFFER_SIZE) == -1) {
		perror("read failed");
		return;
	}
	compare_strdup(buf);
	close(fd);
	compare_strdup("Special: !@#$%^&*()_+");
	compare_strdup("Unicode: こんにちは世界");
	compare_strdup(NULL);
}

int main() {
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	test_strdup();
}