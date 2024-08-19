CC = gcc
AS = nasm

# CFLAGS = -Wall -Wextra -Werror -MMD -MP
ASFLAGS = -f elf64

CPPFLAGS = -I.
LDFLAGS = -L.
LDLIBS = -lasm
NAME = libasm.a
SRCS = helloworld.s ft_strlen.s ft_strcpy.s ft_strcmp.s

TEST_NAME = test
TEST_SRCS = main.c

OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/, $(SRCS:%.s=%.o))
TEST_OBJ = $(addprefix $(OBJDIR)/, $(TEST_SRCS:%.c=%.o))

DEPENDS = $(OBJ:.o=.d)
TEST_DEPENDS = $(MY_TEST_OBJ:.o=.d)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJDIR)/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ) $(DEPENDS)
	$(RM) $(TEST_OBJ) $(DEPENDS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)

test: $(NAME) $(TEST_OBJ)
	$(CC) -o $(TEST_NAME) $(TEST_OBJ) $(LDFLAGS) $(LDLIBS)

leaks: $(MY_TEST_NAME)
	leaks -q -atExit -- ./$(MY_TEST_NAME)

re: fclean all

-include $(DEPENDS)
-include $(MY_TEST_DEPENDS)

.PHONY: all clean fclean re leaks comp