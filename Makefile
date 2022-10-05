SRCS			= main.cpp 
OBJS			= $(SRCS:.cpp=.o)

CXX				= c++
RM				= rm -f
CXXFLAGS		= -Wall -Wextra -Werror -I. -std=c++98 -pedantic -Wshadow 
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
		

.PHONY:			all clean fclean re
