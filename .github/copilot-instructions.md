# MyCompany Project - AI Coding Assistant Instructions

## Project Overview

This is an **isometric tile-based game** using C++ with SDL3's GPU API for rendering and lighting. The project builds on two embedded library submodules:
- **pplib** - "Patrick's Programming Library" v7 (core, graphics, audio modules)
- **ppltk** - "Patrick's Programming Library Toolkit" (GUI/window management with SDL3)

The game layer is minimal (~2 files in `src/`), leveraging these comprehensive libraries for infrastructure while implementing custom 3D rendering using SDL3's low-level GPU capabilities.

## Architecture

### Three-Layer Structure
1. **pplib** (`pplib/`) - Core library providing:
   - `libppl7-core.a` - String handling, file I/O, threads, data structures
   - `libppl7-gfx.a` - Graphics primitives, image formats, sprites, textures
   - `libppl7-audio.a` - Audio playback (MP3, Vorbis)

2. **ppltk** (`ppltk/`) - GUI toolkit built on pplib:
   - Window management via SDL3
   - Widget system with event handling
   - Provides `ppltk::WindowManager_SDL3` class (uses SDL3)

3. **Game Layer** (`src/`, `include/`) - Application code:
   - `main.cpp` - Entry point with `start()` function
   - `sdl.cpp` / `sdl_wrapper.h` - SDL abstraction classes (`SDL`, `SDLFont`)
   - Custom 3D engine using SDL3 GPU API for isometric tiles and lighting

### Key Design Patterns

**Namespace Convention**: All pplib code uses `ppl7::` namespace (with `ppl7::grafix::` for graphics). ppltk uses `ppltk::` namespace. Source files always include:
```cpp
using namespace ppl7;
using namespace ppl7::grafix;
```

**Exception Handling**: Uses macro-based exception declarations. See `EXCEPTION(name, inherit)` macro in `sdl_wrapper.h`. pplib exceptions are in `ppl7::Exception` hierarchy.

**SDL Integration**: Custom wrapper classes bridge pplib's graphics system with SDL3:
- `SDL::createTexture()` converts `ppl7::grafix::Drawable` to `SDL_Texture*`
- `SDL::lockTexture()` returns a `Drawable` for pixel manipulation
- Pixel format conversion via `SDL2RGBFormat()` / `RGBFormat2SDLFormat()`

**SDL3 GPU Rendering**: The game uses SDL3's GPU API for isometric tile rendering and lighting:
- SDL3 GPU API provides low-level access to Vulkan/Metal/Direct3D 12 backends
- Custom 3D engine built on SDL3 GPU capabilities (shaders, textures, compute)
- Isometric projection for tile-based world
- Dynamic lighting system implemented via custom shaders
- **Asset pipeline undecided**: May use 3D models (Lightwave 3D 2024 format) or pre-rendered 2D graphics
- **2D rendering pipeline**: Uses normal maps for all graphics to enable dynamic lighting via fragment shaders
- Shader-based rendering with SPIR-V or native shader languages

## Build System (Autotools + Make)

### Configuration Flow
1. Run `./configure` (generated from `configure.ac` via autoconf)
2. Creates platform-specific `Makefile` from `Makefile.in`
3. Configures all three components: main + pplib + ppltk

### Common Build Commands
```bash
# Full build with parallel jobs
make -j 16

# Build only pplib modules
make ppl7

# Build only ppltk
make ppl_toolkit

# Generate asset files
make sprites    # Creates texture atlases from lightwave renders
make fonts      # Generates .fnt6 font files from TTF

# Clean variants
make clean      # Removes main program objects only
make cleanall   # Cleans main + all submodules
```

### Version Management
- Version auto-generated in `include/version.h` via `update_version` target
- Uses git commit count as build number: `BUILD_NUMBER := $(shell git rev-list --all --count)`
- **Important**: References "decker.exe" and "GeorgeDecker" in mingw target - likely legacy from previous project name

