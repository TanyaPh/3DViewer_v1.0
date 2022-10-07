.PHONY: all re Back clean check test
#.PHONY если есть файлы с именем как цель, они игнорируются

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
TST_LIBS :=  -lcheck -lm -lpthread
OS := $(shell uname -s)

ifeq ($(OS),Linux)
	CFLAGS+=-D LINUX
else
	ifeq ($(OS),Darwin)
		CFLAGS+=-D MAC
	endif
endif

# all, install, uninstall, clean, dvi, dist, tests, gcov_report

all: tests Back.a s21_matrix.a gcov_report

re: clean tests gcov_report

tests: Back.a s21_matrix.a test.o
	$(CC) $(CFLAGS) test.o Back.a s21_matrix.a $(TST_LIBS) -o test
	@./test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o test.o

Back.a: Back.o
	@ar rcs Back.a Back.o
	ranlib Back.a

Back.o: Back.c
	$(CC) $(CFLAGS) -c Back.c -o Back.o

s21_matrix.a: s21_matrix.o
	@ar rcs s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

s21_matrix.o: s21_matrix.c
	$(CC) $(CFLAGS) -c s21_matrix.c -o s21_matrix.o

gcov_report: gcov_test.info
	@genhtml -o report/ gcov_test.info
	@open report/index.html

gcov_test.info: gcov_test gcov_test.gcda
	@lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test: test.c Back.c
	$(CC) $(CFLAGS) --coverage test.c Back.c s21_matrix.a $(TST_LIBS) -o gcov_test

gcov_test.gcda:
	@chmod +x *
	@./gcov_test

install:
	make clean
	mkdir build
	cd 3D_Viewer && qmake && make && make clean && rm Makefile && cd ../ && mv 3D_Viewer/3D_Viewer.app build

uninstall:
	rm -rf build*

dvi:
	open Read_me.html

dist:
	rm -rf Archive_3D_Viewer.0/
	mkdir Archive_3D_Viewer/
	mkdir Archive_3D_Viewer/src
	cp -r ./build/3D_Viewer.app Archive_3D_Viewer/src/
	tar cvzf Archive_3D_Viewer.tgz Archive_3D_Viewer/
	rm -rf Archive_3D_Viewer/

clean: 
	@rm -rf test gcov_test *.gcno *.gcda *.info report *.{a,o,dSYM,out} $(EXECUTABLE)

style:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.h *.c
	clang-format -n 3D_Viewer/*.h 3D_Viewer/*.cpp
	
valgrind:
	valgrind --leak-check=full --track-origins=yes --trace-children=yes -s ./test

leak:
	CK_FORK=no leaks -atExit -- ./test