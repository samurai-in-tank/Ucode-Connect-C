# libsqlite3 Makefile

# Executable file name
EXEC_FILE = libsqlite3.a

# Compiler settings
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

# Libraries
#LIBS_DIR = 
#LIBS = 

# Serial list of tasks
PIPELINE = uninstall build archive index


SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(addprefix obj/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard inc/*.h)
LIBS_FILES = $(addprefix $(LIBS_DIR)/, $(LIBS:%=%.a))

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

PRMPT = [$(GREEN)$(EXEC_FILE)$(UNSET)]


all: $(PIPELINE)

link:
	@printf "$(PRMPT) Linking executable file\t"
	@$(CC) $(CFLAGS) -g obj/* -I inc/ -mwindows -o $(EXEC_FILE) $(LIBS_FILES)
	@printf "$(GREEN)linked$(UNSET)\n"


archive:
	@printf "$(PRMPT) Archiving library\t\t"
	@ar -rc $(EXEC_FILE) obj/*.o
	@printf "$(GREEN)archived$(UNSET)\n"


index:
	@printf "$(PRMPT) Indexing library\t\t"
	@ranlib $(EXEC_FILE)
	@printf "$(GREEN)indexed$(UNSET)\n"


build: $(OBJ_FILES)
	@printf "\r$(PRMPT) Compiling                                                                                                            "
	@printf "\r$(PRMPT) Compiling object files\t$(GREEN)compiled$(UNSET)\n"


$(OBJ_FILES): obj


obj:
	@mkdir -p $@


obj/%.o: src/%.c $(INC_FILES)
	@printf "\r$(PRMPT) Compiling                                                                                                            "
	@printf "\r$(PRMPT) Compiling $(<:src/%.c=%).o"
	@$(CC) $(CFLAGS) -c $< -o $@ -I inc


clean:
	@printf "$(PRMPT) Deleting obj/ directory\t"
	@rm -rf obj $@
	@rm -rf $(OBJ_FILES) $@
	@printf "$(RED)deleted$(UNSET)\n"

fullclean:
	@make clean -sC $(LIB_DIR)
	@printf "$(PRMPT) Deleting obj/ directory\t"
	@rm -rf obj $@
	@rm -rf $(OBJ_FILES) $@
	@printf "$(RED)deleted$(UNSET)\n"


uninstall:
	@printf "$(PRMPT) Deleting obj/ directory\t"
	@rm -rf obj $@
	@rm -rf $(OBJ_FILES) $@
	@printf "$(RED)deleted$(UNSET)\n"
	@printf "$(PRMPT) Deleting executable file\t"
	@rm -rf $(EXEC_FILE)
	@printf "$(RED)deleted$(UNSET)\n"

fulluninstall:
	@make uninstall -sC $(LIB_DIR)
	@printf "$(PRMPT) Deleting obj/ directory\t"
	@rm -rf obj $@
	@rm -rf $(OBJ_FILES) $@
	@printf "$(RED)deleted$(UNSET)\n"
	@printf "$(PRMPT) Deleting executable file\t"
	@rm -rf $(EXEC_FILE)
	@printf "$(RED)deleted$(UNSET)\n"


reinstall: uninstall all


.PHONY: all lib link archive index build uninstall clean fullclean fulluninstall reinstall

