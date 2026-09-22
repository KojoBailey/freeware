# Conventions
## Casing
- **Types**: `PascalCase`
- **Functions**: `camelCase`
- **Variables**: `camelCase`
- **Macros**: `SHOUTING_CASE`
- **Namespaces**: `lowercase`

## Naming
- **Maps**: `valueByKey` - e.g., `componentByHandle`
- **Getters**: `getX` - e.g., `getSize()`

## Files
- `#pragma once` for headers.
- Any `.cpp` file should have a corresponding `.hpp`.
- Include order: corresponding header -> project headers -> SDL -> standard library
