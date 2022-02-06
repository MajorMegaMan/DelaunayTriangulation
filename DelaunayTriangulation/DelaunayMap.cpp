#include "pch.h"
#include "DelaunayMap.h"

DelaunayMap::DelaunayMap(const Vector2* pointArray, int pointCount)
{
	Init(pointArray, pointCount);
}

DelaunayMap::DelaunayMap(const DelPoint* pointArray, int pointCount)
{
	Init(pointArray, pointCount);
}

DelaunayMap::~DelaunayMap()
{
	Clear();
}

void DelaunayMap::CreatePointArray(int pointCount)
{
	Clear();

	m_delPointArray = new DelPoint[pointCount];
	m_delPointCount = pointCount;

	for (int i = 0; i < pointCount; i++)
	{
		m_delPointArray[i].index = i;
	}
}

void DelaunayMap::SetPoint(int index, float x, float y)
{
	m_delPointArray[index].x = x;
	m_delPointArray[index].y = y;
}

void DelaunayMap::Init(const Vector2* pointArray, int pointCount)
{
	m_delPointArray = new DelPoint[pointCount];
	m_delPointCount = pointCount;

	for (int i = 0; i < pointCount; i++)
	{
		m_delPointArray[i] = pointArray[i];
		m_delPointArray[i].index = i;
	}

	SweepLineTriangulate();
}

void DelaunayMap::Init(const DelPoint* pointArray, int pointCount)
{
	m_delPointArray = new DelPoint[pointCount];
	m_delPointCount = pointCount;

	for (int i = 0; i < pointCount; i++)
	{
		m_delPointArray[i] = pointArray[i];
	}

	SweepLineTriangulate();
}

void DelaunayMap::Clear()
{
	ClearPointList();
	ClearTriangles();
}

int DelaunayMap::GetPointCount() const
{
	return m_delPointCount;
}

const DelPoint* DelaunayMap::GetPointBegin() const
{
	return m_delPointArray;
}

int DelaunayMap::GetTriCount() const
{
	return m_delTriCount;
}

const DelTri* DelaunayMap::GetTriBegin() const
{
	return m_delTriArray;
}

void DelaunayMap::SortPointArray()
{
	// bubble sort
	bool hasSwapped = false;
	do
	{
		hasSwapped = false;
		for (int i = 0; i < m_delPointCount - 1; i++)
		{
			m_delPointArray[i].TrySortLower(m_delPointArray[i + 1], hasSwapped);
		}
	} while (hasSwapped);

	for (int i = 0; i < m_delPointCount; i++)
	{
		m_delPointArray[i].index = i;
	}
}

void DelaunayMap::SweepLineTriangulate()
{
	// Sort Point array with lowest x value first
	SortPointArray();

	// Check if at least one triangle can be made
	if (m_delPointCount < 3)
	{
		return;
	}

	// Initialise hull from first triangle
	DelHull hull;
	hull.Create(m_delPointArray, m_delPointCount);

	// this goes at the end
	CreateTriangleArray(hull);
}

void DelaunayMap::CreateTriangleArray(DelHull& hull)
{
	ClearTriangles();

	m_delTriArray = new DelTri[hull.GetTriangleCount()];
	hull.CreateTriangles(m_delTriArray, m_delTriCount);
}

void DelaunayMap::ClearPointList()
{
	if (m_delPointArray == nullptr)
	{
		return;
	}

	delete[] m_delPointArray;
	m_delPointArray = nullptr;
	m_delPointCount = 0;
}

void DelaunayMap::ClearTriangles()
{
	if (m_delTriArray == nullptr)
	{
		return;
	}

	delete[] m_delTriArray;
	m_delTriArray = nullptr;
	m_delTriCount = 0;
}
