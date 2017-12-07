.precision_map <- c(`0`=100000, `1`=10000, `2`=1000, `3`=100, `4`=10, `5`=1)

#' Return MGRS grid reference precision (in meters)
#'
#' MGRS coordinates represent a "square" with a certain level of precision. See Details for more info.
#'
#' An MGRS grid reference is a point reference system. When the term 'grid square' is used,
#' it can refer to a square with a side length of 10 km (6 mi), 1 km, 100 m (328 ft), 10 m
#' or 1 m, depending on the precision of the coordinates provided. (In some cases, squares
#' adjacent to a Grid Zone Junction (GZJ) are clipped, so polygon is a better descriptor of
#' these areas.) The number of digits in the numerical location must be even: 0, 2, 4, 6, 8
#' or 10, depending on the desired precision. When changing precision levels, it is important
#' to truncate rather than round the easting and northing values to ensure the more precise
#' polygon will remain within the boundaries of the less precise polygon. Related to this is
#' the primacy of the southwest corner of the polygon being the labeling point for an entire
#' polygon. In instances where the polygon is not a square and has been clipped by a grid
#' zone junction, the polygon keeps the label of the southwest corner as if it had not been
#' clipped.
#'
#' For example (spaces used for clarity):
#'
#' \describe{
#' \item{4Q}{precision level 6x8 degrees (in most cases) - function returns \code{NA} for this}
#' \item{4QFJ}{precision level 100 km}
#' \item{4QFJ 1 6}{precision level 10 km}
#' \item{4QFJ 12 67}{precision level 1 km}
#' \item{4QFJ 123 678}{precision level 100 m}
#' \item{4QFJ 1234 6789}{precision level 10 m}
#' \item{4QFJ 12345 67890}{precision level 1 m}
#' }
#'
#' @md
#' @param x character vector of MGRS grid references
#' @return data frame with `grid_ref` and `precision` columns. `precision` is in meters.
#' @references <https://en.wikipedia.org/wiki/Military_Grid_Reference_System#Grid_zone_designation>
#' @export
#' @examples
#' grefs <- c("4Q", "4QFJ", "4QFJ16", "4QFJ1267", "4QFJ123678",
#'            "4QFJ12346789", "4QFJ1234567890")
#' mgrs_precision(grefs)
mgrs_precision <- function(x) {

  x <- gsub("[[:space:]]", "", x)
  xchars <- sapply(x, nchar)

  y <- sub("^[[:digit:]]{1,2}.{1,3}", "", x)
  y <- sapply(y, nchar)
  y <- as.integer(y / 2)
  y <- as.character(y)
  y <- ifelse(xchars==2, NA_integer_, .precision_map[y])

  y <- data.frame(grid_ref = x, precision = unname(y), stringsAsFactors=FALSE)
  class(y) <- c("tbl_df", "tbl", "data.frame")

  y

}
