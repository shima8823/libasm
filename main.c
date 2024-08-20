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
		printf("Result: PASS\n");
	} else {
		printf("Result: FAIL\n\n");
	}
}

void test_file_read(const char *filename) {
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror("open failed");
		return;
	}

	compare_reads("File read", fd, BUFFER_SIZE);
	close(fd);
}

void test_error_cases() {
	compare_reads("Invalid file descriptor", -1, BUFFER_SIZE);
	compare_reads("NULL buffer", STDIN_FILENO, 0);
}


void test_read() {
	printf("Comparing standard read with ft_read:\n\n");
	test_file_read("test.txt");
	test_error_cases();	
}

int main() {
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
}