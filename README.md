
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
-   Add in support for the other MGRS conversion thingys
-   Error checking
-   Precision validation
-   Tests (etc)

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
