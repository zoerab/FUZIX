.SUFFIXES: .c .rel

CC = fcc
CFLAGS = -DTINY
COPT = -O2

OBJS = initials.rel data.rel error.rel expr.rel function.rel gen.rel io.rel \
       lex.rel main.rel preproc.rel primary.rel stmt.rel struct.rel sym.rel while.rel

OBJ_Z80 = codez80.rel
OBJ_8080 = code8080.rel
OBJ_6801 = code6801.rel
OBJ_6809 = code6809.rel

OBJ_COPT = copt.rel

INC = data.h defs.h prototype.h

OBJS_ALL = $(OBJS) $(OBJ_Z80) $(OBJ_8080)
all:    scc6801 scc6809 scc8080 sccz80 copt

sccz80: $(OBJS) $(OBJ_Z80)
	$(CC) -o sccz80 --nostdio $(OBJS) $(OBJ_Z80)

scc8080: $(OBJS) $(OBJ_8080)
	$(CC) -o scc8080 --nostdio $(OBJS) $(OBJ_8080)

scc6801: $(OBJS) $(OBJ_6801)
	$(CC) -o scc6801 --nostdio $(OBJS) $(OBJ_6801)

scc6809: $(OBJS) $(OBJ_6809)
	$(CC) -o scc6809 --nostdio $(OBJS) $(OBJ_6809)

copt:	$(OBJ_COPT)
	$(CC) -o copt $(OBJ_COPT)

clean:
	rm -f $(OBJ) scc8080 sccz80 scc6801 scc6809 *.rel *~

.c.rel:
	$(CC) $(COPT) $(CFLAGS) -c $< -o $@

$(OBJS_ALL) : $(INC)
