#include"header.h"

void FReadFace()
{
    gface = NULL;
    char token[64];
    int face;
    int i;  // for index;

    while(region == 1 )
    {
        index = FGetToken(buf,index,token);

        if(strcmp(token,"") == 0 ){
            printf(" region value is %d\n",region);
            continue;
        }
        sscanf(token,"%d",&face);
        printf("the face id is %d \n",face);
        struct GFACE* tmp = FNewGface();
        tmp->_faceid = face;

         index = FGetToken(buf,index,token);
         printf(" the face type is  %s\n",token);
         if(strcmp(token,"so") == 0)
           {
             printf("find the so surface type!\n");
             // next read the four parameters

             //for( i=0;i<4;i++)
               //index = FGetToken(buf,index,token);
             tmp->_face._type = 2;    // represent this is the sphere
             tmp->_face._numbercoefficient = 4;
             tmp->_face._coefficient = (double*)malloc( (tmp->_face._numbercoefficient)*sizeof(double) );
             for(i =0;i< tmp->_face._numbercoefficient;i++){
                 index = FGetToken(buf,index,token);
                 sscanf(token,"%lf",&((tmp->_face._coefficient)[i]));
               }
           }
         else if(token[0] == 'p' || token[0] == 'P') {   // 需要把面进行展开，进行数值运算
             printf("find the plane surface type!\n");

             for(i=0;i<4;i++)
               index = FGetToken(buf,index,token);

           }
         else if(token[0] == 'c/x' || token[0] == 'C/X'){   // this function is not right
             printf("find the cylinder surface type!\n");
             for(i=0;i<3;i++)
               index = FGetToken(buf,index,token);
           }
         else if(token[0] == 'c/y' || token[0] == 'C/Y'){   // this function is not right
             printf("find the cylinder surface type!\n");
             for(i=0;i<3;i++)
               index = FGetToken(buf,index,token);
           }
         else if(token[0] == 'c/z' || token[0] == 'C/Z'){   // this function is not right
             printf("find the cylinder surface type!\n");
             for(i=0;i<3;i++)
               index = FGetToken(buf,index,token);
           }
         else{
             printf("this surface type is not known, please check your input \n");
             exit(0);
           }
    }

    return;
}
