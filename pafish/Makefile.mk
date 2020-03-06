
CC        = gcc.exe
LINK      = gcc.exe
WINDRES   = windres.exe
OBJ       = Objects/MingW/chutil.o Objects/MingW/common.o Objects/MingW/utils.o Objects/MingW/debuggers.o Objects/MingW/sandboxie.o \
            Objects/MingW/vbox.o Objects/MingW/gensandbox.o Objects/MingW/wine.o Objects/MingW/vmware.o \
            Objects/MingW/qemu.o Objects/MingW/hooks.o Objects/MingW/cpu.o Objects/MingW/cuckoo.o Objects/MingW/bochs.o \
            # Objects/MingW/pafish_private.res
LINKOBJ   = $(OBJ)
LIBS      = -lwsock32 -liphlpapi -lsetupapi -lmpr -lole32 -lwbemuuid -loleaut32 -lws2_32 -s
INCS      =
# BIN       = Output/MingW/pafish.exe
BIN       = Output/MingW/pafish.dll
CFLAGS    = $(INCS) -Wall -Wextra -Wpedantic -O0

all: $(BIN)

clean:
	del /Q Objects\MingW\*.o
	del /Q Objects\MingW\*.res
	del /Q Output\MingW\*.exe

$(BIN): $(OBJ)
	$(LINK) $(LINKOBJ) -shared -o "$(BIN)" $(LIBS)

Objects/MingW/chutil.o: $(GLOBALDEPS) chutil.c
	$(CC) -c chutil.c -o Objects/MingW/chutil.o $(CFLAGS)

Objects/MingW/common.o: $(GLOBALDEPS) common.c
	$(CC) -c common.c -o Objects/MingW/common.o $(CFLAGS)

Objects/MingW/utils.o: $(GLOBALDEPS) utils.c
	$(CC) -c utils.c -o Objects/MingW/utils.o $(CFLAGS)

Objects/MingW/debuggers.o: $(GLOBALDEPS) debuggers.c
	$(CC) -c debuggers.c -o Objects/MingW/debuggers.o $(CFLAGS)

Objects/MingW/sandboxie.o: $(GLOBALDEPS) sandboxie.c
	$(CC) -c sandboxie.c -o Objects/MingW/sandboxie.o $(CFLAGS)

Objects/MingW/vbox.o: $(GLOBALDEPS) vbox.c
	$(CC) -c vbox.c -o Objects/MingW/vbox.o $(CFLAGS)

Objects/MingW/gensandbox.o: $(GLOBALDEPS) gensandbox.c
	$(CC) -c gensandbox.c -o Objects/MingW/gensandbox.o $(CFLAGS)

Objects/MingW/wine.o: $(GLOBALDEPS) wine.c
	$(CC) -c wine.c -o Objects/MingW/wine.o $(CFLAGS)

Objects/MingW/vmware.o: $(GLOBALDEPS) vmware.c
	$(CC) -c vmware.c -o Objects/MingW/vmware.o $(CFLAGS)

Objects/MingW/qemu.o: $(GLOBALDEPS) qemu.c
	$(CC) -c qemu.c -o Objects/MingW/qemu.o $(CFLAGS)

Objects/MingW/hooks.o: $(GLOBALDEPS) hooks.c
	$(CC) -c hooks.c -o Objects/MingW/hooks.o $(CFLAGS)

Objects/MingW/cpu.o: $(GLOBALDEPS) cpu.c
	$(CC) -c cpu.c -o Objects/MingW/cpu.o $(CFLAGS)

Objects/MingW/cuckoo.o: $(GLOBALDEPS) cuckoo.c
	$(CC) -c cuckoo.c -o Objects/MingW/cuckoo.o $(CFLAGS)

Objects/MingW/bochs.o: $(GLOBALDEPS) bochs.c
	$(CC) -c bochs.c -o Objects/MingW/bochs.o $(CFLAGS)

# Objects/MingW/pafish_private.res: Objects/MingW/pafish_private.rc
#	$(WINDRES) Objects/MingW/pafish_private.rc --input-format=rc -o Objects/MingW/pafish_private.res -O coff