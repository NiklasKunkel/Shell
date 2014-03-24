//  main.cpp
//  Shell
//
//  Created by Niklas Kunkel on 3/20/14.
//  Copyright (c) 2014 Niklas Kunkel. All rights reserved.

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "parser.h"
#include "execute.h"
#include "cd.h"

#define BUF_LIM 120

typedef void (*sighandler_t)(int);
char c = '\0';

void handle_signal(int signo)
{
    fflush(stdout);
}

int main(void)
{
    
    //Buffer to hold our input commands
    char buffer[BUF_LIM];
    
    //Index for cycling through buffer
    unsigned long int index;
    
    //Stores pointers to token strings
    char *tokens[BUF_LIM];
    
    //Process ID
    pid_t pid;
    
    //Status of process
    int status;
    
    //Used for deciding file descriptors
    unsigned long int in, out, inout, back;
    
    //File descriptors
    int fd[2], fdin, fdout;
    
    //used to exit by pressing ctrl+D
    signal(SIGINT, SIG_IGN);
    signal(SIGINT, handle_signal);
    
    //Loop bash shell so it doesn't return after a single command
    while(1)
    {
        //print prompt - printf reqires %% to print %
        printf("nkunkel$ >> ");
        
        //Get buffer from user
        while(fgets(buffer,BUF_LIM,stdin) != NULL)
        {
            //Checks if cd was called
            if(stringCompare(buffer, "cd"))
            {
                //find beginning of path to cd into
                tokens[0] = strchr(buffer,' ')+1;
                
                //Make sure string ends properly
                *strchr(tokens[0], '\n')='\0';
                
                //Call c
                cd(tokens[0]);
            }
            
            else
            {
                //Parse our buffer command
                Parser(buffer, tokens, index, in, out, inout, back);
                
                //If 
                if((in && inout) || (out && inout))
                {
                    fprintf(stderr, "Not implemented\n");
                    continue;
                }
                
                //Call fork
                pid = fork();
                
                //Fork doesn't work
                if(pid < 0)
                {
                    perror("fork error");
                    exit(1);
                }
                
                //child process
                else if(!pid)
                {
                    //Execute the command
                    execute(tokens, fd, fdin, fdout, in, out, inout, back, pid, status);
                }
            }
        }
    }
}