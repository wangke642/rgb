CC=g++
TARGETDIR=./bin
TARGET=$(TARGETDIR)/librgb2yuv.so
CFLAG+=-fPIC -shared
CFLAG+=-I ./inc
OBJECT=./src/*.cpp
LIBS=/lib

all:
	@$(CC) -o $(TARGET) $(OBJECT) $(CFLAG)
	@echo Generated $(TARGET)
test:
	@$(MAKE) -C demo
install:
	@cp $(TARGET) $(LIBS)
	@echo Installed $(TARGET) to $(LIBS)
clean:
	@rm $(TARGET) -rf
	@echo Cleaned $(TARGET)
