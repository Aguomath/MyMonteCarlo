#include"header.h"

void FReadMaterial()
{
    int i;
    int materialid;
    char token[64];
    while(region == 2){
        index = FGetToken(buf,index,token);
        if(strcmp(token,"")==0)
        {
            printf("region value is  %d\n ",region);
            continue;
        }
        printf("%s\n",token);
        if(strlen(token)>=2 &&
           (token[0] == 'm' || token[0] == 'M')
           && isdigit(token[1]) )
          {
            // get material id and the the ace data from data
            char number[8];
            for(i=1;i<strlen(token);i++)
              number[i-1] = token[i];
            number[i-1] = '\0';
            printf("the number is %s \n",number);  // get the material number so you can find the data
            // 把这个material id 存储起来，和截面匹配
            sscanf(number,"%d",&materialid);  // next read the material id
            for(;;){
                index = FGetToken(buf,index,token);
                if(strcmp(token,"") == 0){
                    continue;
                }
            }
          }
    }
    return;
}



