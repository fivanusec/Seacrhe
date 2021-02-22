#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h> 
#include <pwd.h>
#include <malloc.h>

int Find(char *** list, char * file_name, char * directory, int * location);
char *getUserName();
 
int main(int argc, char * argv[]) 
{
    if (argc < 3) {
        char *user = getUserName();
        char *path = malloc(strlen("/home/" + strlen(user)+1));
        strcpy(path, "/home/");
        strcat(path, user);
        argv[2] = path;
    }
     
    char ** found_list = (char**)malloc(sizeof(char*) * 30);
    if (!found_list) return 0;
 
    int counter_location = 0;
     
    char * ini_dir = (char*)malloc(sizeof(char) * 500);
    if (!ini_dir) {
        free (found_list);
        return 0;
    }
 
    if (argv[2]) strcpy(ini_dir, argv[2]);
 
    Find(&found_list, argv[1], ini_dir, &counter_location);   
     
    if (counter_location > 0) {
        while (--counter_location >= 0) {
            printf("%s\n", found_list[counter_location]);
            free (found_list[counter_location]);
        }
    }
    else {
        printf("Failed to find the file!\n");
    }
 
    free (ini_dir);
    free (found_list);
    return 0;
}
 
int Find(char *** list, char * file_name, char * directory, int * location)
{
    DIR * opened_dir;
    struct dirent * directory_structure;
     
    char * temp_dir = (char*)malloc(sizeof(char) * 300);
    if (!temp_dir) return -1;
     
    strcat(directory, "/"); 
    opened_dir = opendir(directory);
    if (opened_dir == NULL) {
        free (temp_dir);
        return -1;
    }
     
    while (1) {
        directory_structure = readdir(opened_dir);
        if (!directory_structure) {
            closedir(opened_dir);
            free (temp_dir);
            return 0;
        }
        if (!strcmp(directory_structure->d_name, "..") || 
            !strcmp(directory_structure->d_name, ".")) continue; 
         
        else if (!strcmp(directory_structure->d_name, file_name)) {
            (*list)[*location] = (char*)malloc(sizeof(char) * 300);
            sprintf((*list)[*location], "%s%s", directory, directory_structure->d_name);
            char *print = (char *)malloc(sizeof((*list)[*location]) + sizeof(directory) + sizeof(directory_structure->d_name) +1);
            strcpy(print,(*list)[*location]);
            strcat(print,directory);
            strcat(print,directory_structure->d_name);
            (*location)++;
        }
        else if (directory_structure->d_type == DT_DIR) {
            sprintf(temp_dir, "%s%s", directory, directory_structure->d_name);
            if (Find(list, file_name, temp_dir, location) == -1) {
                closedir(opened_dir);
                free (temp_dir);
                return -1;
            }
        }
    }
                 
    return 0;
}

char *getUserName()
{
  uid_t uid = geteuid();
  struct passwd *pw = getpwuid(uid);
  if (pw)
  {
    return pw->pw_name;
  }

  return "";
}