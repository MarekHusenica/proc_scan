CC=gcc
CFLAGS=-std=c11 -g -Wall -Wextra -Werror=return-type
PROGRAM=proc_scan

SRC_DIR=src
OBJS=main.o d_linked_list.o

VENV=.venv

VALGRIND=valgrind
VFLAGS=--leak-check=full --show-leak-kinds=all --error-exitcode=1

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)

main.o: $(SRC_DIR)/main.c $(SRC_DIR)/d_linked_list.h
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $(SRC_DIR)/main.c

d_linked_list.o: $(SRC_DIR)/d_linked_list.c $(SRC_DIR)/d_linked_list.h
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $(SRC_DIR)/d_linked_list.c

linked_lib.so:
	$(CC) -fPIC -shared -I$(SRC_DIR) -o linked_lib.so $(SRC_DIR)/d_linked_list.c

venv: $(VENV)/bin/activate

$(VENV)/bin/activate:
	python3 -m venv $(VENV)
	$(VENV)/bin/pip install pytest

test: all linked_lib.so venv
	$(VENV)/bin/python -m pytest tests/ -v

memcheck: $(PROGRAM)
	$(VALGRIND) $(VFLAGS) ./$(PROGRAM) > /dev/null
	@echo "Memory check passed!"

clean:
	rm -f *.o *.so $(PROGRAM)
	rm -rf .pytest_cache
	find . -type d -name "__pycache__" -exec rm -rf {} +

distclean: clean
	rm -rf $(VENV)