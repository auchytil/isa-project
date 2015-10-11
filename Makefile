# Variables #
#############
CPP = g++
CPPFLAGS = -std=c++11 -fPIC -pedantic -Wall -Werror -g
NAME = smtpclient
SOURCE = src/args.cpp src/client.cpp src/main.cpp src/msg.cpp

# Rules #
#########
all:
	$(CPP) $(CPPFLAGS) -o $(NAME) $(SOURCE)

run:
	./$(NAME)

# Phony #
#########
.PHONY: clean
clean:
	-rm $(NAME)
