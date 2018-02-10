OBJ_DIR=obj
TEST_INC_DIRS=main/include test/include
INC_VAL=$(patsubst %,-I%,$(TEST_INC_DIRS))
TEST_SRC_DIR=test

test: test_exe
	./test_exe

test_exe: $(OBJ_DIR)/*.o
	g++ -o $@ $^ -lcppunit

$(OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp $(TEST_INC_DIRS)/%.hpp
	mkdir -p $(OBJ_DIR)
	g++ -std=c++11 $(TEST_SRC_DIR)/*.cpp -c -o $@ $(INC_VAL) -lcppunit

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR)
	rm -f test_exe
