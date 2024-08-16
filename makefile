CC = gcc
AS = nasm

# CFLAGS = -Wall -Wextra -Werror -MMD -MP
ASFLAGS = -f elf64

CPPFLAGS = -I. -L. -lasm
NAME = libasm.a
SRCS = helloworld.s 

TEST_NAME = test
TEST_SRCS = main.c

OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/, $(SRCS:%.s=%.o))

DEPENDS = $(OBJ:.o=.d)
TEST_DEPENDS = $(MY_TEST_OBJ:.o=.d)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJDIR)/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	$(RM) $(OBJ) $(DEPENDS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)

test: $(NAME)
	$(CC) -o $(TEST_NAME) $(TEST_SRCS) $(CFLAGS) $(CPPFLAGS)

leaks: $(MY_TEST_NAME)
	leaks -q -atExit -- ./$(MY_TEST_NAME)

re: fclean all

-include $(DEPENDS)
-include $(MY_TEST_DEPENDS)

.PHONY: all clean fclean re leaks comp