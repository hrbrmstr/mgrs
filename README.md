
[![Project Status: Active - The project has reached a stable, usable state and is being actively developed.](http://www.repostatus.org/badges/0.1.0/active.svg)](http://www.repostatus.org/#active) [![codecov](https://codecov.io/gh/hrbrmstr/mgrs/branch/master/graph/badge.svg)](https://codecov.io/gh/hrbrmstr/mgrs) [![Travis-CI Build Status](https://travis-ci.org/hrbrmstr/mgrs.svg?branch=master)](https://travis-ci.org/hrbrmstr/mgrs) [![keybase verified](https://img.shields.io/badge/keybase-verified-brightgreen.svg)](https://gist.github.com/hrbrmstr/be2f2c14fd78cac24697)

`mgrs` : Convert 'MGRS' (Military Grid Reference System) References To and From Other Coordinate Systems

Essentially, a lightweight R wrapper around bits of <https://svn.osgeo.org/gdal/trunk/gdal/frmts/nitf/>.

Decent reference on MGRS & UTM (Universal Transverse Mercator): <https://www.luomus.fi/en/utm-mgrs-atlas-florae-europaeae>.

The following functions are implemented:

-   `latlng_to_mgrs`: Convert latitude/longitude to MGRS string
-   `mgrs_to_latlng`: Convert an MGRS string to latitude/longitude
-   `mgrs_to_ups`: Convert MGRS to UPS
-   `mgrs_to_utm`: Convert MGRS to UTM
-   `ups_to_mgrs`: Convert UPS to MGRS
-   `utm_to_mgrs`: Convert UTM to MGRS

### TODO

-   Find all the folks/projects I need to add in the `DESCRIPTION` for auth/ctb & docs
-   Vectorize ALL THE THINGS
-   <strike>Add in support for the other MGRS conversion thingys</strike>
-   More error checking (basic checking is done)
-   Precision validation
-   More tests (basic testing is done)

### Installation

``` r
devtools::install_github("hrbrmstr/mgrs")
```

### Usage

``` r
library(mgrs)

# current verison
packageVersion("mgrs")
```

    ## [1] '0.1.0'

``` r
mgrs_to_latlng("33UXP04")
```

    ##      lat      lng 
    ## 48.20535 16.34593

``` r
latlng_to_mgrs(48.20535, 16.34593)
```

    ## [1] "33UXP0000040000"

``` r
mgrs_to_latlng("33UXP0500444996")
```

    ##      lat      lng 
    ## 48.24947 16.41449

``` r
latlng_to_mgrs(48.24948, 16.41449)
```

    ## [1] "33UXP0500344996"

``` r
mgrs_to_latlng("24XWT783908")
```

    ##       lat       lng 
    ##  83.62738 -32.66879

``` r
latlng_to_mgrs(83.62738, -32.66879)
```

    ## [1] "25XEN0410486507"

``` r
utm_to_mgrs(48, "N", 377299, 1483035)
```

    ## [1] "48PUV7729983035"

``` r
mgrs_to_utm("48PUV7729883034")
```

    ##              mgrs zone hemisphere easting northing
    ## 1 48PUV7729883034   48          N  377298  1483034

``` r
ups_to_mgrs("N", 2426773, 1530125)
```

    ## [1] "ZGC2677330125"

``` r
mgrs_to_ups("ZGC2677330125")
```

    ##            mgrs hemisphere easting northing
    ## 1 ZGC2677330125          N 2426773  1530125

### Test Results

``` r
library(mgrs)
library(testthat)

date()
```

    ## [1] "Sun Apr  9 23:30:49 2017"

``` r
test_dir("tests/")
```

    ## testthat results ========================================================================================================
    ## OK: 10 SKIPPED: 0 FAILED: 0
    ## 
    ## DONE ===================================================================================================================

### Code of Conduct

Please note that this project is released with a [Contributor Code of Conduct](CONDUCT.md). By participating in this project you agree to abide by its terms.
