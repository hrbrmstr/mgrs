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
//' @param include_mgrs_ref if `TRUE` the data frame returned fill include
//'        the MGRS reference in a column named `mgrs`. Default: `TRUE`.
//' @export
//' @return `data.frame`
//' @examples
//' mgrs_to_latlng("15TWG0000049776")
// [[Rcpp::export]]
DataFrame mgrs_to_latlng(std::vector < std::string > MGRS, bool degrees = true,
                         bool include_mgrs_ref = true) {

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
    Rcpp::warning(
      "%d error%s encounterd while converting %d MGRS input strings.\nErrant MGRS strings will be turned into `NA` pairs.",
      err_ct, (err_ct > 1 ? "s" : ""), MGRS.size()
    );
  }

  if (include_mgrs_ref) {
    return(
      DataFrame::create(
        _["mgrs"] = MGRS,
        _["lat"] = lat_vec,
        _["lng"] = lng_vec,
        _["stringsAsFactors"] = false
      )
    );
  } else {
    return(
      DataFrame::create(
        _["lat"] = lat_vec,
        _["lng"] = lng_vec,
        _["stringsAsFactors"] = false
      )
    );
  }

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
//' @note vectorized
//' @param mgrs_string acharacter vector of MGRS strings
//' @param include_mgrs_ref if `TRUE` the data frame returned fill include
//'        the MGRS reference in a column named `mgrs`. Default: `TRUE`.
//' @return `data.frame`
//' @export
//' @examples
//' mgrs_to_utm("48PUV7729883034")
// [[Rcpp::export]]
DataFrame mgrs_to_utm(std::vector < std::string > mgrs_string, bool include_mgrs_ref = true) {

  long zone;
  char h_buf[80];
  double easting, northing;
  long ret;
  IntegerVector zonev = IntegerVector(mgrs_string.size());
  StringVector hemispherev = StringVector(mgrs_string.size());
  NumericVector eastingv = NumericVector(mgrs_string.size());
  NumericVector northingv = NumericVector(mgrs_string.size());

  for (unsigned int i=0; i<mgrs_string.size(); i++) {

    ret = Convert_MGRS_To_UTM((char *)mgrs_string[i].c_str(), &zone, h_buf, &easting, &northing);

    if (ret != MGRS_NO_ERROR) {
      Rcpp::warning("Error converting MGRS to UGM");
      zonev[i] = NA_INTEGER;
      hemispherev[i] = NA_STRING;
      eastingv[i] = NA_REAL;
      northingv[i] = NA_REAL;
    } else {
      h_buf[1] = '\0';
      zonev[i] = zone;
      hemispherev[i] = std::string(h_buf);
      eastingv[i] = easting;
      northingv[i] = northing;
    }

  }

  if (include_mgrs_ref) {
    return(
      DataFrame::create(
        _["mgrs"] = mgrs_string,
        _["zone"] = zonev,
        _["hemisphere"] = hemispherev,
        _["easting"] = eastingv,
        _["northing"] = northingv,
        _["stringsAsFactors"] = false
      )
    );
  } else {
    return(
      DataFrame::create(
        _["zone"] = zonev,
        _["hemisphere"] = hemispherev,
        _["easting"] = eastingv,
        _["northing"] = northingv,
        _["stringsAsFactors"] = false
      )
    );
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
//' @note vectorized
//' @param mgrs_string a character vector of MGRS strings
//' @param include_mgrs_ref if `TRUE` the data frame returned fill include
//'        the MGRS reference in a column named `mgrs`. Default: `TRUE`.
//' @return `data.frame`
//' @export
//' @examples
//' mgrs_to_ups("ZGC2677330125")
// [[Rcpp::export]]
DataFrame mgrs_to_ups(std::vector < std::string > mgrs_string, bool include_mgrs_ref = true) {

  char h_buf[80];
  double easting, northing;
  long ret;
  StringVector hemispherev = StringVector(mgrs_string.size());
  NumericVector eastingv = NumericVector(mgrs_string.size());
  NumericVector northingv = NumericVector(mgrs_string.size());

  for (unsigned int i=0; i<mgrs_string.size(); i++) {

    ret = Convert_MGRS_To_UPS((char *)mgrs_string[i].c_str(), h_buf, &easting, &northing);

    if (ret != MGRS_NO_ERROR) {
      Rcpp::warning("Error converting MGRS to UGM");
      hemispherev[i] = NA_STRING;
      eastingv[i] = NA_REAL;
      northingv[i] = NA_REAL;
    } else {
      h_buf[1] = '\0';
      hemispherev[i] = std::string(h_buf);
      eastingv[i] = easting;
      northingv[i] = northing;
    }

  }

  if (include_mgrs_ref) {
    return(
      DataFrame::create(
        _["mgrs"] = mgrs_string,
        _["hemisphere"] = hemispherev,
        _["easting"] = eastingv,
        _["northing"] = northingv,
        _["stringsAsFactors"] = false
      )
    );
  } else {
    return(
      DataFrame::create(
        _["hemisphere"] = hemispherev,
        _["easting"] = eastingv,
        _["northing"] = northingv,
        _["stringsAsFactors"] = false
      )
    );
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
