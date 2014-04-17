NAME		=	choose_your_lib

RM		=	rm -rf

CC		=	g++

SRCS		=	Graphic.cpp \
			main.cpp \

LIBFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS	=	-Wall -Wextra


all:			$(NAME)

$(NAME):		$(OBJS)
			$(CC) $(SRCS) -o $(NAME) $(LIBFLAGS)
			cp $(NAME) ..
clean:			
			@$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)
			$(RM) ../$(NAME)

re:			fclean all

allc:			all clean
