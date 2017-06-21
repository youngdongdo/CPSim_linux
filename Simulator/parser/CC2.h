var:2
float accel;
float brake;

input:0

output:0


CAN_input:1
0:0x7FF:2
car_output[TRACK_WIDTH]
car_output[TRACK_DISTANCE]

CAN_output:1
10:0x7FF:2
accel ACCEL
brake BRAKE

code:
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
