#ifndef _GPSTools_H /* start of the GPSTools.h */
#define _GPSTools_H

const long long EARTH_RADIUS = 6371000;

struct coordinate
{
	double lat, lon;
};

double CalcHeading(double lat1, double long1, double lat2, double long2);
double CalcDistance(double lat1, double long1, double lat2, double long2);
struct point CalcSmallestDistance(double lat1, double long1, double lat2, double long2, double lat3, double long3);

#endif /* _GPSTools_H */
