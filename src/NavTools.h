#ifndef _NavTools_H /* start of the NavTools.h */
#define _NavTools_H

const long long EARTH_RADIUS = 6371000;

struct coordinate
{
	double lat, lon;
};

double CalcBearing(double lat1, double long1, double lat2, double long2);
double CalcDistance(double lat1, double long1, double lat2, double long2);
struct coordinate CalcSmallestDistance(double lat1, double long1, double lat2, double long2, double lat3, double long3);

#endif /* _NavTools_H */
