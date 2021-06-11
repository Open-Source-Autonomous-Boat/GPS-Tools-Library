#include "GPSTools.h"
#include<math.h>

// GPSTools::GPSTools()
// {
// 	
// }

GPSTools::CalcDistance(double lat1, double long1, double lat2, double long2)
{
	double sin1 = sin((lat1 - lat2) / 2);
	double sin2 = sin((long1 - long2) / 2);
	return (2 * asin((sin1 * sin1) + (cos(lat1) * cos(lat2) * sin2 * sin2)));
}

GPSTools::CalcHeading(double lat1, double long1, double lat2, double long2)
{
	double atan_ = atan((sin(long1 - long2) * cos(lat1) * cos(lat2) * sin(lat2)) - (cos(long1 - long2) * sin(lat1) * cos(lat2)));
	return (atan_ * atan_);
}
