#ifndef _RTR_MOTOR_H_
#define _RTR_MOTOR_H_

class Motor{
public:
	/**
	 * @brief Construst a new Motor instance
	 * @param 	PWM:pwm input, DIR1/DIR2: direction Control
	 *			CURR: current input
	 */
	Motor(uint8 pwmPin,uint8 dir1Pin,uint8 dir2Pin,uint8 currPin);
	/**
	 * @brief Construst a new Motor instance
	 * @param 	pwm:pwm input, 0 to 65535
	 *			direction: 0 or 1
	 */
	void setVoltage(int pwm, bool direction);
	/**
	 * @brief Construst a new Motor instance
	 * @param 	pwm:pwm input, 0 to 65535
	 *			direction: 0 or 1
	 */
	void setVelocity(float velocity);
	/**
	 * @brief Construst a new Motor instance
	 * @param 	pwm:pwm input, 0 to 65535
	 *			direction: 0 or 1
	 */
	float getCurrent();
	/* max RPM of the motor*/
	int maxRpm;
	/* relative radius of motor in mm*/
	float radius;

private:
	uint8 PWM;
	uint8 DIR1;
	uint8 DIR2;
	uint8 CURR;
};

Motor::Motor(uint8 pwmPin,uint8 dir1Pin,uint8 dir2Pin,uint8 currPin){
	PWM = pwmPin;
	DIR1 = dir1Pin;
	DIR2 = dir2Pin;
	CURR = currPin;
}

void Motor::setVoltage(int pwm, bool direction){
	SR.dWrite(DIR1,direction,DIR2,!direction);
	if(pwm > 255) pwm=255;
	else if(pwm < 0) pwm = 0;
	analogWrite(PWM,pwm);
}

void Motor::setVelocity(float velocity){
	float rpm = velocity * 60 / PI / 2 / radius;
	int out = (rpm / maxRpm * 65535) + 0.5;
	if(out > 0) SR.dWrite(DIR1,1,DIR2,0);
	else SR.dWrite(DIR1,0,DIR2,1);
	if(abs(out) > 65535) out = 65535;
	pwmWrite(PWM,abs(out));
}

float Motor::getCurrent(){ // Iout/Isense = 800, 3.3V, 4095 resolution, 1k resistor
	return 800*analogRead(CURR)*3.3/1000/4095;
}


Motor MOTOR1(PWM_M1,DIR_M1A,DIR_M1B,CURR_M1);
Motor MOTOR2(PWM_M2,DIR_M2A,DIR_M2B,CURR_M2);
Motor MOTOR3(PWM_M3,DIR_M3A,DIR_M3B,CURR_M3);

#endif