#include <pgmspace.h>

#define SECRET
#define THINGNAME "INSERT-THING_NAME"

const char WIFI_SSID[] = "INSERT_SSID";
const char WIFI_PASSWORD[] = "INSERT_PASSWORD";
const char AWS_IOT_ENDPOINT[] = "INSERT_ENDPOINT";

const char SHADOW_GET[] = "INSERT_SHADOW_TOPIC";
const char SHADOW_GET_ACCEPTED[] = "INSERT_SHADOW_TOPIC";
const char SHADOW_GET_REJECTED[] = "INSERT_SHADOW_TOPIC";
const char SHADOW_UPDATE[] = "INSERT_SHADOW_TOPIC";
const char SHADOW_UPDATE_ACCEPTED[] = "INSERT_SHADOW_TOPIC";
const char SHADOW_UPDATE_REJECTED[] = "INSERT_SHADOW_TOPIC";


// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
INSERT_CERT
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
INSERT_CERT
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
INSERT_CERT
-----END RSA PRIVATE KEY-----
)KEY";
