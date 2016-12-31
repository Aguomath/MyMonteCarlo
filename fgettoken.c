#include"header.h"

//extern int region;
// using the diagram to define the system

int FGetToken(char *buf, int index ,char *token)
{
  // first loop over the white space
  while(buf[index] == ' ')
    index++;
  int low = index;

  if(buf[index] == '\n'){
      if(index>0 && buf[index-1]=='\n')
        {
          index++;
          region = region + 1;
          printf("the region value is %d\n",region);
          token[0] = '\0';
          return index;
        }
      index++;
      token[0] = '\0';
      return index;
   }

  if(isalnum(buf[index]) ||  (buf[index] == '+') ||  (buf[index] == '-')) {
      index++;
      while(isalnum(buf[index]) || buf[index] == '.')
        index++;
      int len = index - low;
      strncpy(token,buf+low,len);
      token[len] = '\0';
      return index;
  }
  if(buf[index] == ':')
    {
      index++;
      int len = index-low;
      strncpy(token,buf+low,len);
      token[len] = '\0';
      return index;
    }
  if(buf[index] == '=')
    {
      index++;
      int len = index-low;
      strncpy(token,buf+low,len);
      token[len] = '\0';
      return index;
    }
  //return index;
}

/*
int FGetToken(char *buf,int index,char *token)
{
    int low;
    low = index;
    while(buf[index]==' '){
        index++;
    }
    low = index;
    while( buf[index] != ' ' && isalnum(buf[index]) ) //&& buf[index] != '\n')
    {
        if(buf[index]=='\n')
        {
            if(index>0 && buf[index-1]=='\n'){
                printf("the region is %d \n",region);
                region++;  // 0 represent the geometry region 
                           // 1 represent the face region
                           // 2 represent the physical region
            }
            index++;
            break;
        }


        if(buf[index]==':'){
            index++;
            break;
        }
        if(buf[index] == '='){
            index++;
            break;
        }


        index++;
    }
    if(buf[index] == ':')
    {

     }

    if(buf[index] == '\n')
        index++;

    int len = index - low;
    strncpy(token,buf+low,len);
    token[len] = '\0'; 
    return index;
}
*/
