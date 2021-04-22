# Control deej via Wi-Fi with an ESP32

A basic project to control [my fork of deej](https://github.com/iamjackg/deej) via UDP using an ESP32 microcontroller.

## Getting started

1. Install [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation.html)
1. Clone this repository
1. Change `upload_port` in [`platformio.ini`](platformio.ini) to point to where your ESP32 is connected
1. Change the `board` to whatever model you have
1. In the `src` folder, copy [`configuration.h.sample`](src/configuration.h.sample) to `configuration.h`
1. Fill in the details in `configuration.h`
    * `DEST_IP`: the host where you're running deej
    * `SSID`: the name of your Wi-Fi connection
    * `PASSWORD`: the password for your Wi-Fi connection
    * `HOSTNAME`: the hostname you want the ESP32 to assume on your network. The default value is fine.
1. If you have more or fewer than 5 sliders, change the code in [`src/main.cpp`](src/main.cpp) accordingly
1. In a terminal, run `platformio run`
