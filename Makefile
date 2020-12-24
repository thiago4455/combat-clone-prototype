FLAGS = -Wall -lallegro -lallegro_image
OBJFILES = main.o Manager.o Utils.o Game.o
TARGET = game

all: $(TARGET)

$(TARGET): $(addprefix src/, $(OBJFILES))
	gcc $(FLAGS) -o $(TARGET) $(addprefix src/, $(OBJFILES))

run:	$(TARGET)
	./$(TARGET)
	rm -f $(OBJFILES)

clear: 
	rm -f  $(addprefix src/, $(OBJFILES)) $(TARGET) *~