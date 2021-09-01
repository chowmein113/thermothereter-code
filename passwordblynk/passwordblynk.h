#pragma once

struct passwordblynk
{
const char* ssid= "dog2";

const char* pass = "Podrey321!";

const char* getssid() {return ssid;}
const char* getpass() { return pass;}
void setssid(const char* ss) {
	ssid = ss;
}
void setpass(const char* ps) {
	pass = ps;
}
};