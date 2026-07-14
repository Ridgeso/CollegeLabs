#include "MapDistance.h"
#include <cmath>

MapDistance::MapDistance(const std::string& conection, const MapPoint& startPosition, const MapPoint& endPosition)
    : m_conectionName(conection),
    m_pointDistance(endPosition.m_latitude - startPosition.m_latitude,
                    endPosition.m_longitude - startPosition.m_longitude)
{

}


void MapDistance::print() const
{
    std::cout << "MapDistance [" << m_conectionName << "]: (" << m_pointDistance.m_latitude << ", " << m_pointDistance.m_longitude << ")" << std::endl;
}

double MapDistance::dist() const
{
    return std::sqrt(m_pointDistance.m_latitude * m_pointDistance.m_latitude + m_pointDistance.m_longitude * m_pointDistance.m_longitude);
}