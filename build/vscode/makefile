INCS=-I../../src 

test: ../../src/main.cpp
	g++ -g ../../src/main.cpp  ../../src/autocell.cpp \
	-o../../bin/test.exe  $(INCS)
     
life: ../../src/life.cpp
	g++ -g ../../src/life.cpp  ../../src/autocell.cpp \
	-o../../bin/life.exe  $(INCS)

guilife: ../../src/life.cpp
	g++ -g -DGUI \
	../../src/life.cpp  ../../src/cConway.cpp ../../src/autocell.cpp \
	-lgdi32 -lcomdlg32 \
	-o../../bin/life.exe  $(INCS) -I../../../windex/include