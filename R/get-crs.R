# #' Retrieve {sf}-compatible CRS from various package function outputs
# #'
# #' @param mgs_result the output of one of the {mgrs} functions
# #' @return either an EPSG value, a PROJ string, a vector of
# #'         PROJ strings (if the UTM references vary), or
# #'         `NA` if the input is just an MGRS ref string or unknown
# #'         (with a warning)
# #' @export
# get_crs <- function(mgrs_result) {
#
#   if (inherits(mgrs_result, "character")) {
#     warning("Cannot retrieve CRS for an MGRS reference")
#     return(NA_character_)
#   }
#
#   if (!inherits(mgrs_result, "data.frame")) {
#     warning("Supplied parameter is not an output of an {mgrs} transform")
#     return(NA_character_)
#   }
#
#   # lat/lng data frane
#
#   if (length(setdiff(
#       x = c("mgrs", "lat", "lng"),
#       y = colnames(mgrs_result)
#     )) == 0) {
#     return(4326L)
#   }
#
#   # UTM data frame
#
#   if (length(setdiff(
#     x = c("mgrs", "zone", "hemisphere", "easting", "northing"),
#     y = colnames(mgrs_result)
#   )) == 0) {
#
#
#
#   }
#
#
# }
#
#
#
# setdiff(
#   c("lat", "lng"),
#   c("mgrs", "zone", "hemisphere", "easting", "northing")
# )
#
