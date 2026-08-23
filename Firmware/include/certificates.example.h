#pragma once

/*
  Public root-CA trust anchor template for SSLClient.

  Copy this file to certificates.h and replace the placeholder below with
  the public root CA required by your MQTT / AWS IoT endpoint.

  This file must contain public CA certificate material only.
  Device certificates, private keys, APN credentials and account-specific
  values belong in secrets.h, which is excluded from Git.
*/

static const char TAs[] PROGMEM = R"CERT(
-----BEGIN CERTIFICATE-----
PUBLIC_ROOT_CA_GOES_HERE
-----END CERTIFICATE-----
)CERT";

static const size_t TAs_NUM = 1;
