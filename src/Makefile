CC = gcc
SRC_DIR = .
UNAME = $(shell uname -s)
CFLAGS=-Wall -Wextra -std=c11 -lm
PACKAGE = `pkg-config --cflags --libs gtk4`
LIBS = `pkg-config --libs gtk4`
BUILD_DIR = code/build
DIST_NAME = SmartCalc-v1.0
EXE = $(BUILD_DIR)/SmartCalc_app
ifeq ($(UNAME),Darwin)
	LIN_FLAGS=-lcheck -lm -lpthread -fprofile-arcs
	OPEN = open
	MEMORY_TEST = leaks
# Ubuntu
else ifneq (,$(wildcard /etc/lsb-release))
	LIN_FLAGS=-lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs
	OPEN = xdg-open
	MEMORY_TEST = valgrind
# Other linux
else ifeq ($(UNAME),Linux)
	LIN_FLAGS=-lcheck -lm -lpthread -lrt -fprofile-arcs
	OPEN = xdg-open
	MEMORY_TEST = valgrind
endif

ifeq ($(PREFIX), )
	PREFIX:=/usr/local
endif

GCOVFLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS = -fprofile-arcs --coverage
OBJ_DIR = code/obj
TEST_DIR = code/tests
CODE_DIR = code
REPORT_DIR = code/report
TEX_FILE = code/doc/info.tex
INSTALL_DIR = $(PREFIX)/SmartCalc
CHECK=-lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs

#SOURCES:= rpn.c
TESTS:= $(TEST_DIR)/test*.c

SRCS = $(SRC_DIR)/s21_smartcalc.c $(SRC_DIR)/rpn.c 
SOURCES:= rpn.c
OBJS = $(OBJ_DIR)/s21_smartcalc.o $(OBJ_DIR)/rpn.o 

vpath %.c $(SOURCES) : $(TESTS)
vpath %.o $(OBJ_DIR)

all : clean style gcov_report dvi build copy

build: clean $(BUILD_DIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(CODE_DIR)/rpn.c -o $(OBJ_DIR)/rpn.o -lm
	$(CC) $(CFLAGS) -c $(CODE_DIR)/s21_smartcalc.c -o $(OBJ_DIR)/s21_smartcalc.o $(PACKAGE) -lm
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE) $(LIBS) -lm

copy:
	cp $(EXE) .
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(INC_DIR) $< -o $@ $(PACKAGE) 
	
install: clean build $(INSTALL_DIR) dvi
	mv info.pdf $(PREFIX)/SmartCalc/info.pdf
	cp $(EXE) $(PREFIX)/SmartCalc/

run:
	$(PREFIX)/SmartCalc/SmartCalc_app
uninstall:
	rm -rf $(PREFIX)/SmartCalc

dvi:
	texi2dvi -q --pdf -c $(TEX_FILE)
	
dist: clean build dvi
	mkdir $(DIST_NAME)
	mv info.pdf $(DIST_NAME)/info.pdf
	cp $(EXE) $(DIST_NAME)/SmartCalc_app
	tar -zcvf $(DIST_NAME).tar.gz $(DIST_NAME)
	rm -rrf $(DIST_NAME)

# Сборка приложения для запуска тестов
test: clean $(OBJ_DIR)
	$(CC) $(CFLAGS) -c --coverage $(CODE_DIR)/rpn.c -o $(OBJ_DIR)/rpn.o -lm
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test.c -o $(OBJ_DIR)/$(TEST_DIR)/test.o 
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test1.c -o $(OBJ_DIR)/$(TEST_DIR)/test1.o 
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test2.c -o $(OBJ_DIR)/$(TEST_DIR)/test2.o 
	$(CC) $(CFLAGS) -o $(TEST_DIR)/test $(OBJ_DIR)/rpn.o $(OBJ_DIR)/$(TEST_DIR)/test.o $(OBJ_DIR)/$(TEST_DIR)/test1.o $(OBJ_DIR)/$(TEST_DIR)/test2.o $(CHECK)
	./$(TEST_DIR)/test

# Создание временной папки для .o-файлов
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(TEST_DIR)

gcov_report: test $(REPORT_DIR)
	rm -f $(TEST_DIR)/*.g*
	gcovr -r . --html --html-details -o $(REPORT_DIR)/report.html
	open $(REPORT_DIR)/report.html

# Создание временной папки для отчетов
$(REPORT_DIR):
	@mkdir -p $(REPORT_DIR)
	
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	
$(INSTALL_DIR):
	@mkdir -p $(INSTALL_DIR)
	
style:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(CODE_DIR)/*.c $(CODE_DIR)/*.h $(TEST_DIR)/*.c $(TEST_DIR)/*.h
	rm .clang-format


format:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(CODE_DIR)/*.c $(CODE_DIR)/*.h $(TEST_DIR)/*.c $(TEST_DIR)/*.h
	rm .clang-format

# Удаление временных файлов и папок	
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(REPORT_DIR)
	rm -rf $(BUILD_DIR)
	rm -f SmartCalc_app
	rm -f test
	rm -f *.a
	rm -f *.o
	rm -f *.pdf
	rm -f $(TEST_DIR)/*.g*
	rm -f *.gc*
	rm -f *.log 
	rm -f $(TEST_DIR)/test
	rm -f G*
	rm -rf $(DIST_NAME)
	rm -rf $(DIST_NAME).*

