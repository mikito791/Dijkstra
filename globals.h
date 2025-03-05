#pragma once


struct Point
{
	int x, y;
	bool operator<(const Point& other) const 
	{
		// xÀ•W‚Å”äŠrA“¯‚¶‚È‚çyÀ•W‚Å”äŠr
		if (x == other.x) {
			return y < other.y;
		}
		return x < other.x;
	}
	bool operator!=(const Point& other) const
	{
		return x != other.x || y != other.y;
	}
};

struct Pointf
{
	float x, y;
};

struct Rect
{
	int x, y, w, h;
	Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
	Point GetCenter() { return Point{ x + w / 2, y + h / 2 }; }
};


enum STAGE_OBJ {
	EMPTY,
	WALL,
	GOAL,
	MAX_OBJECT
};

struct StageObj
{
	STAGE_OBJ obj;
	float weight;
};


enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE,
	MAXDIR
};

const int CHA_WIDTH = 32;
const int CHA_HEIGHT = 32;