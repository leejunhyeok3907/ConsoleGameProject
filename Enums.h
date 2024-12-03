#pragma once

enum class SCENE_TYPE
{
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MONSTER,
	GROUND,
	UI,
	END,
};

enum class KEY_TYPE
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Z,
	X,
	C,
	Q,
	SPACE,
	END
};

enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	AWAY,
};

enum class ConsoleRenderingColor
{
	UNKNOWN = -1,
	BLACK,
	DARKBLUE,
	DARKGREEN,
	DARKCYAN,
	DARKRED,
	DARKMAGENTA,
	DARKYELLOW,
	GRAY,
	DARKGRAY,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	WHITE,
};

enum class ConsoleRenderingType
{
	TEXT=0,
	BACKGROUND
};