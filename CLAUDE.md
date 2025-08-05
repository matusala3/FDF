# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

```bash
# Build the project
make

# Clean object files
make clean

# Clean everything including executable
make fclean

# Rebuild from scratch
make re

# Run the program
./fdf maps/test_maps/42.fdf
```

## Dependencies

- **MinilibX**: Graphics library - must be installed or cloned to `minilibx-linux/` directory
- **libft**: Custom C library (included in project)
- **System libraries**: X11, Xext, math library

## Architecture Overview

FDF is a 3D wireframe visualizer that transforms height map files (.fdf) into isometric wireframe displays using MinilibX.

### Core Data Flow

1. **Parsing Pipeline** (`parse.c`):
   - `get_file_dimensions()` → `allocate_map()` → `fill_map_data()`
   - Creates `t_map` structure containing 2D array of `t_point` structs
   - Height values automatically mapped to colors

2. **Graphics Pipeline** (`draw.c`):
   - `project_point()` applies isometric projection: `(x-y)*scale, (x+y)*scale - z*height`
   - `draw_wireframe()` connects adjacent grid points
   - Direct pixel buffer manipulation for performance

3. **Memory Management**:
   - Staged allocation with rollback on failure
   - `cleanup_graphics()` handles proper MLX resource cleanup
   - Helper functions in `helper.c` for common cleanup patterns

### Key Data Structures

- `t_map`: Contains `t_point **map` (2D grid), dimensions
- `t_graphics`: MLX context, image buffer, direct pixel access
- `t_point`: Grid coordinates (x,y), height (z), color
- `t_spoint`: 2D screen coordinates after projection

### Coordinate Systems

- **Grid Space**: File row/col → world x/y coordinates  
- **World Space**: 3D points with height (z) values
- **Screen Space**: Isometric projection with dynamic scaling and centering

### Dynamic Scaling Algorithm

- **Adaptive Scale**: Calculates optimal scale based on both X and Y window constraints
- **Scale Range**: Clamped between 2-30 pixels per grid unit for optimal viewing
- **Margin Handling**: 50px margins ensure complete wireframe visibility
- **Height Scaling**: Z-axis height scales proportionally (scale/2) for balanced 3D effect

### Event Handling

- ESC key (keycode 65307) exits application
- Window close button handled
- Event handlers in `helper.c`: `handle_keypress()`, `handle_close()`

## Common Issues

- MinilibX dependency missing: Clone from official repository
- Map file format: Space-separated integers, consistent row lengths
- Memory leaks: Always use cleanup functions on error paths
- Color format: 0xRRGGBB format for MinilibX compatibility

## File Format

.fdf files contain space-separated integers representing height values:
```
0 0 1 2 3
0 1 2 3 4
1 2 3 4 5
```

Height-to-color mapping:
- 0: Blue (water)
- 1-5: Green (low)  
- 6-10: Yellow (medium)
- >10: Pink (high)