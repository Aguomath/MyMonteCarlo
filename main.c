#include"header.h"

int main(int argc,char*argv[])
{
    FReadGeometry();
    FReadFace();
    FReadMaterial();

    FReadAce();
    FInit();
    FSimulate();
    FOutput();
    return 0;
}


