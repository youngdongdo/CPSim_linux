#include "task_created.hh"
#include "can_api.h"
#include "data_list.hh"

extern list<CAN_Msg *> waiting_data;

// Task0 (CC1)
Task0::Task0(Task_info *task_info):Task(task_info)
{
}

Task0::~Task0()
{
}

void Task0::write()
{
	for(unsigned int i = 0; i < successors.size(); i++)
	{
		successors[i]->internal_data[0] = internal_data[0];
	}
}

void Task0::procedure()
{
	internal_data[0] = car_output[SPEED];
}


// Task1 (LK1)
Task1::Task1(Task_info *task_info):Task(task_info)
{
}

Task1::~Task1()
{
}

void Task1::write()
{
	for(unsigned int i = 0; i < successors.size(); i++)
	{
		successors[i]->internal_data[0] = internal_data[0];
		successors[i]->internal_data[1] = internal_data[1];
	}
}

void Task1::procedure()
{
	internal_data[0] = car_output[TRACK_WIDTH];
	internal_data[1] = car_output[DISTANCE];
}


// Task2 (CC2)
Task2::Task2(Task_info *task_info):Task(task_info)
{
}

Task2::~Task2()
{
}

void Task2::write()
{
	;

	// can send
	CAN_Msg *can_msg = new CAN_Msg(completion_time, 1, 0x7FF, 2, ACCEL, BRAKE, accel, brake, this->task_link->get_task_name());
	insert_can_msg(&waiting_data, can_msg);
}

void Task2::procedure()
{


	float speed = internal_data[0];
	float dist = car_output[DISTANCE];



	dist = fabs(dist);
	brake = 0.0;

	if (dist >= 2.5){
		accel = 1.0;
	}
	else if(dist >= 1.5){
		if(speed > 10.0)
			brake = 0.15;
		else
			accel = 0.4;
	}
	else if (speed > 10.0){
		brake = 0.01;
		accel = 0.0;
	}
	else if (speed < 2.0 )
		accel = 0.1;
	else if (speed < 5.0 )
		accel = 0.1;
	else if(speed < 6.0){
	    brake = 0.005;
	    accel = 0.0;
	}
	else {
		brake = 0.003;
		accel = 0.0;
	}


}


// Task3 (LK2)
Task3::Task3(Task_info *task_info):Task(task_info)
{
}

Task3::~Task3()
{
}

void Task3::write()
{
	for(unsigned int i = 0; i < successors.size(); i++)
	{
		successors[i]->internal_data[2] = internal_data[2];
		successors[i]->internal_data[3] = internal_data[3];
	}
}

void Task3::procedure()
{
	internal_data[2] = car_output[TRACK_ANGLE];
	internal_data[3] = car_output[YAW];
}


// Task4 (other1)
Task4::Task4(Task_info *task_info):Task(task_info)
{
}

Task4::~Task4()
{
}

void Task4::write()
{
	;
}

void Task4::procedure()
{
	;
}


// Task5 (other2)
Task5::Task5(Task_info *task_info):Task(task_info)
{
}

Task5::~Task5()
{
}

void Task5::write()
{
	;
}

void Task5::procedure()
{
	;
}


// Task6 (other3)
Task6::Task6(Task_info *task_info):Task(task_info)
{
}

Task6::~Task6()
{
}

void Task6::write()
{
	;
}

void Task6::procedure()
{
	;
}


// Task7 (LK3)
Task7::Task7(Task_info *task_info):Task(task_info)
{
}

Task7::~Task7()
{
}

void Task7::write()
{
	;

	// can send
	CAN_Msg *can_msg = new CAN_Msg(completion_time, 1, 0x7FE, 1, STEER, STEER, steering, steering, this->task_link->get_task_name());
	insert_can_msg(&waiting_data, can_msg);
}

void Task7::procedure()
{




	// sensor data
	float track_width = internal_data[0];
	float distance = internal_data[1];
	float track_angle = internal_data[2];
	float yaw = internal_data[3];

	// get difference of angle
	float angle = track_angle - yaw;
	float pi = 3.141592;
	while(angle > pi)
	    angle -= 2*pi;
	while(angle < -pi)
	    angle += 2*pi;

	// calculate steering value
	float SC = 7.0;
	float curve_SC = 3.0;
	float curve = 0.05;
	float weight_dist = 6.875;
	float close_weight_dist = 9.0;

	if(track_width == 0.0)
		steering = 0.0;
	else  if ( -0.02 < distance && distance < 0.02 )
		{

			if(-0.01 < distance && distance < 0.01)
				steering = (1.0 + 200.0*fabs(distance))*((10.0 - weight_dist)*angle - weight_dist*distance/track_width);
			else
				steering = curve_SC*((10.0 - weight_dist)*angle - weight_dist*distance/track_width);

		}
	else
		steering = SC*(angle - 5.0*distance/track_width);



}


