// ============ PBFILESYS.C ================

// ================= Include =================

#include "pbfilesys.h"
#if BUILDMODE == 0
#include "pbfilesys-inline.c"
#endif

// ================ Functions implementation ====================

char* _PBFSJoinPath(const int nbPath, ...) {
  // Declare a variable to calculate the length of the final string
  int len = 0;
  // Loop on the arguments
  va_list paths;
  va_start(paths, nbPath);
  for (int iPath = 0; iPath < nbPath; ++iPath) {
    char* path = va_arg(paths, char*);
    int l = strlen(path);
    len += l;
    if (path[l - 1] != PBFILESYS_FOLDERSEP)
      ++len;
  }
  // Allocate memory for the final string
  char* joinedPath = PBErrMalloc(PBFileSysErr, (len + 1) * sizeof(char));
  // Loop again on the arguments
  va_start(paths, nbPath);
  int startPos = 0;
  for (int iPath = 0; iPath < nbPath; ++iPath) {
    char* path = va_arg(paths, char*);
    int l = strlen(path);
    strcpy(joinedPath + startPos, path);
    startPos += strlen(path);
    if (iPath < nbPath - 1 && path[l - 1] != PBFILESYS_FOLDERSEP) {
      joinedPath[startPos] = PBFILESYS_FOLDERSEP;
      ++startPos;
    }
  }
  va_end(paths);
  // Return the final string
  return joinedPath;
}

