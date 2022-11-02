SRCS			= main_exp.cpp 
OBJS			= $(SRCS:.cpp=.o)

CXX				= c++
RM				= rm -f
CXXFLAGS		= -Wall -Wextra -Werror -I $(INC) -std=c++98 -pedantic -Wshadow 
INC				= ./includes
TESTFLAGS		= -DREAL

NAME			= a.out

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o : %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY: test
test: CXXFLAGS += $(TESTFLAGS) 
test: $(NAME)
		
gtest_set: 
	rm -rf tests/googletest-release-1.12.1
	mkdir -p tests
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
	tar -xvzf release-1.12.1.tar.gz
	rm -rf release-1.12.1.tar.gz
	pwd
	cd ./googletest-release-1.12.1 && cmake . && make
	mv googletest-release-1.12.1 tests
	
GTEST_DIR = tests/googletest-release-1.12.1
TEST_SRCS = tests/src/vector_test.cpp

GTEST_INCLUDES += -I$(GTEST_DIR)/googletest/include
GTEST_LDFLAGS = -L$(GTEST_DIR)/lib
GTEST_LIBS = 	-lgtest \
				-lgtest_main


gtest_run: $(GTEST_DIR) $(NAME) 
	clang++ -std=c++11 -I$(INC) $(GTEST_INCLUDES) \
			$(GTEST_LDFLAGS) $(GTEST_LIBS) $(TEST_SRCS) -o test
	-@./test
	rm -rf test
	

.PHONY:			all clean fclean re
