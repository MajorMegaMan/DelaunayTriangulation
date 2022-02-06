// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the DELAUNAYTRIANGULATION_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// DELAUNAYTRIANGULATION_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DELAUNAYTRIANGULATION_EXPORTS
#define DELAUNAYTRIANGULATION_API __declspec(dllexport)
#else
#define DELAUNAYTRIANGULATION_API __declspec(dllimport)
#endif

#include "DelaunayMap.h"

class DELAUNAYTRIANGULATION_API ExportDelaunayMap
{
    DelaunayMap m_delMap;

public:
    void AllocatePointArray(int pointCount);
    void SetPoint(int index, float x, float y);
    void Triangulate();
    void Clear();

    int GetPointCount();
    float GetPointValue(int pointIndex, int valuePosition);

    int GetTriCount();
    int GetVerticePointIndex(int triangleIndex, int verticePosition);
    int GetNeighbourIndex(int triangleIndex, int neighbourPosition);
};

extern "C"
{
    DELAUNAYTRIANGULATION_API ExportDelaunayMap* Export_DelaunayMap_Create();

    DELAUNAYTRIANGULATION_API void Export_DelaunayMap_Destroy(ExportDelaunayMap* handle);

    DELAUNAYTRIANGULATION_API void Export_DelaunayMap_AllocatePointArray(ExportDelaunayMap* handle, int pointCount);

    DELAUNAYTRIANGULATION_API void Export_DelaunayMap_SetPoint(ExportDelaunayMap* handle, int pointIndex, float x, float y);

    DELAUNAYTRIANGULATION_API void Export_DelaunayMap_Triangulate(ExportDelaunayMap* handle);

    DELAUNAYTRIANGULATION_API void Export_DelaunayMap_Clear(ExportDelaunayMap* handle);

    DELAUNAYTRIANGULATION_API int Export_DelaunayMap_GetPointCount(ExportDelaunayMap* handle);

    DELAUNAYTRIANGULATION_API float Export_DelaunayMap_GetPointValue(ExportDelaunayMap* handle, int pointIndex, int valuePosition);

    DELAUNAYTRIANGULATION_API int Export_DelaunayMap_GetTriCount(ExportDelaunayMap* handle);

    DELAUNAYTRIANGULATION_API int Export_DelaunayMap_GetVerticePointIndex(ExportDelaunayMap* handle, int triangleIndex, int verticePosition);

    DELAUNAYTRIANGULATION_API int Export_DelaunayMap_GetNeighbourIndex(ExportDelaunayMap* handle, int triangleIndex, int neighbourPosition);
}
