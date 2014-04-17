NAME		=	lib_nibbler_sfml.so

RM		=	rm -rf

CC		=	g++

SRCS		=	Graphic.cpp \

INC             =       -I ../../game/header -I ./ -I ../../game/loader

INC             +=      -I ../../game/timer -I ../../game/patern

LDFLAGS		=	-shared -fPIC

LIBFLAGS	=	$(INC) -lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS	=	-Wall -Wextra -fPIC



all:			$(NAME)

$(NAME):		$(OBJS)
			$(CC) $(SRCS) -o $(NAME) $(LIBFLAGS) $(LDFLAGS)
			cp $(NAME) ../libso/
clean:
			$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)
			$(RM) ../libso/$(NAME)

re:			fclean all

allc:			all clean
