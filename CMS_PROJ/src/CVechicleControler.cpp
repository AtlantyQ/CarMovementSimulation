#include "CVechicleControler.h"



CVechicleCtrl::CVechicleCtrl( Position position, const QObject* parent )
{

}

CVechicleCtrl::CVechicleCtrl( CVechicleCtrl& x )
{

}

CVechicleCtrl& CVechicleCtrl::operator=( CVechicleCtrl& x )
{

}

CVechicleCtrl::~CVechicleCtrl()
{

}

void CVechicleCtrl::move( int dt )
{

}

Position CVechicleCtrl::calculateMovement( int dt )
{

}

void CVechicleCtrl::setPos( const Position& positon  )
{

}

Position CVechicleCtrl::getPos() const
{


}

IVechicleCtrl* CVechicleCtrl::getClone()
{
    return new CVechicleCtrl( *this );
}





