CC	= g++
TARGET	= P0
OBJS	= tree.o main.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: main.cpp
	$(CC) -std=c++11 -c main.cpp

tree.o: tree.cpp tree.h
	$(CC) -std=c++11 -c tree.cpp

.PHONY: clean
clean:
	/bin/rm -f *.o *.preorder *.inorder *.postorder $(TARGET)
