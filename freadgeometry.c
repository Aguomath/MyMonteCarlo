#include"header.h"


extern int region;
void FReadGeometry()
{
    region = 0;
    char *file = "godiva.dat";

    // read the file and output

    buf = FGetData(file);
#if 1
    printf("d\n%s\n",buf);
#endif
    gcelllist = NULL;
    inputbuf = buf;
    char token[64];
    index = 0;
    // begion read the cell parameters
    while( region == 0  )//index<strlen(buf)-1)
    {
        index = FGetToken(buf,index,token);
        if(strcmp(token,"") == 0){

            printf("region value is %d\n",region);

            continue;
          }
        //printf("cell id is %s\n",token);

        struct CELLLIST * cell = FNewCell(); 
        // next read the cell id to convert 
        // the data

        sscanf(token,"%ld",&((cell->_cell)._id));
        printf("cell id is %d\n",cell->_cell._id);
        index = FGetToken(buf,index,token);

        // next read the material id
        (cell->_cell)._mat = FNewMaterial();
        sscanf(token,"%d",&((cell->_cell._mat->_matid))); 
        if( cell->_cell._mat->_matid != 0){
            index = FGetToken(buf,index,token);
            sscanf(token,"%lf",&(cell->_cell._mat->_totaldensity));
            printf("the total density is %lf\n",cell->_cell._mat->_totaldensity);
          }
        // next read the face
        //
        //struct FACELIST *tmp;
        //tmp = cell->_cell._facelist = FNewFaceList();
        struct FACELIST *tmp;
        for(;;){
            index = FGetToken(buf,index,token);
            if(cell->_cell._facelist == NULL){
                tmp = cell->_cell._facelist = FNewFaceList();
                sscanf(token,"%d",&(tmp->_normal));
                tmp = tmp->_next;
            }else{
                tmp = FNewFaceList();
                sscanf(token,"%d",&(tmp->_normal));
                tmp = tmp->_next;
            }
            if(strcmp(token,"imp") == 0)
              {
                index = FGetToken(buf,index,token);    // the token ':'
                index = FGetToken(buf,index,token);    // the token 'n'
                index = FGetToken(buf,index,token);    // the token '='
                index = FGetToken(buf,index,token);    // the token  number : the importance number
                break;
              }
        }
    }
    return;
}
