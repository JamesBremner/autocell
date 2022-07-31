#source file search paths
VPATH = ./src 

	# compiler include search paths
INCS = -I./src \
	-I../ravencode/pub/src \
	-I../raven-set \
	-I../boost/boost1_78 

LIBS = \
	-lgdiplus -lgdi32 -lcomdlg32 -lstdc++fs \
	#-mwindows

static_link_flags = -static-libstdc++ -static-libgcc -static

# folders
ODIR = ./.vscode/obj
RDIR = ../ravencode/pub/src

OPT = -g
CCflags = -std=c++17 $(OPT) -D_mingw_

# sources
OBJtest = \
	$(ODIR)/main.o $(ODIR)/autocell.o
OBJlife = \
	$(ODIR)/life.o $(ODIR)/cConway.o $(ODIR)/autocell.o
### COMPILE

$(ODIR)/%.o: %.cpp  
	g++  $(CCflags) \
	-c -o $@ $< $(INCS)

test: $(OBJtest)
	g++ $(OPT) \
	-o bin/test.exe $^  \
	$(static_link_flags) $(LIBS)

life: $(OBJlife)
	g++ $(OPT) \
	-o bin/test.exe $^  \
	$(static_link_flags) $(LIBS)

.PHONY: clean
clean:
	del /q .vscode\\obj\\*.o

