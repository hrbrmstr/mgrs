#ifndef MGRS_H
#define MGRS_H

#define MGRS_NO_ERROR                0x0000
#define MGRS_LAT_ERROR               0x0001
#define MGRS_LON_ERROR               0x0002
#define MGRS_STRING_ERROR            0x0004
#define MGRS_PRECISION_ERROR         0x0008
#define MGRS_A_ERROR                 0x0010
#define MGRS_INV_F_ERROR             0x0020
#define MGRS_EASTING_ERROR           0x0040
#define MGRS_NORTHING_ERROR          0x0080
#define MGRS_ZONE_ERROR              0x0100
#define MGRS_HEMISPHERE_ERROR        0x0200
#define MGRS_LAT_WARNING             0x0400

#ifdef __cplusplus
extern "C" {
#endif

long Set_MGRS_Parameters(double a, double f, char *Ellipsoid_Code);
void Get_MGRS_Parameters(double *a, double *f, char *Ellipsoid_Code);
long Convert_Geodetic_To_MGRS (double Latitude, double Longitude, long Precision, char *MGRS);
long Convert_MGRS_To_Geodetic (char *MGRS, double *Latitude, double *Longitude);
long Convert_UTM_To_MGRS (long Zone, char Hemisphere, double Easting,  double Northing,
                          long Precision, char *MGRS);
long Convert_MGRS_To_UTM (char *MGRS, long *Zone, char *Hemisphere, double *Easting,
                          double *Northing);
long Convert_UPS_To_MGRS (char Hemisphere, double Easting, double Northing, long Precision,
                          char *MGRS);
long Convert_MGRS_To_UPS (char *MGRS, char *Hemisphere, double *Easting, double *Northing);

#ifdef __cplusplus
}
#endif

#endif /* MGRS_H */
