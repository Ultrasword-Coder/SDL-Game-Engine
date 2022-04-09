#SDL Game Engine

## Designed to be cross platform

- who knows if it actually is to be honest
- I have no idea myself, I just hope that yall know how to use it!

## Set up on Mac

- mac is stupid
- go download the SDL_Image .dmg file from the SDL_Image website
- Then navigate to `usr/bin/Library/Frameworks`
- open the .dmg you downloaded
- paste the `SDL_Image.framework` into the `usr/bin/Library/Frameworks`

## Set up on Windows

- I don't know how to help if you aren't using mingw

### Mingw

#### Header Files!

- now this is good
- first, download the SDL2 zip and the SDL_Image zip
- extract zip files
- cool, now open the SDL_Image folder and go to `include` and copy and paste the `SDL_image.h` into the `include` folder in the SDL2 folder.
- now you wanna just copy the include folder from SDL2 folder and naviate to where you installed mingw
- copy paste the include into the `msys64/mingw64/include` and rename to SDL2

#### DLLs

- go to the extracted SDL2 folder
- copy and paste the .a files from the `lib` folder into the `msys64/mingw64/lib`
- go to the `bin` folder in SDL2 extracted
- copy and paste `SDL2.dll` into your coding directory
- go to the extracted SDL_Image folder
- copy and paste the `SDL_image.dll` into your coding directory

### WARNING

- when i say coding directory, I mean where you will be compiling your .exe file to
