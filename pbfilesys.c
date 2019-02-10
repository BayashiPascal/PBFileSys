// ============ PBFILESYS.C ================

// ================= Include =================

#include "pbfilesys.h"
#if BUILDMODE == 0
#include "pbfilesys-inline.c"
#endif

// ================ Functions implementation ====================

// Join the paths in arguments 
// Ignore the empty paths
// Return the result path as a new string
// Take care of adding the folder separator where needed
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
    if (l > 0 && path[l - 1] != PBFILESYS_FOLDERSEP)
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
    if (l > 0) {
      strcpy(joinedPath + startPos, path);
      startPos += l;
      if (iPath < nbPath - 1 && path[l - 1] != PBFILESYS_FOLDERSEP) {
        joinedPath[startPos] = PBFILESYS_FOLDERSEP;
        ++startPos;
      }
    }
  }
  va_end(paths);
  // Return the final string
  return joinedPath;
}

// Get the root folder of the path 'path'
// Examples:
// PBFSGetRootPath("A/B") -> "A"
// PBFSGetRootPath("/A/B") -> "/A"
// PBFSGetRootPath("/A/B/") -> "/A/B"
// PBFSGetRootPath("A") -> ""
// PBFSGetRootPath("/A") -> "/"
// PBFSGetRootPath("/") -> "/"
// PBFSGetRootPath("") -> ""
// PBFSGetRootPath(NULL) -> NULL
char* PBFSGetRootPath(const char* path) {
  // If the path is null
  if (path == NULL)
    return NULL;
  // Declare a variable for the result
  char* res = NULL;
  // Declare a pointer to search the last separator
  const char* ptr = path + strlen(path);
  // Look for the last separator
  while (*ptr != PBFILESYS_FOLDERSEP && ptr != path)
    ptr--;
  // If we went down to the beginning of the path
  if (ptr == path) {
    // if the first char of the path is a separator
    if (*ptr == PBFILESYS_FOLDERSEP) {
      // The result is the separtor only
      res = PBErrMalloc(PBFileSysErr, sizeof(char) * 2);
      res[0] = PBFILESYS_FOLDERSEP;
      res[1] = '\0';
    // Else the the first char is not a separator
    } else {
      // The result is the empty string
      res = PBErrMalloc(PBFileSysErr, sizeof(char));
      res[0] = '\0';
    }
  // Else, we have found the last separator in the middle of the path
  } else {
    // If we have stopped on a separator
    if (*ptr == PBFILESYS_FOLDERSEP)
      // Skip it
      ptr--;
    // Copy the root path in the result
    int l = (1 + ptr - path);
    res = PBErrMalloc(PBFileSysErr, sizeof(char) * (1 + l));
    memcpy(res, path, l);
    res[l] = '\0';
  }
  // Return the root path
  return res;
}
