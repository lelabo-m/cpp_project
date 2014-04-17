NAME		=	lib_nibbler_opengl.so

RM		=	rm -rf

CC		=	g++

SRCS		=	src/Graphic.cpp \

INC             =       -I ../../game/header -I./header -I ../../game/loader

INC             +=      -I ../../game/timer -I ../../game/patern

LDFLAGS		=	-shared -fPIC

LIBFLAGS	=	-lrt -lGL -lGLU -lglut -lSDL -lSDL_image $(INC)

CXXFLAGS	=	-Wall -Wextra -fPIC -g



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
