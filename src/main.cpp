#include <Rcpp.h>

#include "mgrs.h"

using namespace Rcpp;

//' Convert an MGRS string to latitude/longitude
//'
//' @md
//' @param MGRS an MGRS string
//' @param degrees convert to degrees? Default: `TRUE`
//' @export
//' @examples
//' mgrs_to_latlng("15TWG0000049776")
// [[Rcpp::export]]
NumericVector mgrs_to_latlng(std::string MGRS, bool degrees = true) {

  double lat, lng;
  long ret;

  ret = Convert_MGRS_To_Geodetic((char *)MGRS.c_str(), &lat, &lng);

  NumericVector coords = NumericVector::create(
    _["lat"] = degrees ? lat * 180.0/PI : lat,
    _["lng"] = degrees ? lng * 180.0/PI : lng
  );

  return(coords);

}

//' Convert latitude/longitude to MGRS string
//'
//' @md
//' @param latitude,longitude coordinates
//' @param degrees are latitude/longitude in degrees? Default: `TRUE`
//' @param precision level of precision for the conversion. Default `5`
//' @export
//' @examples
//' latlng_to_mgrs(42, -93)
// [[Rcpp::export]]
std::string latlng_to_mgrs(double latitude, double longitude,
                           bool degrees = true, int precision = 5) {

  if (degrees) {
    latitude *= PI / 180.0;
    longitude *= PI / 180.0;
  }

  char buf[80];
  int ret;

  ret = Convert_Geodetic_To_MGRS(latitude, longitude, precision, buf);

  return(std::string(buf));

}
