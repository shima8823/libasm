CC = gcc
AS = nasm

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I.
ASFLAGS = -f elf64
LDFLAGS = -L.
LDLIBS = -lasm
NAME = libasm.a
SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s

TEST_NAME = test
TEST_SRCS = main.c

OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/, $(SRCS:%.s=%.o))
TEST_OBJ = $(addprefix $(OBJDIR)/, $(TEST_SRCS:%.c=%.o))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	ar rcs $@ $?

$(OBJDIR)/%.o: %.s | $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)

test: $(NAME) $(TEST_OBJ)
	$(CC) -o $(TEST_NAME) $(TEST_OBJ) $(LDFLAGS) $(LDLIBS)

re: fclean all

.PHONY: all clean fclean re test