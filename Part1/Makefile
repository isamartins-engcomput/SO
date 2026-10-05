# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lpthread

# Nome do executável e do arquivo fonte
TARGET = busca_thread
SRC = busca_thread.c

# Alvos que não são arquivos físicos
.PHONY: all run clean

# Compila o programa
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Regra para compilar e rodar o programa automaticamente
run: all
	./$(TARGET)

# Regra para limpar os arquivos compilados
clean:
	rm -f $(TARGET)