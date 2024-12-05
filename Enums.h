#pragma once

enum class SCENE_TYPE
{
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	STAGE_04,
	STAGE_05,
	GAMEOVER,
	WIN,
	END,
};

enum class GROUP_TYPE
{
	DEFAULT,
	PORTAL,
	BOSS,
	MONSTER,
	PLAYER,
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