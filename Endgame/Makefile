# Makefile

# b - Build project, p - Play game, bnp - Build'n'Play.

# b:
# 	clang -std=c11 -Wall -Wextra -Werror -Wpedantic source/*.c -o build/game.app -I libraries/include -L libraries/lib -lSDL2-2.0.0 -lSDL2_image -mwindows

# p:
# 	clang -g obj/*.o -I inc/ -L lib -lSDL2-2.0.0 -lSDL2_image -mwindows

# bnp:
# 	clang -std=c11 -Wall -Wextra -Werror -Wpedantic source/*.c -o build/game.app -I libraries/include -L libraries/lib -lSDL2-2.0.0 -lSDL2_image -mwindows
# 	build/game.app
	
LIB_FILES = /lib
SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(addprefix obj/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard inc/*.h)
EXEC_FILE = endgame

CFLAGS = -std=c11 #-Wall -Wextra -Werror -Wpedantic

SDL = -F resource/framework -I resource/framework/SDL2.framework/SDL2 -I resource/framework/SDL2_image.framework/SDL2_image \
	-I resource/framework/SDL2_mixer.framework/SDL2_mixer -I resource/framework/SDL2_ttf.framework/SDL2_ttf

SDL_FLAGS = -rpath resource/framework -framework SDL2 \
		-framework SDL2_image \
		-I resource/framework/SDL2_image.framework/Headers \
		-framework SDL2_mixer \
		-I resource/framework/SDL2_mixer.framework/Headers \
		-framework SDL2_ttf \
		-I resource/framework/SDL2_ttf.framework/Headers \

all: $(EXEC_FILE)
	@printf "Starting $(EXEC_FILE)\n"
	@./$(EXEC_FILE)

$(EXEC_FILE): build link

link:
	@printf "\r\33[2KLink $(EXEC_FILE)\t\t"

	@clang -g obj/* -I inc/ -mwindows -o $(EXEC_FILE) $(SDL_FLAGS) $(SDL)

	@printf "\033[32;1mlinked\033[0m\n"

build: $(OBJ_FILES)

$(OBJ_FILES): obj

obj:
	@mkdir -p $@

obj/%.o: src/%.c $(INC_FILES)
	@printf "\r\33[2KCompile $(<:src/%.c=%).o\t\t"
	@clang $(CFLAGS) -c $< -o $@ -I inc
	@printf "\033[32;1mcompiled\033[0m\n"

clean:
	@printf "Delete obj/\t\t"
	@rm -rf obj $@
	@rm -rf $(OBJ_FILES) $@
	@printf "\033[31;1mdeleted\033[0m\n"

uninstall: clean
	@printf "Delete $(EXEC_FILE)\t\t"
	@rm -rf minilibmx.a
	@printf "\033[31;1mdeleted\033[0m\n"

reinstall: uninstall all

.PHONY: all build uninstall clean reinstall