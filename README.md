# GDExtension C++ Demo (Godot 4.5)

A minimal, **clean-structure** template to build a GDExtension with C++ for **Godot 4.5** using **godot-cpp 4.5**.  
Goal: compile fast, read the code fast, fix issues fast.

## What this is
- A working demo scene that loads a tiny C++ class (`Summator`) via GDExtension.
- A **readable folder layout** (`include/`, `src/`, `demo/`) instead of dumping files everywhere.
- Meant as a starting point you can fork.

## Tested setup
- **Engine:** Godot **4.5**
- **Bindings:** **godot-cpp 4.5**
- **Compiler:** GCC on Linux x86_64
- **Build:** SCons + Python 3

> If you use other versions, pin them and test. Don’t assume “latest” will work.

## Folder structure
```
project/
├─ include/                       # public headers (what you include from .cpp)
|  ├─ gd_extension_modules
|  |  └─ register_types.h
│  └─ modules/
│     └─ summator.h
├─ src/                           # C++ implementations + entry point
│  ├─ gd_extension_modules        
|  |  └─ register_types.cpp       # example_library_init + ClassDB registrations
│  └─ modules/
│     └─ summator.cpp
├─ demo/                          # Godot project using the built .so
│  └─ bin/                        # output .so lives here (debug/release)
└─ external/godot-cpp/            # pinned godot-cpp (submodule)
```

## Build
```bash
# clone with submodules
git clone --recurse-submodules <this-repo>
cd <this-repo>

# build (debug)
scons platform=<platform>
# build (release)
scons target=release
```

**Artifacts**
- `demo/bin/libgdexample.linux.template_debug.x86_64.so`
- `demo/bin/libgdexample.linux.template_release.x86_64.so`

## Run the demo
1. Open `demo/` in Godot 4.5.
2. The `.gdextension` points to the built `.so`.

## Key choices (why this layout)
- `include/` = public headers; `src/` = implementations.  
- `#include "modules/summator.h"` (no `include/` prefix).  
- SCons adds include paths once, not per file.  
- One entry point: `example_library_init` registers all classes.

## Versioning
- Tags like `godot-4.5`, `godot-4.5.1`.  
- Keep `external/godot-cpp` **pinned** to a known-good commit.  
- When Godot **4.6** lands: branch, pin, test, then tag.

## License
MIT. Do whatever you want—just keep the notice.

---

If it breaks, open an issue with:
- OS, compiler version
- Godot version
- `godot-cpp` commit
- Full error log
