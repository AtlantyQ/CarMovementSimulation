#ifndef CVECHICLECONTROLER_H
#define CVECHICLECONTROLER_H


#include <utility>
#include "IVechicleInterface.h"


class CVechicleCtrl : public IVechicleCtrl
{
    Q_OBJECT

public:
    CVechicleCtrl( QObject* parent = nullptr );
    ~CVechicleCtrl();

    void move( int dt );

private:

//Private functions
    void calculateMovement( int dt );
    void setPos( int posX, int posY );
    std::pair<int, int> getPos();

//Private members
    std::pair<int, int> position;
};

#endif // CVECHICLECONTROLER_H
