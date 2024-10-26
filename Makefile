CC = gcc
SRCS = main.c utils.c OBJS = $(SRCS:.c=.o)
TARGET = myprogram
all: $(TARGET)
%.o: %.c ( C C ) − c &lt; -o $@
headers_install: mkdir -p ( I N S T A L L D I R ) c p ∗ . h (INSTALL_DIR)
clean: rm -f ( O B J S ) (TARGET)
install: headers_install
.PHONY: all clean headers_install install