# TRRautopilot
 TRR simulator autopilot
 
[![IMAGE ALT TEXT](http://img.youtube.com/vi/Oe0HFSuLpZk/0.jpg)](http://www.youtube.com/watch?v=Oe0HFSuLpZk "TRRsim")

## How to build the project
Open 'TRRautopilot.cbp' with Code::Blocks (20.03) and MinGW. 
See http://www.codeblocks.org/downloads/binaries/ (codeblocks-20.03mingw-setup.exe) for download and installation
Dependency : Enet library (http://enet.bespin.org/). Precompiled in enet/ directory of the project

## How to use
1) Launch TRRsim.exe,
 Note : TRR simulator (server) requires local network access (port:1234).
2) TRR simulator displays "Waiting for autopilot..."
3) launch TRRautopilot.exe.
 Note : TRR autopilot (client) will try to connect to localhost IP and port 1234.
4) TRRsim will display "Autopilot connected" on top of the screen
5) Start autopilot by hitting F3 key in TRRsim. Hit F4 to suspend, F2 to restrart. and F1 for help.

TRR simulator (process) doesn't need to be restarted when TRR autopilot (process) has to be stopped, recompiled and restarted (algorithm changes).

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
    unsigned int time_ms = 0;                 // Current time in ms
    float lidar_left_distance_mm = 0.0f;      // 0: no obstacle in range, >0 distance in mm
    float lidar_right_distance_mm = 0.0f;     // 0: no obstacle in range, >0 distance in mm
    float lidar_front_distance_mm = 0.0f;     // 0: no obstacle in range, >0 distance in mm
    float lidar_top_distance_mm = 0.0f;       // 0: no obstacle in range, >0 distance in mm
    float velocity_mps = 0.0f;                // Meter per second
    float angular_velocity_dps = 0.0f;        // Degrees per second (trigonometric)
    float manual_direction = 0.0f;            // -1.0 MAX LEFT   +1.0 MAX RIGHT
    float manual_throttle = 0.0f;             // -1.0 MAX BRAKE  +1.0 MAX THROTTLE
};
```

## Autopilot data outputs (setpoints)
* Direction and throttle setpoints in the range [-1.0..1.0].

```
struct Cautopilot_output_commands
{
    float direction = 0.0f;        // -1.0 MAX LEFT   +1.0 MAX RIGHT
    float throttle = 0.0f;         // -1.0 MAX BRAKE  +1.0 MAX THROTTLE
};
```
