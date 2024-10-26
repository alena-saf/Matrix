GCC = g++ -Wall -Werror -Wextra -std=c++17
LIBS = -lgtest -lpthread -lm
SRC = functions/*.cc matrix.h
TEST_SRC= tests/main.cc tests/*.h

all: clean s21_matrix_oop.a check valgrind gcov_report

s21_matrix_oop.a:
	${GCC} -c ${SRC}
	ar rcs libs21_matrix_oop.a *.o
	rm *.o
	ranlib libs21_matrix_oop.a

test: clean s21_matrix_oop.a
	${GCC} ${TEST_SRC} -o test -L. -ls21_matrix_oop ${LIBS}
	./test

valgrind: clean s21_matrix_oop.a
	${GCC} ${TEST_SRC} -o test -L. -ls21_matrix_oop ${LIBS}
	valgrind --tool=memcheck --leak-check=yes ./test

gcov_report: clean
	${GCC} --coverage functions/*.cc tests/main.cc -o test ${LIBS}
	./test
	lcov -t "test" -c -d . -o test_report.info --rc lcov_branch_coverage=1
	lcov --remove test_report.info '*c++/*' '*gtest/*' '*tests/*' --output-file test_report.info
	genhtml -o report test_report.info
	rm -rf *.o *.a *.gch *.gcno *.gcda test
	open ./report/index.html

clean:
	rm -rf *.o *.a *.out *.gcda *.gcno *.info .info *.gch ./report ./test

check:
	clang-format -n functions/* *.h tests/*
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ functions/* *.h tests/*

correct:
	clang-format -i functions/* *.h tests/*