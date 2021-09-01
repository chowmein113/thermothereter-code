#pragma once

struct passwordblynk
{
const char* ssid= "";

const char* pass = "";

const char* getssid() {return ssid;}
const char* getpass() { return pass;}
void setssid(const char* ss) {
	ssid = ss;
}
void setpass(const char* ps) {
	pass = ps;
}
};
