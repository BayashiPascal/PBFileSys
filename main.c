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
  path = PBFSJoinPath("", pathD);
  printf("'' + %s -> %s\n", pathD, pathD);
  if (path == NULL || strcmp(path, pathD) != 0) {
    PBFileSysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBFileSysErr->_msg, "PBFSJoinPath failed");
    PBErrCatch(PBFileSysErr);
  }
  free(path);
  path = PBFSJoinPath(pathD, "");
  printf("%s + '' -> %s\n", pathD, pathD);
  if (path == NULL || strcmp(path, pathD) != 0) {
    PBFileSysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBFileSysErr->_msg, "PBFSJoinPath failed");
    PBErrCatch(PBFileSysErr);
  }
  free(path);
  printf("UnitTestJoinPath OK\n");
}

void UnitTestRootPath() {
  char* res = NULL;
  res = PBFSGetRootPath("A/B");
  printf("A/B -> %s\n", res);
  if (strcmp(res, "A") != 0) {
    PBFileSysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBFileSysErr->_msg, "PBFSGetRootPath failed");
    PBErrCatch(PBFileSysErr);
  }
  free(res);
  res = PBFSGetRootPath("/A/B");
  printf("/A/B -> %s\n", res);
  if (strcmp(res, "/A") != 0) {
    PBFileSysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBFileSysErr->_msg, "PBFSGetRootPath failed");
    PBErrCatch(PBFileSysErr);
  }
  free(res);
  res = PBFSGetRootPath("/A/B/");
  printf("/A/B/ -> %s\n", res);
  if (strcmp(res, "/A/B") != 0) {
    PBFileSysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBFileSysErr->_msg, "PBFSGetRootPath failed");
    PBErrCatch(PBFileSysErr);
  }
  free(res);
  res = PBFSGetRootPath("A");
  printf("A -> %s\n", res);
  if (strcmp(res, "") != 0) {
    PBFileSysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBFileSysErr->_msg, "PBFSGetRootPath failed");
    PBErrCatch(PBFileSysErr);
  }
  free(res);
  res = PBFSGetRootPath("/A");
  printf("/A -> %s\n", res);
  if (strcmp(res, "/") != 0) {
    PBFileSysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBFileSysErr->_msg, "PBFSGetRootPath failed");
    PBErrCatch(PBFileSysErr);
  }
  free(res);
  res = PBFSGetRootPath("/");
  printf("/ -> %s\n", res);
  if (strcmp(res, "/") != 0) {
    PBFileSysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBFileSysErr->_msg, "PBFSGetRootPath failed");
    PBErrCatch(PBFileSysErr);
  }
  free(res);
  res = PBFSGetRootPath(NULL);
  printf("NULL -> NULL\n");
  if (res != NULL) {
    PBFileSysErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBFileSysErr->_msg, "PBFSGetRootPath failed");
    PBErrCatch(PBFileSysErr);
  }
  free(res);

  printf("UnitTestRootPath OK\n");
}

void UnitTestAll() {
  UnitTestJoinPath();
  UnitTestRootPath();
}

int main(void) {
  UnitTestAll();
  return 0;
}

