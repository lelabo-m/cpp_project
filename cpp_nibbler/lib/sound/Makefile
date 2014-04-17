NAME    =       libsoundplayer.so

REP_SRC =       src/

SRCS    =	$(REP_SRC)libsound.cpp \

OBJS    =	$(SRCS:.cpp=.o)

CXXFLAGS  +=    -I header/ -W -Wall -Wextra -fPIC

LIB	=	../libso/libfmodex64.so -shared

CC      =       g++

RM      =       rm -f

$(NAME) :	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CXXFLAGS) $(LIB)
		cp ${NAME} ../libso

all     :	$(NAME)

clean   :
		$(RM) $(OBJS)

fclean  :       clean
		$(RM) $(NAME)

re      :       fclean all
