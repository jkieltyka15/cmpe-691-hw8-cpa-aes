IDIR = ./inc

CC = g++
CFLAGS = -std=c++11 -I$(IDIR) -Wall -lm

SDIR = ./src
BUILD = ./build
BDIR = $(BUILD)/bin
ODIR = $(BUILD)/obj

_DEPS = aes_sbox.h correlation_coefficient.h ciphertext.hpp
DEPS = $(patsubt %,$(IDIR)/%,$(_DEPS))

_OBJ_cpa = cpa.o aes_sbox.o correlation_coefficient.o ciphertext.o
OBJ_cpa = $(patsubst %,$(ODIR)/%,$(_OBJ_cpa))

$(shell mkdir -p $(BUILD))
$(shell mkdir -p $(BDIR))
$(shell mkdir -p $(ODIR))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: cpa

cpa: $(OBJ_cpa)
	$(CC) -o $(BDIR)/$@ $(OBJ_cpa) $(CFLAGS)

.PHONY: clean

clean:
	@rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~