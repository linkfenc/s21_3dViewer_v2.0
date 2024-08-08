CC = g++
CFLAGS := -lstdc++ -std=c++17 -Wall -Werror -Wextra -g

EXECUTABLE = test

UNAME = $(shell uname)

OPEN_REPORT :=
LEAKS :=

ifeq ($(UNAME), Linux)
OPEN_REPORT += xdg-open
LEAKS += valgrind --leak-check=full -s -q --track-origins=yes
endif

ifeq ($(UNAME), Darwin)
OPEN_REPORT += open
LEAKS += leaks -atExit --
endif

SOURCES = ./tests/test.cc ./model/matrix_t.cc ./model/parser_file.cc

all: tests

install: uninstall
	mkdir -p build
	cd build && qmake ./../view/3d_viewer2/3d_viewer2.pro && make
	@clear

uninstall:
	@rm -rf ./build

clean:
	@rm -rf $(EXECUTABLE)
	@rm -rf a.outs
	@rm -rf *.gcno *.gcda report
	@rm -rf tests.info
	@rm -rf test_out.txt
	@rm -rf report.info
	@rm -rf ./build
	@rm -rf ./dist

tests: clean
	@$(CC) $(CFLAGS) $(SOURCES) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

gcov_report: clean
	@$(CC) $(CFLAGS) $(SOURCES) -lgtest_main -lgtest -o $(EXECUTABLE) --coverage
	@./$(EXECUTABLE)
	mkdir report
	lcov -t "./test" -o report.info --no-external -c -d .
	genhtml -o report report.info
	$(OPEN_REPORT) ./report/index.html
	rm -rf *.gcno *gcda *.gcov

style:
	clang-format -n --style=google tests/*.cc
	clang-format -n --style=google model/*.cc
	clang-format -n --style=google model/*.h
	clang-format -n --style=google controller/*.cc
	clang-format -n --style=google controller/*.h
	clang-format -n --style=google view/3d_viewer2/*.cc
	clang-format -n --style=google view/3d_viewer2/*.h

clang_format:
	clang-format -i --style=google tests/*.cc
	clang-format -i --style=google model/*.cc
	clang-format -i --style=google model/*.h
	clang-format -i --style=google controller/*.cc
	clang-format -i --style=google controller/*.h
	clang-format -i --style=google view/3d_viewer2/*.cc
	clang-format -i --style=google view/3d_viewer2/*.h

dvi:
	$(OPEN_REPORT) ./README.md

dist: clean install
	mkdir -p dist
	cp -R build/3d_viewer2 dist && cp README.md dist
	cd dist && tar cvzf 3d_viewer2.tgz *
	cd dist && rm -rf 3d_viewer2 README.md

leaks_check: tests
	@$(LEAKS) ./$(EXECUTABLE)

valgrind_test: tests
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./test 2> test_out.txt
