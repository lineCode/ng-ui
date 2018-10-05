CXX 	:= g++
CFLAG	:= -ldl -lpthread -lX11 -lXrandr -lXinerama -lXxf86vm -lXcursor
INC		:= -I./include
LIB 	:= lib/libglfw3.a
OBJS 	:= objs/main.o objs/glad.o
EXEC 	:= main

all : $(OBJS)
	$(CXX) $^ $(LIB) $(INC) $(CFLAG) -o $(EXEC)

objs/main.o : main.cpp
	$(CXX) -c $^ $(INC) -o $@

objs/glad.o : glad.c
	$(CXX) -c $^ $(INC) -o $@

clean :
	rm -f $(OBJS)
	rm -f $(EXEC)