NAME		= libbuffered-socky.so

CC			= gcc

ARCHIVER	= ar

SRCS		= src/create.c
SRCS		+= src/destroy.c
SRCS		+= src/write.c
SRCS		+= src/read.c
SRCS		+= src/recv.c
SRCS		+= src/flush.c
SRCS		+= src/flushf.c

TESTS_SRCS	:= $(SRCS)
TESTS_SRCS	+= tests/create_tests.c
TESTS_SRCS	+= tests/destroy_tests.c

OBJS		= $(SRCS:.c=.o)
TESTS_OBJS	= $(TESTS_SRCS:.c=.o)

RM			= rm -f

DEPENDENCIES = buffy socky

RECURSIVE_HEADERS = $(shell dirname `find . -name "*.h"`)

CFLAGS		+= -Wall -Wextra -fPIC -pedantic
CPPFLAGS	+= -I ./include $(addprefix -iquote,$(RECURSIVE_HEADERS))
LIBS		= $(addprefix -l,$(DEPENDENCIES))
LDFLAGS		= -shared $(LIBS) $(addprefix -L,$(DEPENDENCIES))

GREEN=`tput setaf 2`
RED=`tput setaf 1`
YELLOW=`tput setaf 3`
NO_COLOR=`tput sgr0`

%.o : %.c
	@$ $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ ["$(GREEN)"OK"$(NO_COLOR)"]"
.SUFFIXES: .o .c

all: dependencies $(NAME)

dependencies:
	git submodule update --init --recursive
	git submodule foreach make

$(NAME): $(OBJS)
	@$ $(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@
	@echo "$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $@ \
	["$(GREEN)"LINKING OK"$(NO_COLOR)"]"

tests_run: dependencies $(TESTS_OBJS)
	git submodule foreach make $@
	@echo $(TESTS_OBJS)
	@$ $(CC) -lcriterion $(TESTS_OBJS) $(LIBS) -o $@
	@echo "$(CC) -lcriterion $(TESTS_OBJS) $(LIBS) -o $@ \
	["$(GREEN)"LINKING OK"$(NO_COLOR)"]"
	./$@
	@$(RM) $@
	@$(RM) $(TESTS_OBJS)

val_run: CFLAGS += -g3
val_run: $(TESTS_OBJS)
	@$ $(CC) -lcriterion $(TESTS_OBJS) $(LIBS) -o $@
	@echo "$(CC) -lcriterion $(TESTS_OBJS) $(LIBS) -o $@ \
	["$(GREEN)"LINKING OK"$(NO_COLOR)"]"
	valgrind --trace-children=yes --quiet ./$@
	@pkill nc || true
	@pkill $@ || true
	@$(RM) $@
	@$(RM) $(TESTS_OBJS)

debug: CFLAGS += -g3
debug: re
	git submodule foreach make $@

clean:
	git submodule foreach make $@
	$(RM) $(OBJS)

fclean: clean
	git submodule foreach make $@
	$(RM) $(NAME) $(NAME:.so=.a)

re: fclean all

install: all
	git submodule foreach make $@
	@cp $(NAME) /usr/lib/$(NAME) 2> /dev/null || \
	printf "\033[1m\033[31mError : try sudo make install\033[0m\n" && \
	cp include/buffered_socky.h /usr/include/ 2> /dev/null && \
	printf "\033[1m\033[32mLibrary $(NAME) successfully installed !\033[0m\n"

static: $(OBJS)
	$(ARCHIVER) rc $(NAME:.so=.a) $(OBJS)

.PHONY: all clean fclean re tests_run val_run debug install static
