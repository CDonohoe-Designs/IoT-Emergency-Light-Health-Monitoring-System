#pragma once

/*
  Copy this file to secrets.h and fill in your own values.

  I keep these values out of Git because they are specific to the
  mobile network and AWS IoT account used by the device.
*/

const char APN[] = "my_apn";
const char APN_USER[] = "";
const char APN_PASSWORD[] = "";

const char AWS_IOT_ENDPOINT[] = "my-endpoint-ats.iot.region.amazonaws.com";

static const char AWS_DEVICE_CERT[] PROGMEM = R"CERT(
-----BEGIN CERTIFICATE-----
THE_CERTIFICATE_GOES_HERE
-----END CERTIFICATE-----
)CERT";

static const char AWS_PRIVATE_KEY[] PROGMEM = R"KEY(
-----BEGIN PRIVATE KEY-----
THE_PRIVATE_KEY_GOES_HERE
-----END PRIVATE KEY-----
)KEY";
