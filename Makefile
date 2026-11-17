TARGET = my_ls
OBJ = src/main.c src/my_ls.c src/utils.c src/get_files.c
CFLAGS = -Wall -Wextra -Werror

 all : $(TARGET)

 $(TARGET) : $(OBJ)
	gcc $(CFLAGS) -o $(TARGET) $(OBJ)

 $(OBJ) : $(SRC)
	gcc $(CFLAGS) -c $(SRC)

 clean:
	rm -f *.o

 fclean: clean
	rm -f $(TARGET)

 re: fclean all