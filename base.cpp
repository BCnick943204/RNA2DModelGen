#include "base.h"

Base::Base(char base_type)
{
    base_size = QSize(50,50);
    setBasePic(base_type);
}


// Specify the picture to use for the base from
// the specified base type
int Base::setBasePic(char base_type){
    switch(base_type){
    case 'A':
        setPixmap(QPixmap(":/RNABasePics/images/RNA_A_Base.png").scaled(base_size));
        break;

    case 'U':
        setPixmap(QPixmap(":/RNABasePics/images/RNA_U_Base.png").scaled(base_size));
        break;

    case 'C':
        setPixmap(QPixmap(":/RNABasePics/images/RNA_C_Base.png").scaled(base_size));
        break;

    case 'G':
        setPixmap(QPixmap(":/RNABasePics/images/RNA_G_Base.png").scaled(base_size));
        break;

    default:
        perror("Incorrect RNA base specified");
        return -1;
    }
    return 0;
}

