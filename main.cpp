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
        if(in.lidar_cm[0]==0.0f)
            position_estimation = in.lidar_cm[1] - 600.0f;
        else if(in.lidar_cm[1]==0.0f)
            position_estimation = 600.0f - in.lidar_cm[0];
        else if(in.lidar_cm[0]>0.0f && in.lidar_cm[1]>0.0f)
           position_estimation = in.lidar_cm[1]-in.lidar_cm[0];

        // compute direction setpoint
        float const position_setpoint = 0.0f;
        float const position_kp = 0.01f;
        float const position_error = position_setpoint - position_estimation;
        float const direction_pid_output = -position_kp*position_error; // reverse DIR
        out.direction = std::clamp(direction_pid_output,-1.0f,1.0f);

        // compute throttle setpoint
        float const velocity_setpoint = 2.6f; // m/s
        float const velocity_kp = 2.0f;
        float const velocity_error = velocity_setpoint - in.velocity_mps;
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
