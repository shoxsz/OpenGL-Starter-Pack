#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include <algorithm>
#include <vector>
#include <memory>

#include "input_listener.hpp"

struct GLFWwindow;

class Input{
public:
	static bool isKeyDown(int key);
	static bool isKeyJustPressed(int key);

	static bool isButtonPressed(int button);
	static std::pair<int, int> mousePosition();

	static void registerListener(InputListener* listener);
	static void unregisterListener(InputListener* listener);

	static void init(GLFWwindow* window);

private:
	static GLFWwindow* window;
	static std::unique_ptr<InputDispatcher> dispatcher;

	static void keyCallback(GLFWwindow* window, int key, int scamcode, int state, int mods);
	static void cursorCallback(GLFWwindow* window, double x, double y);
	static void mouseButtonCallback(GLFWwindow* window, int button, int state, int mods);

	static void windowCloseCallback(GLFWwindow* window);
	static void windowFocusChangedCallback(GLFWwindow* window, int focused);
	static void windowIconifyCallback(GLFWwindow* window, int iconified);
	static void windowResizeCallback(GLFWwindow* window, int width, int height);
};

//GLFW KEYS MAPPING

#define GKEY_UNKNOWN            -1

/* Printable keys */
#define GKEY_SPACE              32
#define GKEY_APOSTROPHE         39  /* ' */
#define GKEY_COMMA              44  /* , */
#define GKEY_MINUS              45  /* - */
#define GKEY_PERIOD             46  /* . */
#define GKEY_SLASH              47  /* / */
#define GKEY_0                  48
#define GKEY_1                  49
#define GKEY_2                  50
#define GKEY_3                  51
#define GKEY_4                  52
#define GKEY_5                  53
#define GKEY_6                  54
#define GKEY_7                  55
#define GKEY_8                  56
#define GKEY_9                  57
#define GKEY_SEMICOLON          59  /* ; */
#define GKEY_EQUAL              61  /* = */
#define GKEY_A                  65
#define GKEY_B                  66
#define GKEY_C                  67
#define GKEY_D                  68
#define GKEY_E                  69
#define GKEY_F                  70
#define GKEY_G                  71
#define GKEY_H                  72
#define GKEY_I                  73
#define GKEY_J                  74
#define GKEY_K                  75
#define GKEY_L                  76
#define GKEY_M                  77
#define GKEY_N                  78
#define GKEY_O                  79
#define GKEY_P                  80
#define GKEY_Q                  81
#define GKEY_R                  82
#define GKEY_S                  83
#define GKEY_T                  84
#define GKEY_U                  85
#define GKEY_V                  86
#define GKEY_W                  87
#define GKEY_X                  88
#define GKEY_Y                  89
#define GKEY_Z                  90
#define GKEY_LEFT_BRACKET       91  /* [ */
#define GKEY_BACKSLASH          92  /* \ */
#define GKEY_RIGHT_BRACKET      93  /* ] */
#define GKEY_GRAVE_ACCENT       96  /* ` */
#define GKEY_WORLD_1            161 /* non-US #1 */
#define GKEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define GKEY_ESCAPE             256
#define GKEY_ENTER              257
#define GKEY_TAB                258
#define GKEY_BACKSPACE          259
#define GKEY_INSERT             260
#define GKEY_DELETE             261
#define GKEY_RIGHT              262
#define GKEY_LEFT               263
#define GKEY_DOWN               264
#define GKEY_UP                 265
#define GKEY_PAGE_UP            266
#define GKEY_PAGE_DOWN          267
#define GKEY_HOME               268
#define GKEY_END                269
#define GKEY_CAPS_LOCK          280
#define GKEY_SCROLL_LOCK        281
#define GKEY_NUM_LOCK           282
#define GKEY_PRINT_SCREEN       283
#define GKEY_PAUSE              284
#define GKEY_F1                 290
#define GKEY_F2                 291
#define GKEY_F3                 292
#define GKEY_F4                 293
#define GKEY_F5                 294
#define GKEY_F6                 295
#define GKEY_F7                 296
#define GKEY_F8                 297
#define GKEY_F9                 298
#define GKEY_F10                299
#define GKEY_F11                300
#define GKEY_F12                301
#define GKEY_F13                302
#define GKEY_F14                303
#define GKEY_F15                304
#define GKEY_F16                305
#define GKEY_F17                306
#define GKEY_F18                307
#define GKEY_F19                308
#define GKEY_F20                309
#define GKEY_F21                310
#define GKEY_F22                311
#define GKEY_F23                312
#define GKEY_F24                313
#define GKEY_F25                314
#define GKEY_KP_0               320
#define GKEY_KP_1               321
#define GKEY_KP_2               322
#define GKEY_KP_3               323
#define GKEY_KP_4               324
#define GKEY_KP_5               325
#define GKEY_KP_6               326
#define GKEY_KP_7               327
#define GKEY_KP_8               328
#define GKEY_KP_9               329
#define GKEY_KP_DECIMAL         330
#define GKEY_KP_DIVIDE          331
#define GKEY_KP_MULTIPLY        332
#define GKEY_KP_SUBTRACT        333
#define GKEY_KP_ADD             334
#define GKEY_KP_ENTER           335
#define GKEY_KP_EQUAL           336
#define GKEY_LEFT_SHIFT         340
#define GKEY_LEFT_CONTROL       341
#define GKEY_LEFT_ALT           342
#define GKEY_LEFT_SUPER         343
#define GKEY_RIGHT_SHIFT        344
#define GKEY_RIGHT_CONTROL      345
#define GKEY_RIGHT_ALT          346
#define GKEY_RIGHT_SUPER        347
#define GKEY_MENU               348

#define GKEY_LAST               GKEY_MENU

#endif