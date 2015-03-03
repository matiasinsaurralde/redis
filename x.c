	#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

const char *prefix = "./rdbs/";
char archiveFiles[365][15];
int valid_n = 0;

time_t get_mtime(char *prefix, char *path) {
  struct stat statbuf;
  char completePath[100];
  sprintf(completePath, "%s%s", prefix, path);
  if (stat(completePath, &statbuf) == -1) {
    perror(path);
    exit(1);
  };
  return statbuf.st_ctime;
};

int ctimesort(const struct dirent **d1, const struct dirent **d2) {
  // char *prefix = "rdbs/";
  time_t f_time = (int)get_mtime( prefix, (*d1)->d_name );
  time_t f_time2 = (int)get_mtime( prefix, (*d2)->d_name );
  return f_time2-f_time;
};
/*
void generateLastN( int n, char *arr ) {
printf("generateLastN: %d\n", n );
  int i = valid_n-1;
  int total = 0;

  while( i != -1 ) {
    if( total == n ) {
printf("\n");
      break;
    } else {
      const char *fname = archiveFiles[i];
      char *str = malloc( strlen(fname)+1 );
      strcpy( &arr[total], fname);
      printf("%d: %s\n", total, fname);
      //strcpy( &arr[total], fname );
      //strcpy( *arr[i], fname);
      i--;
      total++;
    };
  };
};*/

int main() {
  struct dirent **namelist;
  int n;
  // int valid_n = 0;
  n = scandir( prefix, &namelist, NULL, ctimesort);
  if (n < 0)
    perror("scandir");
  else {
    while (n--) {
      size_t len = strlen( namelist[n]->d_name );
      size_t spn = strcspn( namelist[n]->d_name, ".rdb");
      if( len == 14 && spn == 10 ) {
        // valido
        // printf("%s\n", namelist[n]->d_name);
        strncpy( archiveFiles[valid_n], namelist[n]->d_name, sizeof(namelist[n]->d_name) );
        valid_n++;
      };
      free(namelist[n]);
    };
    free(namelist);
  };

  char* yesterday[] = {};
  char* weekly[] = {};
  char* monthly[] = {};

  int i = valid_n-1;
  int total = 0;

  while( i != -1 ) {
    if( total == n ) {
      break;
    } else {
      const char *fname = archiveFiles[i];
//      printf("%d: %s\n", total, fname);


      //strcpy( &arr[total], fname );
      //strcpy( *arr[i], fname);

/*      if( total == 0 ) {
        yesterday[0] = fname;
      };
*/
      if( total >= 0 && total <= 7 ) {
        if( weekly[total] != NULL ) {
          printf("%s\n", fname );
        };
      };

/*      if( total >= 0 && total <= 30 ) {
        // strcpy( monthly[total], fname );
      };*/

      i--;
      total++;
    };
  };

};
