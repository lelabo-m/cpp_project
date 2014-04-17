##
## Makefile for  in /home/lelabo_m/rendu/cpp_abstractvm
## 
## Made by Marc Le Labourier
## Login   <lelabo_m@epitech.net>
## 
## Started on  Sat Feb 22 18:12:31 2014 Marc Le Labourier
## Last update Sun Mar  2 20:21:06 2014 Marc Le Labourier
##


NAME    =       avm

REP_SRC =       src/

SRCS    =	$(REP_SRC)main.cpp \
		$(REP_SRC)Exception.cpp \
		$(REP_SRC)InputOutput.cpp \
		$(REP_SRC)MotherBoard.cpp \
		$(REP_SRC)Chipset.cpp \
		$(REP_SRC)Instruction.cpp \
		$(REP_SRC)Ram.cpp \
		$(REP_SRC)Operand.cpp \
		$(REP_SRC)Memory.cpp \
		$(REP_SRC)CPU.cpp \

OBJS    =	$(SRCS:.cpp=.o)

CXXFLAGS  +=    -I inc/ -W -Wall -Wextra

CC      =       g++

RM      =       rm -f

$(NAME) :	$(OBJS)
		$(CC) $(SRCS) -o $(NAME) $(CXXFLAGS)

all     :	$(NAME)

clean   :
		$(RM) $(OBJS)

fclean  :       clean
		$(RM) $(NAME)

re      :       fclean all
