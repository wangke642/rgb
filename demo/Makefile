CC=g++
TARGETDIR=./bin
TARGET=$(TARGETDIR)/demo
CFLAG+=-I ../inc
CFLAG+=-I ./inc
LDFLAG+=-L ../bin -lrgb2yuv
OBJECT=./src/*.cpp

all:
	@$(CC) -o $(TARGET) $(OBJECT) $(CFLAG) $(LDFLAG)
	@echo Generated $(TARGET).
clean:
	@rm $(TARGET) -rf
	@echo Cleaned $(TARGET)

