#include"header.h"
#include<math.h>

#define BOLTZMANN 8.617385e-11

// read the ace file from the input file,
// you can consider the data
void FReadAce()
{
    return;
}

int ace_read(struct ATOM * ace,const char* ace_zaid,const char * ace_file)
{
     char csindex[256]={};
     char datapath[256]={};                       // initial the array for zero
     int i,j;                                      //for index
     char * p;
     FILE * fp=NULL;                             // first read the csindex char array and datapath array
     char * temp;
     if(strcmp(ace_file,"")==0)                  //first read the csindex and datapath
     {
         if((fp=fopen("csindex","r"))!=NULL)     //read the current csindex file
         {

             strcpy(csindex,"csindex");          //the current path csindex file
             fseek(fp,0L,SEEK_END);
             long int fpsize = ftell(fp);
             p = (char*)malloc(sizeof(char)*fpsize);
             fseek(fp,0L,SEEK_SET);
             fread(p,sizeof(char),fpsize,fp);
             if((temp=strstr(p,ace_zaid))==NULL)                    //find the sub-string
             {
                 printf("can't find the %s  in cross section library!\n",ace_zaid);
             }

             temp = strtok(temp," ");
             strtok(NULL," ");
             temp = strtok(NULL," ");
//             strcat(datapath,"/");                                   ////>代码导致OTF_DOPPLER程序只能liunux运行
             strcat(datapath,temp);                                    //the datapath
             strtok(NULL," ");strtok(NULL," ");
             long long begin = atoll(strtok(NULL," "));             //数据开始的行数
             long long len   = atoll(strtok(NULL," "));             //数据长度，以字符串为单位
             free(p);                                                         //free the p char
             fclose(fp);
             fp=fopen(datapath,"r");
             if(fp==NULL)
                 printf("can't open the file  %s !\n",datapath);
             fseek(fp,begin,SEEK_SET);
             p = (char *)malloc((len+1) * sizeof(char));
             fread(p,sizeof(char),len+1,fp);
             fclose(fp);
         }
         else                                    //read the environment file
         {
             if((p=getenv("JMCTPATH"))==NULL)
             {
                 printf("this program has error in reading the ace file!\n");
                 exit(1);
             }
             strcpy(datapath,p);
             strcat(datapath,"/data/ENDFB7.0");
             strcpy(csindex,p);
             strcat(csindex,"/data/ENDFB7.0/csindex");
             //  next in the datapath read the zaid nuclear file
             fp = fopen(csindex,"r");
             if(fp==NULL)
                 printf("can't open the csindex file !\n");
             fseek(fp,0L,SEEK_END);
             long int fpsize = ftell(fp);
             p = (char*)malloc(sizeof(char)*fpsize);
             fseek(fp,0L,SEEK_SET);
             fread(p,sizeof(char),fpsize,fp);
             if((temp=strstr(p,ace_zaid))==NULL)                    //find the sub-string
             {
                 printf("can't find the %s  in cross section library!\n",ace_zaid);
             }

             temp = strtok(temp," ");
             strtok(NULL," ");
             temp = strtok(NULL," ");
             strcat(datapath,"/");                                     ////>代码导致OTF_DOPPLER程序只能liunux运行
             strcat(datapath,temp);                                    //the datapath
             strtok(NULL," ");strtok(NULL," ");
             long long begin = atoll(strtok(NULL," "));                //数据开始的行数
             long long len   = atoll(strtok(NULL," "));                //数据长度，以字符串为单位
             free(p);                                                  //free the p char
             fclose(fp);
             fp=fopen(datapath,"r");
             if(fp==NULL)
                 printf("can't open the file  %s !\n",datapath);
             fseek(fp,begin,SEEK_SET);
             p = (char *)malloc((len+1) * sizeof(char));
             fread(p,sizeof(char),len+1,fp);
             fclose(fp);
         }

     }else{
        fp = fopen(ace_file,"r");
        if(fp==NULL)
             printf("you should use full path of the file or you set ace_file==\"\"  %s !\n",ace_file);
        fseek(fp,0L,SEEK_END);
        long int len = ftell(fp);
        fseek(fp,0L,SEEK_SET);
        p = (char *)malloc((len+1) * sizeof(char));
        fread(p,sizeof(char),len+1,fp);
        fclose(fp);
     }
#ifdef DEBUG
        printf("the csindex is %s\n   the datapath is %s\n",csindex,datapath);
        printf("the ACE file of %s is \n %s\n",ace_file,ace_zaid);
#endif

////  next read the ace file from p arrays
////  char * temp

        temp = strtok(p," ");
        if((int)strlen(temp)+1<16)
            strncpy(ace->_name,temp,(int)strlen(temp)+1); //zaid 维度大小
        assert(strcmp(ace->_name,ace_zaid)==0);

//        temp = strtok(NULL," \n");
//        ace->awr = atof(temp );atof(strtok(NULL," \n"));

        ace->_awr = atof(strtok(NULL," \n"));
        ace->_temp = atof(strtok(NULL," \n"));
        ace->_tempk = (ace->_temp)/BOLTZMANN;
        temp = strtok(NULL," \n");
        if((int)strlen(temp)+1<16)
            strncpy(ace->_date,temp,(int)strlen(temp)+1);
        temp = strtok(NULL,"\n");

// char *strncpy(char *dest, const char *src, size_t n);
 
        if((int)strlen(temp)+1<128)
            strncpy(ace->_info,temp,(int)strlen(temp)+1);  //可能会出现内存泄露
        for(i=0;i<4;i++)
            temp = strtok(NULL,"\n"); // the first four line is useless
//
        for(j=0;j<2;j++)
        {
            for(i=0;i<8;i++)
            {
                temp = strtok(NULL," ");
                (ace->_nxs)[j*8+i]=atoi(temp);
            }
        }
        for(j=0;j<4;j++)
        {
            for(i=0;i<8;i++)
            {
                temp = strtok(NULL," ");
                (ace->_jxs)[j*8+i]=atoi(temp);
            }
        }

   int number = (ace->_nxs)[0];
   (ace->_xss) = (double *)malloc(number*sizeof(double));
   for(i=0;i<number/4;i++)
   {
         for(j=0;j<4;j++){
             (ace->_xss)[i*4+j] = atof(strtok(NULL," "));
         }
   }
   if((number%4)!=0)
   {
      (ace->_xss)[4*(number/4)]=atof(strtok(NULL," "));
      
      for(j=1;j<(number%4);j++){
               (ace->_xss)[4*(number/4)+j] = atof(strtok(NULL," "));
      }
   }

#if    ERROR_DEBUG
   for(i=0;i<20;i++)
        printf("%d %e \n ",i,(ace->_xss)[i]);
   for(i=number-50;i<number;i++)
        printf("the last %d %e \n ",number-i,(ace->_xss)[i]);
#endif

/*
//next read the next data for doppler broaden
    ace->ne = ace->nxs[2] ;
    number = ace->ne;
    ace->e = (double*)malloc(number*sizeof(double));
    ace->sigt = (double*)malloc(number*sizeof(double));
    ace->sigc = (double *)malloc(number*sizeof(double));
    ace->sigs = (double *)malloc(number*sizeof(double));
    ace->sigh = (double*)malloc(number*sizeof(double));

//next read the unresulved data block
   lunr = (ace->jxs)[22];
   if(lunr>0)
   { 
     int n = (ace->xss)[lunr-1];
     int m = (ace->xss)[lunr];
     int nnn = 6 + n + n*m*6;
     ace->unr = (double*)malloc(nnn*sizeof(double));
     for(int i=0;i<nnn;i++)
        (ace->unr)[i] = (ace->xss)[lunr-1+i]; 
   }

    for(int i=0;i<(ace->ne);i++)
        (ace->e)[i] = (ace->xss)[i];
//next read the sigt
    for(int i=0;i<(ace->ne);i++)
        (ace->sigt)[i] = (ace->xss)[number+i];
    for(int i=0;i<(ace->ne);i++)
        (ace->sigc)[i] = (ace->xss)[number*2+i];
    for(int i=0;i<(ace->ne);i++)
        (ace->sigs)[i] = (ace->xss)[number*3+i];
    for(int i=0;i<(ace->ne);i++)
        (ace->sigh)[i] = (ace->xss)[number*4+i];
    
    int nmt = (ace->nxs)[3];
    int mtr = (ace->jxs)[2];
    int jtyr = (ace->jxs)[4];
    int jsig = (ace->jxs)[5];
    (ace->mt)=(int *)malloc(sizeof(int)*nmt);
    (ace->tyr) = (int *)malloc(sizeof(int)*nmt);
    (ace->lsig) = (int *)malloc(sizeof(int)*nmt);
    for(int i=0;i<nmt;i++)
        (ace->mt)[i] = (ace->xss)[mtr-1+i];
    for(int i=0;i<nmt;i++)
        (ace->tyr)[i] = (ace->xss)[jtyr-1+i];
    for(int i=0;i<nmt;i++)
        (ace->lsig)[i] = (ace->xss)[jsig-1+i];
*/
    free(p);  // free the temperary data in p data

    return 0;
}

