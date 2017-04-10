#include <Rcpp.h>

#include "ups.h"
#include "utm.h"
#include "mgrs.h"

using namespace Rcpp;

//' Convert an MGRS string to latitude/longitude
//'
//' @md
//' @note vectorized
//' @param MGRS an MGRS string
//' @param degrees convert to degrees? Default: `TRUE`
//' @export
//' @return `data.frame`
//' @examples
//' mgrs_to_latlng("15TWG0000049776")
// [[Rcpp::export]]
DataFrame mgrs_to_latlng(std::vector < std::string > MGRS, bool degrees = true) {

  double lat, lng;
  long ret, err_ct = 0;
  NumericVector lat_vec(MGRS.size());
  NumericVector lng_vec(MGRS.size());

  for (unsigned int i=0; i<MGRS.size(); i++) {

    if ((i % 10000) == 0) Rcpp::checkUserInterrupt();

    ret = Convert_MGRS_To_Geodetic((char *)MGRS[i].c_str(), &lat, &lng);

    if (ret != UTM_NO_ERROR) {
      err_ct += 1;
      lat_vec[i] = NA_REAL;
      lng_vec[i] = NA_REAL;
    } else {
      lat_vec[i] = degrees ? lat * 180.0/PI : lat;
      lng_vec[i] = degrees ? lng * 180.0/PI : lng;
    }

  }

  if (err_ct > 0) {
    Rcpp::warning("One or more errors encounterd while converting %d MGRS input strings");
  }

  return(DataFrame::create(_["mgrs"] = MGRS,
                           _["lat"] = lat_vec,
                           _["lng"] = lng_vec,
                           _["stringsAsFactors"] = false));

}

//' Convert latitude/longitude to MGRS string
//'
//' @md
//' @param latitude,longitude coordinates
//' @param degrees are latitude/longitude in degrees? Default: `TRUE`
//' @param precision 0:5; level of precision for the conversion. Default `5`
//' @export
//' @examples
//' latlng_to_mgrs(42, -93)
// [[Rcpp::export]]
String latlng_to_mgrs(double latitude, double longitude,
                      bool degrees = true, int precision = 5) {

  if (degrees) {
    latitude *= PI / 180.0;
    longitude *= PI / 180.0;
  }

  char buf[80];
  int ret;

  ret = Convert_Geodetic_To_MGRS(latitude, longitude, precision, buf);

  if (ret != MGRS_NO_ERROR) {
    Rcpp::warning("Error conveting latitude/longitudfe to MGRS");
    return(NA_STRING);
  } else {
    return(std::string(buf));
  }

}

//' Convert UTM to MGRS
//'
//' @md
//' @param zone 1:60
//' @param hemisphere South (`S`) or North (`N`)
//' @param easting,northing easting (X) / northing (Y) (meters)
//' @param precision 0:5; level of precision for the conversion. Default `5`
//' @export
//' @examples
//' utm_to_mgrs(48, "N", 377299, 1483035)
// [[Rcpp::export]]
String utm_to_mgrs(long zone, std::string hemisphere,
                   double easting, double northing,
                   long precision = 5) {

  char buf[80];
  long ret;

  ret = Convert_UTM_To_MGRS(zone, hemisphere.c_str()[0], easting, northing,
                            precision, (char *)&buf);

  if (ret != UTM_NO_ERROR) {
    Rcpp::warning("Error converting UTM to MGRS");
    return(NA_STRING);
  } else {
    return(std::string(buf));
  }

}

//' Convert MGRS to UTM
//'
//' @md
//' @param mgrs_string an MGRS string
//' @return `data.frame`
//' @export
//' @examples
//' mgrs_to_utm("48PUV7729883034")
// [[Rcpp::export]]
DataFrame mgrs_to_utm(std::string mgrs_string) {

  long zone;
  char h_buf[80];
  double easting, northing;
  long ret;

  ret = Convert_MGRS_To_UTM((char *)mgrs_string.c_str(), &zone, h_buf, &easting, &northing);

  if (ret != MGRS_NO_ERROR) {
    Rcpp::warning("Error converting MGRS to UGM");
    return(DataFrame::create(_["mgrs"] = mgrs_string,
                             _["zone"] = NA_INTEGER,
                             _["hemisphere"] = NA_STRING,
                             _["easting"] = NA_REAL,
                             _["northing"] = NA_REAL,
                             _["stringsAsFactors"] = false));
  } else {
    h_buf[1] = '\0';
    return(DataFrame::create(_["mgrs"] = mgrs_string,
                             _["zone"] = zone,
                             _["hemisphere"] = std::string(h_buf),
                             _["easting"] = easting,
                             _["northing"] = northing,
                             _["stringsAsFactors"] = false));
  }
}

