// DelaunayTriangulation.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "DelaunayTriangulation.h"

void ExportDelaunayMap::AllocatePointArray(int pointCount)
{
	m_delMap.CreatePointArray(pointCount);
}

void ExportDelaunayMap::SetPoint(int index, float x, float y)
{
	m_delMap.SetPoint(index, x, y);
}

void ExportDelaunayMap::Triangulate()
{
	m_delMap.SweepLineTriangulate();
}

void ExportDelaunayMap::Clear()
{
	m_delMap.Clear();
}

int ExportDelaunayMap::GetPointCount()
{
	return m_delMap.GetPointCount();
}

float ExportDelaunayMap::GetPointValue(int pointIndex, int valuePosition)
{
	const DelPoint* point = &m_delMap.GetPointBegin()[pointIndex];
	float* convert = (float*)point;
	float result = *(convert + valuePosition);
	return result;
}

int ExportDelaunayMap::GetTriCount()
{
	return m_delMap.GetTriCount();
}

int ExportDelaunayMap::GetVerticePointIndex(int triangleIndex, int verticePosition)
{
	//const DelTri* tri = &m_delMap.GetTriBegin()[triangleIndex];
	//int result = tri->GetPoint(verticePosition)->index;
	return m_delMap.GetTriBegin()[triangleIndex].GetPoint(verticePosition)->index;
}

int ExportDelaunayMap::GetNeighbourIndex(int triangleIndex, int neighbourPosition)
{
	const DelTri* tri = &m_delMap.GetTriBegin()[triangleIndex];

	auto neighbour = tri->neighbours[neighbourPosition];
	if (neighbour != nullptr)
	{
		return neighbour->index;
	}
	else
	{
		return -1;
	}
}

ExportDelaunayMap* Export_DelaunayMap_Create()
{
	return new ExportDelaunayMap;
}

void Export_DelaunayMap_Destroy(ExportDelaunayMap* handle)
{
	delete handle;
}

void Export_DelaunayMap_AllocatePointArray(ExportDelaunayMap* handle, int pointCount)
{
	handle->AllocatePointArray(pointCount);
}

void Export_DelaunayMap_SetPoint(ExportDelaunayMap* handle, int pointIndex, float x, float y)
{
	handle->SetPoint(pointIndex, x, y);
}

void Export_DelaunayMap_Triangulate(ExportDelaunayMap* handle)
{
	handle->Triangulate();
}

void Export_DelaunayMap_Clear(ExportDelaunayMap* handle)
{
	handle->Clear();
}

int Export_DelaunayMap_GetPointCount(ExportDelaunayMap* handle)
{
	return handle->GetPointCount();
}

float Export_DelaunayMap_GetPointValue(ExportDelaunayMap* handle, int pointIndex, int valuePosition)
{
	return handle->GetPointValue(pointIndex, valuePosition);
}

int Export_DelaunayMap_GetTriCount(ExportDelaunayMap* handle)
{
	return handle->GetTriCount();
}

int Export_DelaunayMap_GetVerticePointIndex(ExportDelaunayMap* handle, int triangleIndex, int verticePosition)
{
	return handle->GetVerticePointIndex(triangleIndex, verticePosition);
}

int Export_DelaunayMap_GetNeighbourIndex(ExportDelaunayMap* handle, int triangleIndex, int neighbourPosition)
{
	return handle->GetNeighbourIndex(triangleIndex, neighbourPosition);
}
