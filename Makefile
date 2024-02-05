# E89 Pedagogical & Technical Lab
# project:     2023_cpp_game
# created on:  2023-01-05 - 09:34 +0100
# 1st author:  martin.leroy - martin.leroy
# description: Makefile

PRJCT_NAME	=	game.out

ARCH_NAME	=	lib$(NAME).a

SRCS	=	$(shell find src/ -name "*.cpp")

OBJS	=	$(SRCS:.cpp=.o)

CFLAGS	+=	-W -Wall -Wextra -Werror

LDFLAGS	+=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

RM	=	rm -vf

CC	:=	g++

CL	:=	c++

ifdef RELEASE
CFLAGS += -O2
endif

ifdef DEBUG
CFLAGS += -g
endif

all: main

$(ARCH_NAME): 	$(OBJS)
		ar rc $(ARCH_NAME) $(OBJS)

# $(NAME_TEST) :	$(ARCH_NAME) $(OBJS) $(OBJS_TEST)
# 		$(CC) -o $(NAME_TEST) $(OBJS) $(OBJS_TEST) -lcriterion

main:	$(ARCH_NAME) src/main.o
	$(CC) $(CFLAGS) $(LDFLAGS) src/main.o $(ARCH_NAME) -o $(PRJCT_NAME) $(LDFLAGS)

main2:	$(ARCH_NAME) src/main.o
	$(CL) $(CFLAGS) $(LDFLAGS) src/main.o $(ARCH_NAME) -o $(PRJCT_NAME) $(LDFLAGS)

sfml:	$(ARCH_NAME) src/sfml_main.o
	$(CC) $(CFLAGS) $(LDFLAGS) src/sfml_main.o $(ARCH_NAME) -o sfml.out $(LDFLAGS)

save:	fclean
	git status
	git add *
	git commit -m "$(NAME) Sauvegarde"
	git push
	git status

clean~:
	@$(RM) *~ */*~ */*/*~

cleano:
	@$(RM) $(OBJS) src/main.o

fclean: clean~ cleano
	@$(RM) $(ARCH_NAME) $(PRJCT_NAME)

re: fclean all

re2: fclean main2

# Theses rules do not directly map to a specific file
.PHONY: all clean~ cleano fclean re save main main2

