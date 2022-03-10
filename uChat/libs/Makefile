# Libraries Makefile

# Libraries
LIBS_DIR = $(wildcard */)
LIBS_FILES = $(LIBS_DIR:%/=%.a)

# Serial list of tasks
PIPELINE = clean libs

BLACK	= \033[30;1m
GREEN 	= \033[32;1m
RED 	= \033[31;1m
YELLOW 	= \033[33;1m
BLUE	= \033[34;1m
VIOLET	= \033[35;1m
CYAN	= \033[36;1m
GRAY	= \033[37;1m

BOLD	= \033[1m
OPACITY	= \033[2m
UNDER	= \033[4m
BLINK	= \033[5m

UNSET 	= \033[0m

PRMPT = [$(GRAY)libs$(UNSET)]


all: $(PIPELINE)

libs: $(LIBS_FILES)

%.a:
	@printf "$(PRMPT) Makefile for $@...\n"
	@make -s -C $(@:%.a=%/)
	@printf "$(PRMPT) Create copy of $@\t"
	@cp -f $(@:%.a=%/)$@ $@
	@printf "$(GREEN)copied$(UNSET)\n"

clean:
	rm -rf *.a

.PHONY: all clean
