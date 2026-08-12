# certificates.h

The firmware expects an `include/certificates.h` file containing the public root CA trust anchors required by SSLClient.

In the original project I generated this from the Amazon Root CA used by AWS IoT.

This file should contain public CA information only. Device certificates, private keys and account-specific credentials belong in `secrets.h`, which is excluded from Git.
