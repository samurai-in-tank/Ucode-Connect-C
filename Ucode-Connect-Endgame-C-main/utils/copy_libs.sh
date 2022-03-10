# load_libs.sh

# Using to copy SDL libs to current workspace folder

mkdir lib

cp -r ~/.brew/opt/sdl2/include/ inc/
cp -r ~/.brew/opt/sdl2/lib/ lib/

cp ~/.brew/opt/sdl2_image/include/SDL2/SDL_image.h inc/SDL2/
cp ~/.brew/opt/sdl2_image/lib/libSDL2_image-2.0.0.dylib lib/
cp ~/.brew/opt/sdl2_image/lib/libSDL2_image.a lib/
cp ~/.brew/opt/sdl2_image/lib/libSDL2_image.dylib lib/
cp ~/.brew/opt/sdl2_image/lib/pkgconfig/SDL2_image.pc lib/pkgconfig/

cp ~/.brew/opt/sdl2_ttf/include/SDL2/SDL_ttf.h inc/SDL2/
cp ~/.brew/opt/sdl2_ttf/lib/libSDL2_ttf-2.0.0.dylib lib/
cp ~/.brew/opt/sdl2_ttf/lib/libSDL2_ttf.a lib/
cp ~/.brew/opt/sdl2_ttf/lib/libSDL2_ttf.dylib lib/
cp ~/.brew/opt/sdl2_ttf/lib/pkgconfig/SDL2_ttf.pc lib/pkgconfig/

cp ~/.brew/opt/sdl2_mixer/include/SDL2/SDL_mixer.h inc/SDL2/
cp ~/.brew/opt/sdl2_mixer/lib/libSDL2_mixer-2.0.0.dylib lib/
cp ~/.brew/opt/sdl2_mixer/lib/libSDL2_mixer.a lib/
cp ~/.brew/opt/sdl2_mixer/lib/libSDL2_mixer.dylib lib/
cp ~/.brew/opt/sdl2_mixer/lib/pkgconfig/SDL2_mixer.pc lib/pkgconfig/
