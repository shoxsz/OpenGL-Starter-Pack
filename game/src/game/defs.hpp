#ifndef _DEFS_HPP_
#define _DEFS_HPP_

#define WORLD_TOP (10.0f)
#define WORLD_BOTTOM (-10.0f)

#define CAMERA_WIDTH (20.0f)
#define CAMERA_HEIGHT (20.0f)

#define WORLD_UNIT (1.0f / 1.0f)

#define TO_WORLD(x) (x * WORLD_UNIT)
#define FROM_WORLD(x) (x / WORLD_UNIT)

#endif