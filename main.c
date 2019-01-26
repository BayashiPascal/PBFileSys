#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "pbfilesys.h"

void UnitTestJoinPath() {
  char pathA[4] = ". A\0";
  pathA[1] = PBFILESYS_FOLDERSEP;
  char pathB[2] = "B\0";
  char pathC[6] = " A B \0";
  pathC[0] = PBFILESYS_FOLDERSEP;
  pathC[2] = PBFILESYS_FOLDERSEP;
  pathC[4] = PBFILESYS_FOLDERSEP;
  char pathD[3] = "C \0";
  pathD[1] = PBFILESYS_FOLDERSEP;
  char pathE[6] = "D.txt\0";
  char checkA[6] = ". A B\0";
  checkA[1] = PBFILESYS_FOLDERSEP;
  checkA[3] = PBFILESYS_FOLDERSEP;
  char checkB[13] = " A B C D.txt\0";
  checkB[0] = PBFILESYS_FOLDERSEP;
  checkB[2] = PBFILESYS_FOLDERSEP;
  checkB[4] = PBFILESYS_FOLDERSEP;
  checkB[6] = PBFILESYS_FOLDERSEP;
  char* path = PBFSJoinPath(pathA, pathB);
  printf("%s + %s -> %s\n", pathA, pathB, checkA);
  if (path == NULL || strcmp(path, checkA) != 0) {
    PBFileSysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBFileSysErr->_msg, "PBFSJoinPath failed");
    PBErrCatch(PBFileSysErr);
  }
  free(path);
  path = PBFSJoinPath(pathC, pathD, pathE);
  printf("%s + %s + %s -> %s\n", pathC, pathD, pathE, checkB);
  if (path == NULL || strcmp(path, checkB) != 0) {
    PBFileSysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBFileSysErr->_msg, "PBFSJoinPath failed");
    PBErrCatch(PBFileSysErr);
  }
  free(path);
  printf("UnitTestJoinPath\n");
}

void UnitTestAll() {
  UnitTestJoinPath();
}

int main(void) {
  UnitTestAll();
  return 0;
}

