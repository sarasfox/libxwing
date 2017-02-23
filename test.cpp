#include "squad.h"
#include "./json/json.h"
#include <dirent.h>
#include <sys/stat.h>
#include <functional>
#include <fstream>



void RunTestXwsFiles(std::string testFilesDir) {
  std::string d = testFilesDir;
  if(d[d.length()-1] != '/') {
    d += "/";
  }

  DIR *dp;
  struct dirent *dirp;
  int listNameLength = 0;

  // get list name length for formatting purposes
  if((dp = opendir(d.c_str())) == 0) {
    printf("error reading dir\n");
    return;
  }
  while ((dirp = readdir(dp)) != 0) {
    if( (strcmp(dirp->d_name, ".") == 0) || (strcmp(dirp->d_name, "..") == 0)) {
      //printf("skipping %s\n", dirp->d_name);
      continue;
    }

    int newLength = strlen(dirp->d_name);
    if(listNameLength < newLength) {
      listNameLength = newLength;
    }
  }
  closedir(dp);

  // try the lists
  if((dp = opendir(d.c_str())) == 0) {
    printf("error reading dir\n");
    return;
  }
  while ((dirp = readdir(dp)) != 0) {
    if( (strcmp(dirp->d_name, ".") == 0) || (strcmp(dirp->d_name, "..") == 0)) {
      //printf("skipping %s\n", dirp->d_name);
      continue;
    }

    std::string curFile = d + dirp->d_name;
    struct stat st;

    printf("%-*s ", listNameLength, dirp->d_name); fflush(stdout);
    if(stat(curFile.c_str(), &st) != 0) {
      printf("ERROR (reading file)\n");
    }
    else if(st.st_mode & S_IFDIR) {
      printf("ERROR (directory)\n");
    }
    else {
      Squad sq = Squad(curFile);
      try {
        bool ok = true;
        Json::Value root;
        std::ifstream xws(curFile, std::ifstream::binary);
        xws >> root;

        // is list correctly identified as valid/invalid
        bool xwsSquadValid;
        if     (root["vendor"]["XWSTF"].get("valid", "").asString() == "true")  { xwsSquadValid = true; }
        else if(root["vendor"]["XWSTF"].get("valid", "").asString() == "false") { xwsSquadValid = false; }
        else   { throw ""; }
        bool objSquadValid = (sq.Verify().size() == 0);
        if(xwsSquadValid != objSquadValid) {
          ok=false;
          printf("ERROR - Validity [xws:%s obj:%s]\n", xwsSquadValid ? "valid" : "invalid", objSquadValid ? "valid" : "invalid");
        }

        // check squad cost
        uint16_t xwsCost = root.get("points", "").asInt();
        uint16_t objCost = sq.GetCost();
        if(xwsCost != objCost) {
          if(!ok) { printf("%-*s ", listNameLength, ""); }
          ok=false;
          printf("ERROR - Cost [xws:%d obj:%d]\n", xwsCost, objCost);
        }

        // check individual ship costs
        for(int i=0; i<root["pilots"].size(); i++) {
          int xwsShipCost = root["pilots"][i].get("points", "").asInt();
          int objShipCost = sq.GetPilots()[i].GetModCost();
          if(xwsShipCost != objShipCost) {
            if(!ok) { printf("%-*s ", listNameLength, ""); }
            ok = false;
            printf("ERROR - Cost(Ship %d) [xws=%d obj=%d]\n", i+1, xwsShipCost, objShipCost);
            break;
          }
        }

        if(ok) {
          printf("OK\n");
        }
      }
      catch(...) {
        printf("ERROR (parsing json)\n");
      }
    }
  }
  printf("DONE\n");

}
