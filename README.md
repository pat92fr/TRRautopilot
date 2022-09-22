# TRRautopilot
 TRR simulator autopilot

## How to build the project
Open 'TRRautopilot.cbp' with Code::Blocks (20.03) and MinGW. See for http://www.codeblocks.org/downloads/binaries/ (codeblocks-20.03mingw-setup.exe) installation
Dependency : Enet (http://enet.bespin.org/). Precompiled in enet directory of the project

## How to use
1) Launch TRRsim.exe,
2) launch TRRautopilot.exe.
3) Start autopilot by hitting F3 key in TRRsim.

## How to create your own autopilot
* open main.cpp
* create a new Crobot_autopilot class
* put your algorithms in the update member function
* pass an instance of your own autopilot class into client constructor (see main()).

## Autopilot inputs

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


## Autopilot outputs
* Direction and throttle setpoints = [-1.0..1.0]

```
struct Cautopilot_output_commands
{
    float direction = 0.0f;
    float throttle = 0.0f;
};
```
