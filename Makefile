FLAGS = -Wall -lallegro
OBJFILES = main.o Manager.o Utils.o Game.o
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJFILES)
	gcc $(FLAGS) -o $(TARGET) $(OBJFILES)

run:	$(TARGET)
	./$(TARGET)
	rm -f $(OBJFILES)

clear: 
	rm -f $(OBJFILES) $(TARGET) *~