NAME		=	lib_nibbler_allegro.so

RM		=	rm -rf

CC		=	g++

SRCS		=	src/Graphic.cpp \

INC		=	-I ../../game/header -I./header -I ../../game/loader

INC		+=	-I ../../game/timer -I ../../game/patern

LDFLAGS		=	-shared -fPIC  ${INC}

CXXFLAGS	=	-Wall -Wextra -fPIC ${INC}

all:			$(NAME)

$(NAME):		$(OBJS)
			$(CC) $(SRCS) -o $(NAME) $(LDFLAGS)  `pkg-config --libs allegro-5.0 --libs allegro_dialog-5.0 --libs allegro_primitives-5.0 --libs allegro_image-5.0`
			cp $(NAME) ../libso/


clean:
			$(RM) $(OBJS)

fclean:			clean
			$(RM) ../libso/$(NAME)
			$(RM) $(NAME)

re:			fclean all

allc:			all clean
