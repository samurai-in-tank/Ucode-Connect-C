# Client Makefile

# Directories
LIBS_DIR = libs
CLIENT_DIR = client
SERVER_DIR = server

# Serial list of tasks
PIPELINE = libs client server bot_roulette copy done


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

PRMPT = [$(VIOLET)main$(UNSET)]


all: $(PIPELINE)

libs:
	@printf "$(PRMPT) Start makefile for $(UNDER)libraries$(UNSET)...\n"
	@make -s -C libs

client:
	@printf "$(PRMPT) Start makefile for $(UNDER)client$(UNSET)...\n"
	@make -s -C client

server:
	@printf "$(PRMPT) Start makefile for $(UNDER)server$(UNSET)...\n"
	@make -s -C server

bot_roulette:
	@printf "$(PRMPT) Start makefile for $(UNDER)bot$(UNSET)...\n"
	@make -s -C bot_roulette

copy:
	@printf "$(PRMPT) Create copy of executable files\t"
	@cp -f client/uchat uchat
	@cp -f server/uchat_server uchat_server
	@cp -f bot_roulette/uchat_bot_roulette uchat_bot_roulette
	@printf "$(GREEN)copied$(UNSET)\n"

done:
	@printf "$(PRMPT) $(UNDER)DONE$(UNSET)\n"


.PHONY: all libs client server bot_roulette