//' Convert UPS to MGRS
//'
//' @md
//' @param hemisphere South (`S`) or North (`N`)
//' @param easting,northing easting (X) / northing (Y) (meters)
//' @param precision 0:5; level of precision for the conversion. Default `5`
//' @export
//' @examples
//' ups_to_mgrs("N", 2426773, 1530125)
// [[Rcpp::export]]
String ups_to_mgrs(std::string hemisphere,
                   double easting, double northing,
                   long precision = 5) {

  char buf[80];
  long ret;

  ret = Convert_UPS_To_MGRS(hemisphere.c_str()[0], easting, northing,
                            precision, (char *)&buf);

  if (ret != UPS_NO_ERROR) {
    Rcpp::warning("Error converting UPS to MGRS");
    return(NA_STRING);
  } else {
    return(std::string(buf));
  }

}

//' Convert MGRS to UPS
//'
//' @md
//' @param mgrs_string an MGRS string
//' @return `data.frame`
//' @export
//' @examples
//' mgrs_to_ups("ZGC2677330125")
// [[Rcpp::export]]
DataFrame mgrs_to_ups(std::string mgrs_string) {

  char h_buf[80];
  double easting, northing;
  long ret;

  ret = Convert_MGRS_To_UPS((char *)mgrs_string.c_str(), h_buf, &easting, &northing);

  if (ret != MGRS_NO_ERROR) {
    Rcpp::warning("Error converting MGRS to UPS");
    return(DataFrame::create(_["mgrs"] = mgrs_string,
                             _["hemisphere"] = NA_STRING,
                             _["easting"] = NA_REAL,
                             _["northing"] = NA_REAL,
                             _["stringsAsFactors"] = false));
  } else {
    h_buf[1] = '\0';
    return(DataFrame::create(_["mgrs"] = mgrs_string,
                             _["hemisphere"] = std::string(h_buf),
                             _["easting"] = easting,
                             _["northing"] = northing,
                             _["stringsAsFactors"] = false));
  }
}

//' Convert UPS to Latitude/Longitude
//'
//' @md
//' @param hemisphere South (`S`) or North (`N`)
//' @param easting,northing easting (X) / northing (Y) (meters)
//' @param degrees convert to degrees? Default: `TRUE`
//' @export
//' @examples
//' ups_to_latlng("N", 2426773, 1530125)
// [[Rcpp::export]]
NumericVector ups_to_latlng(std::string hemisphere,
                            double easting, double northing,
                            bool degrees = true) {

  double lat, lng;
  long ret;

  ret = Convert_UPS_To_Geodetic(hemisphere.c_str()[0], easting, northing, &lat, &lng);

  NumericVector coords;

  if (ret != UPS_NO_ERROR) {
    Rcpp::warning("Error converting UPS to latitude/longitude");
    coords = NumericVector::create(
      _["lat"] = NA_REAL,
      _["lng"] = NA_REAL
    );
  } else {
    coords = NumericVector::create(
      _["lat"] = degrees ? lat * 180.0/PI : lat,
      _["lng"] = degrees ? lng * 180.0/PI : lng
    );
  }

  return(coords);

}

//' Convert UTM to Latitude/Longitude
//'
//' @md
//' @param zone 1:60
//' @param hemisphere South (`S`) or North (`N`)
//' @param easting,northing easting (X) / northing (Y) (meters)
//' @param degrees convert to degrees? Default: `TRUE`
//' @export
//' @examples
//' utm_to_latlng(48, "N", 377299, 1483035)
// [[Rcpp::export]]
NumericVector utm_to_latlng(long zone, std::string hemisphere,
                            double easting, double northing,
                            bool degrees = true) {

  double lat, lng;
  long ret;

  ret = Convert_UTM_To_Geodetic(zone, hemisphere.c_str()[0], easting, northing, &lat, &lng);

  NumericVector coords;

  if (ret != UTM_NO_ERROR) {
    Rcpp::warning("Error converting UTM to latitude/longitude");
    coords = NumericVector::create(
      _["lat"] = NA_REAL,
      _["lng"] = NA_REAL
    );
  } else {
    coords = NumericVector::create(
      _["lat"] = degrees ? lat * 180.0/PI : lat,
      _["lng"] = degrees ? lng * 180.0/PI : lng
    );
  }

  return(coords);

}
