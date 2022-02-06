#pragma once
#include "DelHull.h"

class DelaunayMap
{
	DelPoint* m_delPointArray = nullptr;
	int m_delPointCount = 0;

	DelTri* m_delTriArray = nullptr;
	int m_delTriCount = 0;

public:
	DelaunayMap() {};
	DelaunayMap(const Vector2* pointArray, int pointCount);
	DelaunayMap(const DelPoint* pointArray, int pointCount);
	DelaunayMap(const DelaunayMap& other) = delete;
	DelaunayMap& operator=(const DelaunayMap& other) = delete;
	~DelaunayMap();

	void CreatePointArray(int pointCount);
	void SetPoint(int index, float x, float y);

	void Init(const Vector2* pointArray, int pointCount);
	void Init(const DelPoint* pointArray, int pointCount);
	void Clear();

	int GetPointCount() const;
	const DelPoint* GetPointBegin() const;
	int GetTriCount() const;
	const DelTri* GetTriBegin() const;

	void SweepLineTriangulate();
private:
	// Sweep Line algorithim
	void SortPointArray();
	void CreateTriangleArray(DelHull& hull);

	void ClearPointList();
	void ClearTriangles();
};