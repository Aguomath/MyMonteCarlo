#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//#include<math>
#include<assert.h>
#include<ctype.h>
/*
 *  this program is named JMCT-minicore
 *  the project is proposed by JMCT code which is developed by Li Deng & Gang Li
 *
 */
/*
struct CELL;
struct CELLLIST;
struct FACELIST;
struct FACE;
struct GFACE;
struct MATERIAL;
struct NUCLIDE;
struct ATOM;     // the nuclide is for ace
struct GATOM;
*/
typedef struct ATOM{     // the nuclide is for ace
    char _name[16];
    double _awr;
    double _temp;     // the ace temeperature in energy eV
    double _tempk;    // the ace temperature in K 
    char _date[16];   // the date in ACE file
    char _info[128];  // the information in ACE file

    int _nxs[16];     // the nxs array
    int _jxs[32];     // the jxs array
    double *_xss;     // the xss array
}ATOM;

typedef struct NUCLIDE{
    ATOM* _atom;
    double _density;
    struct NUCLIDE* _next;
}NUCLIDE;

struct GATOM{
    ATOM _atom;
    struct GATOM * _next ;
};

struct MATERIAL{
    int _matid; 
    double _totaldensity;
    char _material[128] ;
    struct NUCLIDE * _nuclide ;
};


struct CELL{
    long long int _id;
    char _name[128];
    struct MATERIAL * _mat;
    struct FACELIST*_facelist;
};


struct CELLLIST{
    struct CELL _cell;
    struct CELLLIST *_next;
};

struct FACELIST{
    int _normal;
    struct FACE *_face;
    struct FACELIST* _next; 
};


/*
 * 
 *  type 1 is the plane  Ax + By + Cz - D = 0  (ABCD)
 *  type 2 is the sphere  (x-x*)^2 + (y-y*)^2 + (z-z*)^2 = R^2 
 *                           x*  y*  z*  R
 *  type 3 is the cylinder
 *                        type 31 (y-y*)^2 + (z-z*)^2 = R^2
 *                        type 32 (x-x*)^2 + (z-z*)^2 = R^2
 *                        type 33 (x-x*)^2 + (y-y*)^2 = R^2
 *
 */

struct FACE{
    int _type;            // the type of the face
    int _numbercoefficient;          // represent the number of coefficients in array
    double *_coefficient; // the double array
};

struct GFACE{
   int  _faceid;
   struct FACE _face;
   struct GFACE * _next ;
};



/*
 * next global data for simulation
 * */
struct CELLLIST *gcelllist ;
struct GFACE *gface;


char * inputbuf;


// the three struct should be in a structure
int region;
char *buf;
int index;

/**
 *  next the simple function of the code
 */

void FReadGeometry();

void FReadAce();

void FInit();

void FOutput();

void FSimulate();

void FReadFace();

struct FACELIST *FNewFaceList();
struct GFACE * FNewGface();

#define MININF  -100000
