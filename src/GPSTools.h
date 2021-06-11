#ifndef _GPSTools_H /* start of the OSAB.h */
#define _GPSTools_H

class GPSTools
{
  public:
//     GPSTools();
    CalcHeading(double lat1, double long1, double lat2, double long2);
    CalcDistance(double lat1, double long1, double lat2, double long2);
  private:
    
};

#endif /* _GPSTools_H */
