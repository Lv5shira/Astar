#pragma once
#include <vector>
#include <math.h>

struct Vector2 {
	
	float x, y;

	Vector2(float _x = 0.0f, float _y = 0.0f)
		:x(_x), y(_y){}

};

struct Node {
	bool isWall = false;
	bool isStart = false;
	bool isEnd = false;

	float G = 0.0f;
	float H = 0.0f;
	float F = 0.0f;

	Vector2 pos;
	Node* parent = nullptr;
	std::vector<Node*> cn;
	Node(Vector2 _pos = { 0.0f, 0.0f })
		:pos(_pos) {}
};

inline float VectorDistance(Vector2 a, Vector2 b)
{
	return (float) sqrt(pow(((double)a.x - (double)b.x), 2) + pow(((double)a.y - (double)b.y), 2));
}

struct Color {
	int r;
	int g;
	int b;
	Color(int _r = 0, int _g = 0, int _b = 0)
		:r(_r), g(_g), b(_b) {}
};