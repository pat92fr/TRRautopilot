#include <iostream>
#include <algorithm>

#include "client.h"

struct Cautopilot_example : Cautopilot
{
    void update(Cautopilot_inut_sensors const & in, Cautopilot_output_commands & out)
    {
        // server request autopilot RESET
        if(in.command==1<<0)
        {

        }

        // compute actual position
        float position_estimation = 0.0f;
        if(in.lidar_left_distance_mm==0.0f)
            position_estimation = in.lidar_right_distance_mm - 6000.0f;
        else if(in.lidar_right_distance_mm==0.0f)
            position_estimation = 6000.0f - in.lidar_left_distance_mm;
        else if(in.lidar_left_distance_mm>0.0f && in.lidar_right_distance_mm>0.0f)
           position_estimation = in.lidar_right_distance_mm-in.lidar_left_distance_mm;

        // compute direction setpoint
        float const position_setpoint = 0.0f;
        float const position_kp = 0.001f;
        float const position_error = position_setpoint - position_estimation;
        float const direction_pid_output = -position_kp*position_error; // reverse DIR
        out.direction = std::clamp(direction_pid_output,-1.0f,1.0f);

        // compute throttle setpoint
        float const velocity_setpoint = 2600.0f; // mm/s
        float const velocity_kp = 0.002f;
        float const velocity_error = velocity_setpoint - in.velocity_mms;
        float const velocity_pid_output = velocity_kp*velocity_error;
        out.throttle = std::clamp(velocity_pid_output,-1.0f,1.0f);
    }
};

int main()
{
    // create an autopilot
    Cautopilot_example autopilot;
    // create a client and pass IP address "x.x.x.x", port number and the autopilot
    Cclient client("127.0.0.1",1234,autopilot);
    // run !
    client.run();
    return 0;
}
