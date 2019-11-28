
[![Project Status: Active – The project has reached a stable, usable
state and is being actively
developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)
[![Signed
by](https://img.shields.io/badge/Keybase-Verified-brightgreen.svg)](https://keybase.io/hrbrmstr)
![Signed commit
%](https://img.shields.io/badge/Signed_Commits-23.5%25-lightgrey.svg)
[![Linux build
Status](https://travis-ci.org/hrbrmstr/mgrs.svg?branch=master)](https://travis-ci.org/hrbrmstr/mgrs)
[![Windows build
status](https://ci.appveyor.com/api/projects/status/github/hrbrmstr/mgrs?svg=true)](https://ci.appveyor.com/project/hrbrmstr/mgrs)
[![Coverage
Status](https://codecov.io/gh/hrbrmstr/mgrs/branch/master/graph/badge.svg)](https://codecov.io/gh/hrbrmstr/mgrs)
![Minimal R
Version](https://img.shields.io/badge/R%3E%3D-3.2.0-blue.svg)
![License](https://img.shields.io/badge/License-MIT-blue.svg)

# mgrs

Convert ‘MGRS’ (‘Military Grid Reference System’) Coordinates From/To
Other Coordinate Systems

## Description

The ‘Military Grid Reference System’ (‘MGRS’) is the geocoordinate
standard used by ‘NATO’ militaries for locating points on the earth. The
‘MGRS’ is derived from the ‘Universal Transverse Mercator’ (‘UTM’) grid
system and the universal polar stereographic (‘UPS’) grid system, but
uses a different labeling convention. The ‘MGRS’ is used for the entire
earth. Methods are provided to convert ‘MGRS’ coordinates to and from
other coordinate systems.

Essentially, a lightweight R wrapper around bits of
<https://svn.osgeo.org/gdal/trunk/gdal/frmts/nitf/>.

Decent reference on MGRS & UTM (Universal Transverse Mercator):
<https://www.luomus.fi/en/utm-mgrs-atlas-florae-europaeae>.

The origin of the MGRS grid, in the Pacific. Honolulu is in 4QFJ.

![The origin of the MGRS grid, in the Pacific. Honolulu is in
4QFJ.](man/figures/mgrs-grid.png)

[CC-BY-SA 3.0](https://en.wikipedia.org/wiki/Military_Grid_Reference_System#/media/File:MGRSgridOriginSchemeAA.png)

## What’s Inside The Tin

The following functions are implemented:

  - `latlng_to_mgrs`: Convert latitude/longitude to MGRS string
  - `mgrs_precision`: Return MGRS grid reference precision (in meters)
  - `mgrs_to_latlng`: Convert an MGRS string to latitude/longitude
  - `mgrs_to_ups`: Convert MGRS to UPS
  - `mgrs_to_utm`: Convert MGRS to UTM
  - `ups_to_latlng`: Convert UPS to Latitude/Longitude
  - `ups_to_mgrs`: Convert UPS to MGRS
  - `utm_to_latlng`: Convert UTM to Latitude/Longitude
  - `utm_to_mgrs`: Convert UTM to MGRS

## Installation

``` r
remotes::install_git("https://git.sr.ht/~hrbrmstr/mgrs")
# or
remotes::install_gitlab("hrbrmstr/mgrs")
# or
remotes::install_github("hrbrmstr/mgrs")
```

NOTE: To use the ‘remotes’ install options you will need to have the
[{remotes} package](https://github.com/r-lib/remotes) installed.

## Usage

``` r
library(mgrs)
library(hrbrthemes)
library(tidyverse)

# current version
packageVersion("wand")
## [1] '0.6.0'
```

### Basics

``` r
mgrs_to_latlng("33UXP04")
##      mgrs      lat      lng
## 1 33UXP04 48.20535 16.34593

latlng_to_mgrs(48.20535, 16.34593)
## [1] "33UXP0000040000"

mgrs_to_latlng("33UXP0500444996")
##              mgrs      lat      lng
## 1 33UXP0500444996 48.24947 16.41449

latlng_to_mgrs(48.24948, 16.41449)
## [1] "33UXP0500344996"

mgrs_to_latlng("24XWT783908")
##          mgrs      lat       lng
## 1 24XWT783908 83.62738 -32.66879

latlng_to_mgrs(83.62738, -32.66879)
## [1] "25XEN0410486507"

utm_to_mgrs(48, "N", 377299, 1483035)
## [1] "48PUV7729983035"

mgrs_to_utm("48PUV7729883034")
##              mgrs zone hemisphere easting northing
## 1 48PUV7729883034   48          N  377298  1483034

ups_to_mgrs("N", 2426773, 1530125)
## [1] "ZGC2677330125"

mgrs_to_ups("ZGC2677330125")
##            mgrs hemisphere easting northing
## 1 ZGC2677330125          N 2426773  1530125

grefs <- c("4Q", "4QFJ", "4QFJ16", "4QFJ1267", "4QFJ123678",
           "4QFJ12346789", "4QFJ1234567890")
mgrs_precision(grefs)
## # A tibble: 7 x 2
##   grid_ref       precision
##   <chr>              <dbl>
## 1 4Q                    NA
## 2 4QFJ              100000
## 3 4QFJ16             10000
## 4 4QFJ1267            1000
## 5 4QFJ123678           100
## 6 4QFJ12346789          10
## 7 4QFJ1234567890         1
```

### Better usage in the {tidyverse}

``` r
data.frame(
  id = 1:50, 
  mgrs = c("16SEB20", "09UXQ25", "12SVC48", "15SWU64", "11SKA54", "13SDC58", 
"18TYM20", "18SWH08", "17RML38", "17SKR77", "09RYR61", "12TTP62", 
"16TBK93", "16TEK73", "15TVG64", "14SNH75", "16SFG94", "15RWP68", 
"19TEL05", "18SUJ54", "19TBG89", "16TFN87", "15TUM73", "16SBB31", 
"15SWC44", "12TXS28", "14TML57", "11SND12", "19TCJ00", "18SWK62", 
"13SDU11", "18TVN87", "17SQV22", "14TMT13", "17TLE65", "14SPE73", 
"10TGP36", "18TTL93", "19TCG20", "17SNT42", "14TMQ40", "16SEE44", 
"14RNV27", "12SVJ72", "18TXQ90", "17SQB46", "11TKN95", "17SNC25", 
"16TBQ64", "13TCH16"),
  stringsAsFactors = FALSE
) -> sample_dta

dplyr::mutate(sample_dta, x = lapply(mgrs, mgrs_to_latlng, include_mgrs_ref = FALSE)) %>% 
  tidyr::unnest(x)
## # A tibble: 50 x 4
##       id mgrs      lat    lng
##    <int> <chr>   <dbl>  <dbl>
##  1     1 16SEB20  32.5  -86.8
##  2     2 09UXQ25  49.2 -127. 
##  3     3 12SVC48  34.2 -112. 
##  4     4 15SWU64  34.7  -92.3
##  5     5 11SKA54  36.5 -120. 
##  6     6 13SDC58  38.7 -106. 
##  7     7 18TYM20  41.5  -72.4
##  8     8 18SWH08  38.7  -75.0
##  9     9 17RML38  27.8  -81.7
## 10    10 17SKR77  32.2  -83.4
## # … with 40 more rows
```

### Visual Verification

``` r
library(purrr)
library(ggplot2)

# precision == 1

c("16SEB20", "09UXQ25", "12SVC48", "15SWU64", "11SKA54", "13SDC58", 
"18TYM20", "18SWH08", "17RML38", "17SKR77", "09RYR61", "12TTP62", 
"16TBK93", "16TEK73", "15TVG64", "14SNH75", "16SFG94", "15RWP68", 
"19TEL05", "18SUJ54", "19TBG89", "16TFN87", "15TUM73", "16SBB31", 
"15SWC44", "12TXS28", "14TML57", "11SND12", "19TCJ00", "18SWK62", 
"13SDU11", "18TVN87", "17SQV22", "14TMT13", "17TLE65", "14SPE73", 
"10TGP36", "18TTL93", "19TCG20", "17SNT42", "14TMQ40", "16SEE44", 
"14RNV27", "12SVJ72", "18TXQ90", "17SQB46", "11TKN95", "17SNC25", 
"16TBQ64", "13TCH16") -> mgrs_state_centers

mgrs_to_latlng(mgrs_state_centers) %>% 
  ggplot(aes(lng, lat)) +
  geom_point(shape=22, size=2, color="black", fill="white") +
  coord_map("polyconic") +
  theme_ft_rc(grid="XY")
```

<img src="man/figures/README-ex3-1.png" width="960" />

## mgrs Metrics

| Lang         | \# Files |  (%) |  LoC |  (%) | Blank lines |  (%) | \# Lines |  (%) |
| :----------- | -------: | ---: | ---: | ---: | ----------: | ---: | -------: | ---: |
| C            |        5 | 0.26 | 1854 | 0.74 |         334 | 0.62 |      918 | 0.52 |
| C++          |        2 | 0.11 |  339 | 0.13 |          63 | 0.12 |       99 | 0.06 |
| C/C++ Header |        5 | 0.26 |  181 | 0.07 |          74 | 0.14 |      546 | 0.31 |
| R            |        6 | 0.32 |   91 | 0.04 |          28 | 0.05 |      158 | 0.09 |
| Rmd          |        1 | 0.05 |   54 | 0.02 |          39 | 0.07 |       40 | 0.02 |

## Code of Conduct

Please note that this project is released with a Contributor Code of
Conduct. By participating in this project you agree to abide by its
terms.
