#' Convert 'MGRS' ('Military Grid Reference System') Coordinates From/To Other Coordinate Systems
#'
#' The 'Military Grid Reference System' ('MGRS') is the geocoordinate
#' standard used by 'NATO' militaries for locating points on the earth. The 'MGRS'
#' is derived from the 'Universal Transverse Mercator' ('UTM') grid system and
#' the universal polar stereographic ('UPS') grid system, but uses a different
#' labeling convention. The 'MGRS' is used for the entire earth. Methods are
#' provided to convert 'MGRS' coordinates to and from other coordinate systems.
#'
#' The origin of the MGRS grid, in the Pacific. Honolulu is in 4QFJ.
#'
#' \if{html}{
#' \figure{mgrs-grid.png}{options: width="850" alt="Figure: The origin of the MGRS grid, in the Pacific. Honolulu is in 4QFJ"}
#' }
#'
#' \if{latex}{
#' \figure{mgrs-grid.png}{options: width=30cm}
#' }
#'
#' [CC-BY-SA 3.0](https://en.wikipedia.org/wiki/Military_Grid_Reference_System#/media/File:MGRSgridOriginSchemeAA.png)
#'
#' @md
#' @name mgrs
#' @docType package
#' @author Bob Rudis (bob@@rud.is)
#' @useDynLib mgrs, .registration=TRUE
#' @importFrom Rcpp sourceCpp
"_PACKAGE"