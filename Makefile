# Variables #
#############
CPP = g++
CPPFLAGS = -std=c++11 -fPIC -pedantic -Wall -Werror -g
NAME = smtpclient
SOURCE = src/args.cpp src/client.cpp src/main.cpp src/msg.cpp src/signal.cpp src/status.cpp
LOGIN = xuchyt03

# Rules #
#########
all:
	$(CPP) $(CPPFLAGS) -o $(NAME) $(SOURCE)

run:
	./$(NAME)

# Phony #
#########
.PHONY: clean pack
clean:
	-rm $(NAME)
	-rm $(LOGIN).tar

pack:
	tar cf $(LOGIN).tar *
