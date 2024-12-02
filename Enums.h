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