#include"header.h"

char * FGetData(char *file)
{
    FILE *fp = fopen(file,"r");
    fseek(fp,0L,SEEK_END);
    size_t len = ftell(fp);
    char *buf0 = (char*)malloc(sizeof(char)*len);
    fseek(fp,0L,SEEK_SET);
    fread((void*)buf0,sizeof(char),len,fp);
    fclose(fp);

    char *buf = (char*) malloc(sizeof(char)*len);
    int index = 0;
    int i = 0;
    while(buf0[i] != '\n')
        i++;            //skip the first line 
    i++;

    for(;;)
    {
        if(i>=len)
            break;
        if(i-1>=0 && buf0[i-1]=='\n' &&
                (buf0[i]=='c'||buf0[i]=='C'))
        {
            while(buf0[i]!='\n')
                i++;
            i++;
            continue;
        }
        if(buf0[i]=='$'){
            while(buf0[i] != '\n')
                i++;
            continue;
        }
        buf[index++] = buf0[i++]; 
    }
    buf[index] = '\0';
    free(buf0);
    return buf;

/*
    for(int i=0;i<len;)
    {
        if(buf0[i] != '$' ||
        (i-1>=0 &&
         ( buf0[i-1]=='\n'
           && (buf0[i]=='c' || buf0[i]=='C') ))
          )
            buf[index++] = buf0[i++];
    }
*/

}
