# MiniRT Header Organization

This document describes the new organized header structure implemented for better maintainability and modularity.

## Directory Structure

```
includes/
├── miniRT.h                    # Main header - includes everything needed
├── miniRT_old.h               # Backup of original monolithic header
├── core/                      # Core system components
│   ├── constants.h           # All project constants and macros
│   ├── types.h              # Basic types and forward declarations  
│   └── control_panel.h      # Main control panel structure
├── math/                      # Mathematical utilities
│   ├── vec3.h               # Vector operations (moved from root)
│   └── interval.h           # Interval operations (moved from root)
├── graphics/                  # Rendering and graphics
│   ├── materials.h          # Material definitions and functions
│   ├── ray.h                # Ray tracing structures  
│   ├── camera.h             # Camera operations
│   ├── lighting.h           # Light structures and calculations
│   └── render.h             # Main rendering functions
├── objects/                   # Geometric objects
│   ├── objects.h            # Base object operations
│   ├── sphere.h             # Sphere-specific code
│   ├── plane.h              # Plane-specific code
│   ├── cylinder.h           # Cylinder-specific code
│   └── cone.h               # Cone-specific code
├── ui/                        # User interface
│   └── ui.h                 # UI components (moved from root)
├── system/                    # System integration
│   ├── mlx_wrapper.h        # MLX integration layer
│   └── memory.h             # Memory management
└── io/                        # Input/output operations
    ├── errors.h             # Error handling (renamed from miniRT_error_p.h)
    └── parsing.h            # File parsing functions
```

## Key Improvements

### 1. **Separation of Concerns**
- Each header now has a specific, well-defined purpose
- Related functionality is grouped together
- Clear dependencies between modules

### 2. **Reduced Compilation Dependencies**
- Source files only include what they actually need
- Forward declarations minimize circular dependencies
- Faster compilation times due to reduced header bloat

### 3. **Better Maintainability**
- Easy to find specific functionality
- Clear module boundaries
- Structured for future extensions

### 4. **Cleaner Include Structure**
The main `miniRT.h` now cleanly includes components in dependency order:
```c
/* Core includes */
# include "core/constants.h"
# include "core/types.h"

/* Math includes */  
# include "math/vec3.h"
# include "math/interval.h"

/* Graphics includes */
# include "graphics/ray.h"           # Must come before materials
# include "graphics/materials.h"
# include "graphics/camera.h"
# include "graphics/lighting.h"  
# include "graphics/render.h"

/* Objects includes */
# include "objects/objects.h"
# include "objects/sphere.h"
# include "objects/plane.h"
# include "objects/cylinder.h"
# include "objects/cone.h"

/* System includes */
# include "system/mlx_wrapper.h"
# include "system/memory.h"

/* UI includes */
# include "ui/ui.h"

/* I/O includes */  
# include "io/errors.h"
# include "io/parsing.h"

/* Main control panel */
# include "core/control_panel.h"
```

## Migration Notes

- **Backup preserved**: Original `miniRT.h` saved as `miniRT_old.h`
- **Source files unchanged**: All `.c` files continue to include `miniRT.h`
- **Compilation verified**: Full clean build passes successfully
- **Functionality preserved**: No behavioral changes, only organizational

## Usage

For most development, simply include the main header:
```c
#include "miniRT.h"
```

For specific modules during development, individual headers can be included:
```c
#include "math/vec3.h"        // Just vector operations
#include "graphics/ray.h"     // Just ray structures  
#include "objects/sphere.h"   // Just sphere operations
```

This organization provides a solid foundation for future development while maintaining all existing functionality.