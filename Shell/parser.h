//
//  parser.h
//  Shell
//
//  Created by Niklas Kunkel on 3/20/14.
//  Copyright (c) 2014 Niklas Kunkel. All rights reserved.
//

#ifndef Shell_parser_h
#define Shell_parser_h

void Parser(char buffer[], char* tokens[], unsigned long int &index, unsigned long int &in, unsigned long int &out, unsigned long int &inout, unsigned long int &back)
{
    //Makes sure the end of our buffer has NULL
    buffer[index = (strlen(buffer) - 1)] = 0;
    
    //Reset from previous buffer values
    index = in = out = inout = back = 0;
    
    //Writes pointer of token to our token array
    tokens[index++] = strtok(buffer, " ");
    
    while((tokens[index] = strtok(NULL, " ")))
    {
        switch(*tokens[index])
        {
            case '<':
                in = index;
                tokens[index] = NULL;
                break;
                
            case '>':
                out = index;
                tokens[index] = NULL;
                break;
                
            case '|':
                inout = index;
                tokens[index] = NULL;
                break;
                
            case '&':
                back = index;
                tokens[index] = NULL;
                break;
                
        }
        index++;
    }
}



#endif
