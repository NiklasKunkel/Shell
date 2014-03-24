//
//  cd.h
//  Shell
//
//  Created by Niklas Kunkel on 3/23/14.
//  Copyright (c) 2014 Niklas Kunkel. All rights reserved.
//

#ifndef Shell_cd_h
#define Shell_cd_h

#define BUF_LIM 120

//Compares the two strings
//For loop is based off of b because that is where cd will be called
//This solution is primitive as there may be other commands starting with cd
int stringCompare(char const *a, char const *b)
{
    for(int k = 0; b[k]; k++)
    {
        //if a and b don't match return -1
        if(a[k] != b[k])
            return 0;
    }
    
    //return 0 if strings are the same
    return 1;
}

int cd(char* token)
{
    char path[BUF_LIM];
    char cwd[BUF_LIM];
    
    strcpy(path,token);
    
    //If cd PATH is based off current working directory
    if(token[0] != '/')
    {
        //Build full path string from current working directory + / + input path
        getcwd(cwd,sizeof(cwd));
        strcat(cwd,"/");
        strcat(cwd,path);
        chdir(cwd);
    }
    
    //Cd /PATH refers to the whole path
    else
    {
        chdir(token);
    }
    
    return 0;
}


#endif
