NAME    =       nibbler

REP_SRC =       game/

SRCS    =	$(REP_SRC)exception/gameexception.cpp \
		$(REP_SRC)timer/timecounter.cpp \
		$(REP_SRC)loader/loader.cpp \
		$(REP_SRC)snake/snake.cpp \
		$(REP_SRC)event/event.cpp \
		$(REP_SRC)map/map.cpp \
		$(REP_SRC)nibbler.cpp \
		$(REP_SRC)nibbler_manager.cpp \
		$(REP_SRC)main.cpp

OBJS    =	$(SRCS:.cpp=.o)

INC	=	-I $(REP_SRC)header/ -I $(REP_SRC)/loader/ -I $(REP_SRC)/patern/
INC	+=	-I $(REP_SRC)/timer/

CXXFLAGS	+=  $(INC) -W -Wall -Wextra

LDFLAGS		+= -ldl -export-dynamic

CC      =       g++

RM      =       rm -f

$(NAME) :	$(OBJS)
		$(CC) -g $(OBJS) -o $(NAME) $(CXXFLAGS) $(LDFLAGS)
		make -C lib/allegro
		make -C lib/sfml
		make -C lib_choose/
		make -C lib/opengl

all     :	$(NAME)

clean   :
		$(RM) $(OBJS)
		make clean -C lib/allegro
		make clean -C lib/sfml
		make clean -C lib_choose/
		make clean -C lib/opengl

fclean  :       clean
		$(RM) $(NAME)
		make fclean -C lib/allegro
		make fclean -C lib/sfml
		make fclean -C lib_choose/
		make fclean -C lib/opengl

re      :       fclean all
