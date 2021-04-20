CC			= gcc
TARGET1		= miniShell
MAIN_SOURCE1	= miniShell.cpp
TARGET2		= program1
MAIN_SOURCE2	= program1.cpp
TARGET3		= program2
MAIN_SOURCE3	= program2.cpp
TARGET4		= program3
MAIN_SOURCE4	= program3.cpp

all: $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)

$(TARGET1): 
	$(CC) -o $(TARGET1) $(MAIN_SOURCE1) -lstdc++
$(TARGET2): 
	$(CC) -o $(TARGET2) $(MAIN_SOURCE2) -lstdc++
$(TARGET3): 
	$(CC) -o $(TARGET3) $(MAIN_SOURCE3) -lstdc++
$(TARGET4): 
	$(CC) -o $(TARGET4) $(MAIN_SOURCE4) -lstdc++

clean:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)