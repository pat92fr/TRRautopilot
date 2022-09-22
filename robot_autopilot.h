/*
 * Copyright 2022 Patrick DUPUTZ
 *
 * This file is part of TRRsim.
 *
 * TRRsim is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or any later version.
 *
 * TRRsim is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * TRRsim. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef ROBOT_AUTOPILOT_H_INCLUDED
#define ROBOT_AUTOPILOT_H_INCLUDED

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

struct Cautopilot_output_commands
{
    float direction = 0.0f;
    float throttle = 0.0f;
};

struct Cautopilot
{
    virtual void update(Cautopilot_inut_sensors const & in, Cautopilot_output_commands & out) = 0;
};

#endif // ROBOT_AUTOPILOT_H_INCLUDED
