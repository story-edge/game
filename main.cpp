#include <string.h>
#include "goBan.hpp"
#include "networkGoban.hpp"

int main(int argc, const char *argv[])
{


    if(argc < 2){
        fprintf(stderr,"Usage : %s <local|network>\n",argv[0]);
        return -1;
    }

    if(strcmp(argv[1],"local") == 0){
        GoBan goBan("b","w");
        goBan.run();
    }else if(strcmp(argv[1],"network") == 0){
        NetworkGoBan networkGoBan("w","b");
        networkGoBan.run();
    }else{
        cout << "unknown mode : " << argv[1] << endl;
        return -1;
    }

    return 0;
}
