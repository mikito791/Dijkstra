//柱大量に配置するステージ
//#include "Stage.h"
//#include "./globals.h"
//
//Stage::Stage()
//{
//	stageData = vector(STAGE_HEIGHT, vector<STAGE_OBJ>(STAGE_WIDTH, STAGE_OBJ::EMPTY));
//
//	for (int y = 0; y < STAGE_HEIGHT; y++)
//	{
//		for (int x = 0; x < STAGE_WIDTH; x++)
//		{
//			if (y == 0 || y == STAGE_HEIGHT - 1 || x == 0 || x == STAGE_WIDTH - 1)
//			{
//				stageData[y][x] = STAGE_OBJ::WALL;
//			}
//			else
//			{
//				if (x % 2 == 0 && y % 2 == 0)
//					stageData[y][x] = STAGE_OBJ::WALL;
//				else
//					stageData[y][x] = STAGE_OBJ::EMPTY;
//			}
//
//		}
//	}
//	setStageRects();
//}
//
//Stage::~Stage()
//{
//}
//
//void Stage::Update()
//{
//}
//
//void Stage::Draw()
//{
//	for (int y = 0; y < STAGE_HEIGHT; y++)
//	{
//		for (int x = 0; x < STAGE_WIDTH; x++)
//		{
//			switch (stageData[y][x])
//			{
//			case STAGE_OBJ::EMPTY:
//				DrawBox(x * CHA_WIDTH, y * CHA_HEIGHT, x * CHA_WIDTH + CHA_WIDTH, y * CHA_HEIGHT + CHA_HEIGHT, GetColor(102, 205, 170), TRUE);
//				break;
//			case STAGE_OBJ::WALL:
//				DrawBox(x * CHA_WIDTH, y * CHA_HEIGHT, x * CHA_WIDTH + CHA_WIDTH, y * CHA_HEIGHT + CHA_HEIGHT, GetColor(119, 136, 153), TRUE);
//				break;
//			case STAGE_OBJ::GOAL:
//
//				break;
//			default:
//				break;
//			}
//		}
//	}
//}
//
//void Stage::setStageRects()
//{
//	for (int y = 0; y < STAGE_HEIGHT; y++)
//	{
//		for (int x = 0; x < STAGE_WIDTH; x++)
//		{
//			if (stageData[y][x] == STAGE_OBJ::WALL)
//			{
//				stageRects.push_back(Rect(x * CHA_WIDTH, y * CHA_HEIGHT, CHA_WIDTH, CHA_HEIGHT));
//			}
//		}
//	}
//}

//迷路ステージ
#include "Stage.h"
#include "./globals.h"
#include <stack>

namespace {
	std::stack<Point> prStack;

	void DigDug(int x, int y, vector<vector<StageObj>>& _stage)
	{
		_stage[y][x].obj = STAGE_OBJ::EMPTY;

		Point Dir[]{ {0,-1},{1, 0},{0, 1},{-1,0} };
		std::vector<int> dList;
		for (int i = 0; i < 4; i++) {
			//nextを0~3まで回してでたーを取得
			Point next = Point{ x + Dir[i].x, y + Dir[i].y };
			Point nextNext = { next.x + Dir[i].x, next.y + Dir[i].y };
			if (nextNext.x < 0 || nextNext.y < 0 || nextNext.x > STAGE_WIDTH - 1 || nextNext.y > STAGE_HEIGHT - 1)
				continue;

			if (_stage[nextNext.y][nextNext.x].obj == STAGE_OBJ::WALL)
			{
				dList.push_back(i);
			}
			//ここにelseつけて、もう一個掘っちゃうといいかも！（ループのやつ）
		}
		if (dList.empty())
		{
			return;
		}
		int nrand = rand() % dList.size();
		int tmp = dList[nrand];

		Point next = { x + Dir[tmp].x, y + Dir[tmp].y };
		Point nextNext = { next.x + Dir[tmp].x, next.y + Dir[tmp].y };

		_stage[next.y][next.x].obj = STAGE_OBJ::EMPTY;
		_stage[nextNext.y][nextNext.x].obj = STAGE_OBJ::EMPTY;

		prStack.push(nextNext);
		DigDug(nextNext.x, nextNext.y, _stage);
	}


	void AllWall(int w, int h, vector<vector<StageObj>>& _stage)
	{
		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++) {
				if (i == 0 || j == 0 || i == w - 1 || j == h - 1)
					_stage[j][i].obj = STAGE_OBJ::EMPTY;
				else
					_stage[j][i].obj = STAGE_OBJ::WALL;
			}
		}
	}

	void MakeMazeDigDug(int w, int h, vector<vector<StageObj>>& _stage)
	{
		AllWall(w, h, _stage);
		Point sp{ 1, 1 };
		prStack.push(sp);
		while (!prStack.empty())
		{
			sp = prStack.top();
			prStack.pop();
			DigDug(sp.x, sp.y, _stage);
		}


		for (int j = 0; j < h; j++)
		{
			for (int i = 0; i < w; i++)
			{
				_stage[j][i].weight = 1.0;
				if (i == 0 || j == 0 || i == w - 1 || j == h - 1)
					_stage[j][i].obj = STAGE_OBJ::WALL;
				continue;
			}
		}
	}

}




Stage::Stage()
{
	stageData = vector(STAGE_HEIGHT, vector<StageObj>(STAGE_WIDTH, { STAGE_OBJ::EMPTY, 1.0f }));

	MakeMazeDigDug(STAGE_WIDTH, STAGE_HEIGHT, stageData);
	//for (int y = 0; y < STAGE_HEIGHT; y++)
	//{
	//	for (int x = 0; x < STAGE_WIDTH; x++)
	//	{
	//		if (y == 0 || y == STAGE_HEIGHT - 1 || x == 0 || x == STAGE_WIDTH - 1)
	//		{
	//			stageData[y][x] = STAGE_OBJ::WALL;
	//		}
	//		else
	//		{
	//			if (x % 2 == 0 && y % 2 == 0)
	//				stageData[y][x] = STAGE_OBJ::WALL;
	//			else
	//				stageData[y][x] = STAGE_OBJ::EMPTY;
	//		}
	//	}
	//}
	setStageRects();
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			switch (stageData[y][x].obj)
			{
			case STAGE_OBJ::EMPTY:
				DrawBox(x * CHA_WIDTH, y * CHA_HEIGHT, x * CHA_WIDTH + CHA_WIDTH, y * CHA_HEIGHT + CHA_HEIGHT, GetColor(102, 205, 170), TRUE);
				break;
			case STAGE_OBJ::WALL:
				DrawBox(x * CHA_WIDTH, y * CHA_HEIGHT, x * CHA_WIDTH + CHA_WIDTH, y * CHA_HEIGHT + CHA_HEIGHT, GetColor(119, 136, 153), TRUE);
				break;
			case STAGE_OBJ::GOAL:

				break;
			default:
				break;
			}
		}
	}
}

void Stage::setStageRects()
{
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			if (stageData[y][x].obj == STAGE_OBJ::WALL)
			{
				stageRects.push_back(Rect(x * CHA_WIDTH, y * CHA_HEIGHT, CHA_WIDTH, CHA_HEIGHT));
			}
		}
	}

}