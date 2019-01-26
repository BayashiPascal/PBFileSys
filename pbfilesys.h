// ============ PBFILESYS.H ================

#ifndef PBFILESYS_H
#define PBFILESYS_H

// ================= Include =================

#include <stdlib.h>
#include <stdio.h>
#include "pberr.h"
#include "pbcextension.h"

// ================= Define ==================

#define PBFILESYS_FOLDERSEP '/'

// ================ Functions declaration ====================

// Join the paths in arguments 
// Return the result path as a new string
// Take care of adding the folder separator where needed
char* _PBFSJoinPath(const int nbPath, ...);
#define PBFSJoinPath(...) \
  _PBFSJoinPath(__VA_NB_ARGS__(const char*, __VA_ARGS__), __VA_ARGS__)

// ================ Inliner ====================

#if BUILDMODE != 0
#include "pbfilesys-inline.c"
#endif

#endif
