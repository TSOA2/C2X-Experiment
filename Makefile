CC     := gcc
CFLAGS := -std=c2x -Wall -Werror -fsanitize=leak

OUT    := experiment
SRC    := main.c

all: $(OUT)

run: $(OUT)
	./$(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(OUT)
