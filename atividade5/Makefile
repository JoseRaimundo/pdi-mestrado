include Makefile.top

MODULE     = main

VERSION    = 0.1

# caminho dos arquivos headers necessarios
CFLAGS = -I$(INCDIR)/ \
        -I/usr/local/include/\
        -I/usr/include/\
		-Iinclude/\
		-lopencv_highgui\
		-lopencv_core\

CFLAGS += -g -ggdb -fPIC

# caminho das bibliotecas necessarias
LDFLAGS = \
	-L/usr/local/lib\
	-lopencv_highgui\
	-lopencv_core\
	-lopencv_videoio\
	-lopencv_video\
	-lopencv_imgproc\
	-lopencv_imgcodecs\
        #-L../../../common/xml/bin/\

HEADERS = \
        #lavidcine/player/controller/ElementaryPlayerConnectionManager.h\

SOURCES = \
	Common.cpp\
        main.cpp

 #ElementaryPlayerConnectionManager.cpp\

## TESTS ##
# nome dos arquivos que compoe os examples
EXAMPLES_TESTS  =  \
                #source.cpp \

# nome dos arquivos que compoe os testes unitarios
UNIT_TESTS      =  \
                #source.cpp \

# headers necessarios para compilacao dos testes
CFLAGS_TESTS    = \
                $(CFLAGS) \

# bibliotecas necessarias para compilar o teste unitario do componente
LDFLAGS_TESTS   = \
                $(LDFLAGS) \
                -L$(BINDIR) -l$(COMPONENT) \
        		-lcppunit \


# tipos de extensoes que serao tratadas pelo sistema de build
.SUFFIXES: .cpp .o .h

include Makefile.build

default: all 

	
	
	