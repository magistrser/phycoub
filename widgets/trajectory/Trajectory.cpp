#include "Trajectory.h"

#include "VectorUtils.h"
#include "ProgrammingException.h"
#include "DrawUtils.h"

#if defined( DARWIN )
#    include <cmath>
#    include <OpenGL/glu.h>
#elif defined( WIN32 )
#    define _USE_MATH_DEFINES
#    include <math.h>
#    include <GL/glu.h>
#endif

namespace phywidgets
{

Trajectory::Trajectory( unsigned maxPointCount, double pointAngle, double lengthSkip )
    : _maxPointCount( maxPointCount )
    , _pointCosAngle( cos( pointAngle ) )
    , _lengthSkip( lengthSkip )
{
    PROGRAMMING_ASSERT( maxPointCount >= 2 );
    PROGRAMMING_ASSERT( pointAngle > 0 && pointAngle < M_PI_2 );
}

void Trajectory::update( const Vector& coordinate )
{
    // first two define first direction
    if ( _trajectory.size() < 3 )
    {
        _trajectory.push_back( coordinate );
        return;
    }

    // last equal particle coordinate
    _trajectory.pop_back();

    auto last = _trajectory.back();
    auto beforeLast = ( _trajectory.end()-- )--;

    Vector prevDirection = last - *beforeLast;
    Vector newDirection = coordinate - last;

    double cosBetweenDirections
        = VectorUtils::getCosBetweenVectors( prevDirection, newDirection );

    if ( cosBetweenDirections < _pointCosAngle )
    {
        _trajectory.push_back( coordinate );
    }

    if ( _trajectory.size() > _maxPointCount )
    {
        _trajectory.pop_front();
    }

    _trajectory.push_back( coordinate );
}

void Trajectory::clear()
{
    _trajectory.clear();
}

void Trajectory::drawTrajectory() const
{
    if ( _trajectory.size() < 2 )
    {
        return;
    }

    bool isFirst = true;
    Vector priviesCoordinate;

    for ( auto coordinate : _trajectory )
    {
        if ( isFirst )
        {
            priviesCoordinate = coordinate;
            isFirst = false;
            continue;
        }

        Vector distance = coordinate - priviesCoordinate;
        if ( distance.getModule() < _lengthSkip )
        {
            DrawUtils::drawLine( priviesCoordinate, coordinate, 0.001 );
        }

        priviesCoordinate = coordinate;
    }
}

} // namespace phywidgets