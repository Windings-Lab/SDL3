# SDL3 Development

## Dependencies

* Use `conan` package manager
* `find_package` will look for `zlib`, `libpng`, `boost`

## MSVC linkage issues

If you encountering a linkage error:  
Open `vendor/SDL/src/stdlib/SDL_malloc.c` and comment line 31 on `#define FORCEINLINE`
