.SILENT:
CC = gcc
OS = $(shell uname)
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
GCOV = --coverage -O0 -g -fno-eliminate-unused-debug-types -fno-inline
LFLAGS =

ifeq ($(OS), Darwin)
	LFLAGS += -lcheck
else ifeq ($(OS), Linux)
	LFLAGS += -lcheck -lsubunit -lm -lrt -lpthread
endif

MAIN_FUNC = $(wildcard core/*.c)
COMMON = $(wildcard common/*.c)  
IO_FUNC = $(wildcard core/io/*.c)  
BONUS_FUNC = $(wildcard core/bonus/*.c)  

SOURCE = $(MAIN_FUNC) $(COMMON) $(IO_FUNC) $(BONUS_FUNC)
OBJ_DIR = obj
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCE))
OBJS_TESTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(TESTS))

TEST_CHECK = $(wildcard tests/func_tests/tests_check/*.c)
TEST_CHECK_BASENAMES = $(basename $(notdir $(TEST_CHECK)))
TESTS_FUNC_DIR = tests/func_tests/
TESTS_FUNC = $(wildcard tests/func_tests/*.c)
TESTS = $(MAIN_TEST)  $(TESTS_FUNC)
MAIN_TEST = tests/s21_string_tests.c

LIB_NAME = s21_string.a

all: $(LIB_NAME)

checkmk:
	@for file in $(TEST_CHECK); do \
		filename=$$(basename $$file .c); \
		checkmk clean_mode=1 $$file > $(TESTS_FUNC_DIR)$$filename.c; \
	done

$(LIB_NAME): $(OBJS)
	ar rcs $@ $^
	ranlib $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

gcov:	CFLAGS += $(GCOV)
gcov: re

test: CFLAGS += $(GCOV)
test: re $(OBJS_TESTS)
	$(CC) $(CFLAGS)  $(OBJS_TESTS) -o s21_string_tests $(LFLAGS) $(LIB_NAME)

gcov_report: test
	./s21_string_tests
	lcov -t "s21_string_tests" -o s21_test.info -c -d . --rc branch_coverage=all --exclude "tests/*"
	genhtml -o report s21_test.info --branch-coverage

gcov_report_clang: clang_i clang_n gcov_report

clean:
	rm -rf $(OBJ_DIR) $(LIB_NAME)
	rm -rf report
	rm -f s21_string_tests
	rm -f *.gcov
	rm -f *.gcda
	rm -f *.gcno
	rm -f s21_test.info
	rm -rf tests/logs
	
re: clean all

clang_i:
	# cp ../materials/linters/.clang-format .
	clang-format -i  */*.c */*/*.c
	clang-format -i  */*.h */*/*.h *.h

clang_n:
	# cp ../materials/linters/.clang-format .
	clang-format -n  */*.h */*/*.h *.h
	clang-format -n  */*.c */*/*.c

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="valgrind.log" ./s21_string_tests