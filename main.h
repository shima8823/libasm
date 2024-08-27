#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

#define MAGENTA "\x1b[35m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define WHITE "\x1b[0m"

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char * dst, const char * src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t count);
char	*ft_strdup(const char *s);

#endif