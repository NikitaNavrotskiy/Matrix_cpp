CC=gcc
FLAGS=-Wall -Werror -Wextra --std=c++17 -O3 -lstdc++

SRC=my_matrix_oop.cc
HEADERS=my_matrix_oop.h 
OBJ=$(patsubst %.cc, %.o, $(SRC))
NAME=my_matrix_oop.a

TEST_EXEC=my_matrix_oop_test
TEST_FLAGS=-lgtest -lpthread
TEST_SRC=test/test.cc

CLANG_FORMAT_FILES=$(SRC) $(HEADERS) $(TEST_SRC) 


all: clean $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $<
	ranlib $@
	rm -rf $<


%.o: %.cpp 
	$(CC) $(FLAGS) -c $< -o $@ 

clean:
	rm -rf $(OBJ) $(NAME) $(TEST_EXEC) .clang-format
	rm -rf report
	rm -rf *gcov.info *gcda *gcno

test_executable: $(NAME)
	g++ $(FLAGS) $(TEST_SRC) $< -o $(TEST_EXEC) $(TEST_FLAGS)

test: test_executable
	./$(TEST_EXEC)


gcov_report : clean
	g++ $(FLAGS) --coverage $(SRC) $(TEST_SRC) -o $(TEST_EXEC) $(TEST_FLAGS)
	./$(TEST_EXEC)
	lcov -t "$(TEST_EXEC)" -o matrix_gcov.info -c -d .
	genhtml -o report matrix_gcov.info
	open report/index.html
	google-chrome report/index.html