### Dependencies (Required)
Check `configure.ac` for full list. Critical ones:
- SDL3 3.2.0+ (with GPU API support for Vulkan/Metal/D3D12)
- Assimp 5.0+ (3D model loading, including Lightwave LWO files)
- PCRE2, zlib, bzip2, iconv
- PNG, JPEG/JPEG-turbo
- mpg123, libvorbis (audio)
- dav1d (AV1 video codec)
- NASM (x86 assembly optimizations)

### Platform-Specific Notes
- **Windows (MinGW)**: Uses `make mingw` for packaging with Inno Setup
- **FreeBSD**: Adds `/usr/local/include` and `/usr/local/lib` paths
- Supports address sanitizer: `./configure --with-asan`
- **C++ Standard**: Uses C++20 (enables designated initializers, concepts, ranges)

## Key Files & Locations

### Main Game Code
- `src/main.cpp` - Initializes SDL, pplib graphics (`ppl7::grafix::Grafix`), and window manager
- `include/sdl_wrapper.h` - Declares `SDL` and `SDLFont` wrapper classes
- `include/version.h` - Auto-generated version macros (don't edit manually)

### Libraries (Submodules)
- `pplib/include/ppl7.h` - Main pplib header (includes all core functionality)
- `pplib/include/ppl7-grafix.h` - Graphics subsystem
- `ppltk/include/ppltk.h` - GUI toolkit header
- `ppltk/src/WindowManager_SDL3.cpp` - SDL3 window implementation

### Build Configuration
- `configure.ac` - Autoconf source (667 lines, checks for all dependencies)
- `Makefile.in` - Template for generated Makefile
- `pplib/autoconf/*.m4` - Dependency detection macros for libraries

### Asset Tools
- `texmaker` - Tool for creating texture atlases (referenced in `make sprites`)
- `pplfontmaker` - Converts TTF fonts to custom .fnt6 format
- Lightwave 3D 2024 used for 3D asset creation (files in `lightwave/` directory)
- Asset format TBD: May use Lightwave models directly or pre-render to 2D with normal maps

## Development Workflow

### Adding New Source Files
1. Add `.cpp` file to `src/`
2. Add corresponding object to `OBJECTS` in `Makefile.in`:
   ```makefile
   OBJECTS=compile/main.o \
           compile/sdl.o \
           compile/your_new_file.o
   ```
3. Add build rule:
   ```makefile
   compile/your_new_file.o: src/your_new_file.cpp Makefile include/your_header.h
       $(CXX) -o compile/your_new_file.o -c src/your_new_file.cpp $(CFLAGS)
   ```

### Working with pplib/ppltk
- **Read-only usage**: These are git submodules. Don't modify unless contributing upstream
- Update submodules: `make git` or `git submodule update --init --recursive`
- Include paths already set: `-Ipplib/include -Ippltk/include`

### Debugging
- Debug symbols enabled by default: `EXTRA_CFLAGS = -ggdb -Wall`
- Use address sanitizer: `./configure --with-asan && make`
- Locale setup critical: `setlocale(LC_CTYPE, "")` and `setlocale(LC_NUMERIC, "C")` required

### Testing
- pplib has extensive Google Test suite in `pplib/tests/`
- Main game currently has no test infrastructure

## Common Gotchas

1. **Character encoding on Windows**: Always call `ppl7::String::setGlobalEncoding("UTF-8")` before using strings
2. **Makefile still references "decker"**: Legacy name, actual binary is `tilegame`
4. **Font6 format**: Custom binary font format specific to pplib, not standard
5. **No IDE project files**: Pure autotools-based workflow, use `compile_commands.json` if needed for IDE integration
6. **Rendering approach undecided**: Architecture flexible for either 3D models (with potential Lightwave importer) or pre-rendered 2D sprites with normal maps for lighting
7. **SDL3 GPU API**: Requires SDL 3.2.0+ for GPU functionality; abstracts Vulkan/Metal/D3D12 for cross-platform low-level rendering
