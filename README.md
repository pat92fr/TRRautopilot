# TRRautopilot
 TRR simulator autopilot

## How to build the project
Open 'TRRautopilot.cbp' with Code::Blocks (20.03) and MinGW. 
See http://www.codeblocks.org/downloads/binaries/ (codeblocks-20.03mingw-setup.exe) for download and installation
Dependency : Enet library (http://enet.bespin.org/). Precompiled in enet/ directory of the project

## How to use
1) Launch TRRsim.exe,
 Note : TRR simulator (server) requires local network access (port:1234).
2) launch TRRautopilot.exe.
 Note : TRR autopilot (client) will try to connect to localhost IP and port 1234.
3) TRRsim will display "Autopilot OK" on top of the screen
4) Start autopilot by hitting F3 key in TRRsim. Suspend by hitting F4. Restrart by F2.

## How to create your own autopilot (C/C++ coding)
* open main.cpp
* create a new Crobot_autopilot class
* put your algorithms in the update member function
* pass an instance of your own autopilot class into client constructor (see main()).

## Autopilot data inputs (sensors)
* Time
* Distance measured by virtual LIDARs (zero if obstacle distance is too far > 6m)
* Actual velocity
* Joystick direction and throttle setpoints
```
struct Cautopilot_inut_sensors
{
    unsigned int command = 0;
    unsigned int time_ms = 0;
    float lidar_left_distance_mm = 0.0f;
    float lidar_right_distance_mm = 0.0f;
    float lidar_front_distance_mm = 0.0f;
    float lidar_top_distance_mm = 0.0f;
    float velocity_mms = 0.0f;
    float manual_direction = 0.0f;
    float manual_throttle = 0.0f;
};
```

## Autopilot data outputs (setpoints)
* Direction and throttle setpoints in the range [-1.0..1.0].

```
struct Cautopilot_output_commands
{
    float direction = 0.0f;
    float throttle = 0.0f;
};
```
