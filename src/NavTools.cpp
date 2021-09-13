#include<cmath>
#include"NavTools.h"

double CalcDistance(double lat1, double long1, double lat2, double long2)
{
	double sin1 = sin((lat1 - lat2) / 2);
	double sin2 = sin((long1 - long2) / 2);
	return EARTH_RADIUS * (2 * asin((sin1 * sin1) + (cos(lat1) * cos(lat2) * sin2 * sin2)));
}

double CalcBearing(double lat1, double long1, double lat2, double long2)
{
	// double atan_ = atan((sin(long1 - long2) * cos(lat1) * cos(lat2) * sin(lat2)) - (cos(long1 - long2) * sin(lat1) * cos(lat2)));
	// return EARTH_RADIUS * (atan_ * atan_);
	double deltaLong = (long2 - long1);
	double y = sin(deltaLong) * cos(lat2);
	double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(deltaLong);
	double brng = atan2(y, x);
	brng = brng * (180.0/3.141592653589793238463); // radians to degrees
	brng = fmod((brng + 360), 360);
	//brng = 360 - brng; // count degrees counter-clockwise - remove to make clockwise
	return brng;
}

struct coordinate CalcSmallestDistance(double lat1, double long1, double lat2, double long2, double lat3, double long3)
{
	//Keep in mind! This funcion is *not* meant to be readable, it focuses on purely performance, you'd be better off implementing yourself rather than understand this
	struct point
	{
		double x, y, z;
	}a, b, c;
	{
		//calculate cartesian coordinates
		double tempcos = cos(lat1);
		a.y = tempcos * sin(long1) * EARTH_RADIUS;
		a.x = tempcos * cos(long1) * EARTH_RADIUS;
		a.z = sin(lat1) * EARTH_RADIUS;
		tempcos = cos(lat2);
		b.y = tempcos * sin(long2) * EARTH_RADIUS;
		b.x = tempcos * cos(long2) * EARTH_RADIUS;
		b.z = sin(lat2) * EARTH_RADIUS;
		tempcos = cos(lat3);
		c.y = tempcos * sin(long3) * EARTH_RADIUS;
		c.x = tempcos * cos(long3) * EARTH_RADIUS;
		c.z = sin(lat3) * EARTH_RADIUS;
	}
	{
		//math black magic that projects c to a plane perpendacular to ab equator
		struct point n = {.x = ((a.y * a.z) - (b.z * b.y)), .y = ((a.z * b.x) - (a.x * b.z)), .z = ((a.x * b.y) - (a.y * b.x))};
		double dotcn = (c.x * n.x) + (c.y * n.y) + (c.z * n.z);
		double dotcc = (c.x * c.x) + (c.y * c.y) + (c.z * c.z);
		double temp = dotcn / dotcc;
		struct point temppoint = {.x = n.x * temp, .y = n.y * temp, .z = n.z * temp};
		c = {.x = c.x - temppoint.x, .y = c.y - temppoint.y, .z = c.z - temppoint.z};
	}
	//calculating the actual point
	double cosine;
	struct point ac = {.x = c.x - a.x, .y = c.y - a.y, .z = c.z - a.z};
	struct point ab = {.x = b.x - a.x, .y = b.y - a.y, .z = b.z - a.z};
	cosine = (ac.x * ab.x) + (ac.y * ab.y) + (ac.z * ab.z);
	cosine /= sqrt((ac.x * ac.x) + (ac.y + ac.y) + (ac.z + ac.z));
	ab = {.x = ab.x * cosine, .y = ab.y * cosine, .z = ab.z * cosine};
	ab = {.x = ab.x + a.x, .y = ab.y + a.y, .z = ab.z + a.z};
	struct coordinate result = {.lat = sqrt((ab.x * ab.x) + (ab.y * ab.y) / ab.z), .lon = atan(ab.y / ab.x)};
	return result;
}
