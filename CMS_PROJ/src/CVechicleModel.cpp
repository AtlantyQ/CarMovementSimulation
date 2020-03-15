#include "CVechicleModel.h"



CVechicleModel::CVechicleModel( std::string type, Qt::GlobalColor color, double factor, int maxSpeed, const QObject* parent )
{

}

CVechicleModel::CVechicleModel( CVechicleModel& x )
{

}

CVechicleModel& CVechicleModel::operator=( CVechicleModel& x )
{

}

CVechicleModel::~CVechicleModel()
{

}

void CVechicleModel::move( int dt )
{

}

Position CVechicleModel::calculateMovement( int dt )
{

}

void CVechicleModel::setPos( const Position& positon  )
{

}

IVechicleModel* CVechicleModel::getClone()
{
    return nullptr;// new CVechicleModel( *this );
}

Position CVechicleModel::getPos() const
{

}







