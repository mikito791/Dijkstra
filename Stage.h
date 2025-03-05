#pragma once
#include "./Library/GameObject.h"
#include <vector>
#include <map>
#include <string>
#include <vector>
#include "./Source/Screen.h"
#include "./globals.h"

using std::vector;


constexpr int STAGE_WIDTH = (Screen::WIDTH / CHA_WIDTH) % 2 ? (Screen::WIDTH / CHA_WIDTH) : (Screen::WIDTH / CHA_WIDTH) - 1;
constexpr int STAGE_HEIGHT = (Screen::HEIGHT / CHA_HEIGHT) % 2 ? (Screen::HEIGHT / CHA_HEIGHT) : (Screen::HEIGHT / CHA_HEIGHT) - 1;


class Stage :
	public GameObject
{
	vector<vector<StageObj>> stageData;//–À˜H
	//vector<vector<STAGE_OBJ>> stageData;//’Œ‘å—Ê
	vector<Rect> stageRects;
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	StageObj GetStageData(int x, int y) { return stageData[y][x]; }
	vector<Rect> GetStageRects() { return stageRects; }
	vector<vector<StageObj>>& GetStageGrid() { return stageData; }
	void setStageRects();

};