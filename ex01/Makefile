NAME		:= ex01

SRCS		:= main.cpp \
			   Span.cpp

CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -pedantic
OBJDIR		:= obj
OBJS		:=	$(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:	%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

check:
	@echo "Checking $(SRCS) for banned patterns (printf, alloc, free, using namespace, friend)..."
	@grep -n 'printf\|alloc\|free\|using namespace\|friend' $(SRCS) \
		&& echo "RESULT: \033[1;31mKO\033[0m (banned pattern found)" && exit 1 \
		|| echo "RESULT: \033[1;32mOK\033[0m (no banned patterns)"

run:re
	clear
	valgrind --leak-check=full --show-leak-kinds=all -q ./$(NAME)

.PHONY: all clean fclean re check run
