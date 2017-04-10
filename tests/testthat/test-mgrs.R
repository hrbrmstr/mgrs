context("basic functionality")
test_that("we can do something", {

  expect_equal(mgrs_to_latlng("33UXP04"),
               structure(c(48.2053484084679, 16.3459269599006),
                         .Names = c("lat", "lng")))

  expect_equal(latlng_to_mgrs(48.20535, 16.34593), "33UXP0000040000")

  expect_equal(mgrs_to_latlng("33UXP0500444996"),
               structure(c(48.2494747750754, 16.4144942785798),
                         .Names = c("lat", "lng")))

  expect_equal(latlng_to_mgrs(48.24948, 16.41449), "33UXP0500344996")

  expect_equal(mgrs_to_latlng("24XWT783908"),
               structure(c(83.6273817605432, -32.6687891809823),
                         .Names = c("lat", "lng")))

  expect_equal(latlng_to_mgrs(83.62738, -32.66879), "25XEN0410486507")

  expect_equal(utm_to_mgrs(48, "N", 377299, 1483035), "48PUV7729983035")

  expect_equal(mgrs_to_utm("48PUV7729883034"),
               structure(list(mgrs = "48PUV7729883034", zone = 48, hemisphere = "N",
                              easting = 377298, northing = 1483034),
                         .Names = c("mgrs", "zone", "hemisphere", "easting", "northing"),
                         row.names = c(NA,
                                                                                                                                            -1L), class = "data.frame"))

  expect_equal(ups_to_mgrs("N", 2426773, 1530125), "ZGC2677330125")

  expect_equal(mgrs_to_ups("ZGC2677330125"),
               structure(list(mgrs = "ZGC2677330125", hemisphere = "N", easting = 2426773,
                              northing = 1530125), .Names = c("mgrs", "hemisphere",
                                                              "easting",  "northing"),
                         row.names = c(NA, -1L), class = "data.frame"))

})
