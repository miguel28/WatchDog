# Project: SDLEX win
# Makefile created by Dev-C++ 4.9.9.2

CPP  = g++
CC   = gcc
WINDRES = windres.exe
RES  = hid-libusb.o
OBJ  = main.o USBInterfaceClass.o MkLib/MikeLibrary.o MkLib/MK_Backgrounds.o MkLib/MK_Graphics.o MkLib/MK_Sprites.o MkLib/MK_Video.o MkLib/SDL_rotozoom.o MkLib/MK_Math.o MkLib/MK_Text.o $(RES)
LINKOBJ  = main.o USBInterfaceClass.o MkLib/MikeLibrary.o MkLib/MK_Backgrounds.o MkLib/MK_Graphics.o MkLib/MK_Sprites.o MkLib/MK_Video.o MkLib/SDL_rotozoom.o MkLib/MK_Math.o MkLib/MK_Text.o $(RES)
LIBS = -lSDLmain -lSDL -lSDL_image -lSDL_ttf `pkg-config libusb-1.0 libudev --libs`
INCS = 
CXXINCS = 
BIN  = "ControlCarrito"
CXXFLAGS = $(CXXINCS)   -O1
CFLAGS = $(INCS)   -O1
RM = rm -f

LIBS2      = `pkg-config libusb-1.0 libudev --libs` 
INCLUDES ?= -I./hidapi `pkg-config libusb-1.0 --cflags`

.PHONY: all all-before all-after clean clean-custom

all: all-before "ControlCarrito" all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)
	cp ./Temp/hid-libusb.o hid-libusb.o

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "ControlCarrito" $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

USBInterfaceClass.o: USBInterfaceClass.cpp
	$(CPP) -c USBInterfaceClass.cpp -o USBInterfaceClass.o $(CXXFLAGS) $(INCLUDES) $(LIBS)

hid-libusb.o: hid-libusb.c
	$(CC) -c hid-libusb.c -o hid-libusb.o $(CXXFLAGS)

MkLib/MikeLibrary.o: MkLib/MikeLibrary.cpp
	$(CPP) -c MkLib/MikeLibrary.cpp -o MkLib/MikeLibrary.o $(INCLUDES) $(LIBS2)

MkLib/MK_Backgrounds.o: MkLib/MK_Backgrounds.cpp
	$(CPP) -c MkLib/MK_Backgrounds.cpp -o MkLib/MK_Backgrounds.o $(CXXFLAGS)

MkLib/MK_Graphics.o: MkLib/MK_Graphics.cpp
	$(CPP) -c MkLib/MK_Graphics.cpp -o MkLib/MK_Graphics.o $(CXXFLAGS)

MkLib/MK_Sprites.o: MkLib/MK_Sprites.cpp
	$(CPP) -c MkLib/MK_Sprites.cpp -o MkLib/MK_Sprites.o $(CXXFLAGS)

MkLib/MK_Video.o: MkLib/MK_Video.cpp
	$(CPP) -c MkLib/MK_Video.cpp -o MkLib/MK_Video.o $(CXXFLAGS)

MkLib/SDL_rotozoom.o: MkLib/SDL_rotozoom.c
	$(CPP) -c MkLib/SDL_rotozoom.c -o MkLib/SDL_rotozoom.o $(CXXFLAGS)

MkLib/MK_Math.o: MkLib/MK_Math.cpp
	$(CPP) -c MkLib/MK_Math.cpp -o MkLib/MK_Math.o $(CXXFLAGS)

MkLib/MK_Text.o: MkLib/MK_Text.cpp
	$(CPP) -c MkLib/MK_Text.cpp -o MkLib/MK_Text.o $(CXXFLAGS)

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CFLAGS) -c $(INCLUDES) $< -o $@
