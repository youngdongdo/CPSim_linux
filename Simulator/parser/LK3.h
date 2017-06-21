var:1
float steering;

input:0

output:0

CAN_input:0

CAN_output:1
10:0x7FE:1
steering STEER

code:
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
