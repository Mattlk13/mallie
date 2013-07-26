#ifndef __MESH_LOADER_H__
#define __MESH_LOADER_H__

#include "mesh.h"

class
MeshLoader
{
 public:
  MeshLoader();

  ///< Load wavefront obj data from a file.
  ///< Allocated memory for mesh must be free'ed by the application.
  static bool LoadObj(Mesh& mesh, const char* filename);
};

#endif  // __MESH_LOADER_H__
// vim:set sw=2 ts=2 expandtab:
