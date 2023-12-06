library(mgrs)

expect_equal(
  mgrs_to_latlng("33UXP04"),
  structure(
    list(
      mgrs = "33UXP04",
      lat = 48.2053484084679,
      lng = 16.3459269599006),
    .Names = c("mgrs", "lat", "lng"),
    row.names = c(NA, -1L), class = "data.frame"
  )
)

expect_equal(
  latlng_to_mgrs(48.20535, 16.34593), "33UXP0000040000"
)

expect_equal(
  mgrs_to_latlng(
    "33UXP0500444996"),
  structure(
    list(
      mgrs = "33UXP0500444996",
      lat = 48.2494747750754,
      lng = 16.4144942785798),
    .Names = c("mgrs", "lat", "lng"),
    row.names = c(NA, -1L),
    class = "data.frame")
)

expect_equal(
  latlng_to_mgrs(48.24948, 16.41449), "33UXP0500344996"
)

expect_equal(
  mgrs_to_latlng(c("24XWT783908", "33UXP0500444996")),
  structure(
    list(
      mgrs = c("24XWT783908", "33UXP0500444996"),
      lat = c(83.6273817605432, 48.2494747750754),
      lng = c(-32.6687891809823, 16.4144942785798)),
    .Names = c("mgrs", "lat", "lng"),
    row.names = c(NA, -2L), class = "data.frame")
)

expect_equal(
  latlng_to_mgrs(83.62738, -32.66879), "25XEN0410486507"
)

expect_equal(
  utm_to_mgrs(48, "N", 377299, 1483035), "48PUV7729983035"
)

expect_equal(
  mgrs_to_utm("48PUV7729883034"),
  structure(list(
    mgrs = "48PUV7729883034",
    zone = 48, hemisphere = "N",
    easting = 377298,
    northing = 1483034),
    .Names = c("mgrs", "zone", "hemisphere", "easting", "northing"),
    row.names = c(NA, -1L), class = "data.frame")
)

expect_equal(
  ups_to_mgrs("N", 2426773, 1530125), "ZGC2677330125"
)

expect_equal(
  mgrs_to_ups("ZGC2677330125"),
  structure(list(
    mgrs = "ZGC2677330125",
    hemisphere = "N",
    easting = 2426773,
    northing = 1530125),
    .Names = c("mgrs", "hemisphere",
               "easting",  "northing"),
    row.names = c(NA, -1L), class = "data.frame")
)

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
           "16TBQ64", "13TCH16")
) -> sample_dta

expect_equal(
  ncol(
    mgrs_to_latlng(
      sample_dta$mgrs, include_mgrs_ref = FALSE)),
  2
)

expect_equal(
  ncol(
    mgrs_to_utm("48PUV7729883034", include_mgrs_ref = FALSE)),
  4
)

expect_equal(
  ncol(
    mgrs_to_ups("ZGC2677330125", include_mgrs_ref = FALSE)),
  3
)
