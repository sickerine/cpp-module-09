CC = c++
NAME = PmergeMe
FLAGS = -Wall -Werror -Wextra -std=c++98 
FILES = main.cpp PmergeMe.cpp
FILES_O = $(FILES:.cpp=.o)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(FILES_O)
	$(CC) $(FLAGS) $(FILES_O) -o $(NAME) 

all: $(NAME)

clean:
	rm -rf $(FILES_O)
	
fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re