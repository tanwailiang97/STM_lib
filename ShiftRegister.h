#ifndef _RTR_SHIFT_REGISTER_H_
#define _RTR_SHIFT_REGISTER_H_

class ShiftRegister{
public:
	/**
	 * @brief Construst a new Shift Register instance
	 * @param 	STCP:storage register clock input, SHCP: shift register clock input
	 *			DS: serial data input
	 */
	ShiftRegister(uint8 STCP,uint8 SHCP,uint8 DS);

	void dWriteAll(uint8 * Data);
	void dWrite(uint8 Pin_0, bool Value_0);
	void dWrite(uint8 Pin_0, bool Value_0, uint8 Pin_1, bool Value_1);
	void dWrite(uint8 Pin_0, bool Value_0, uint8 Pin_1, bool Value_1, uint8 Pin_2, bool Value_2);
	void dWrite(uint8 Pin_0, bool Value_0, uint8 Pin_1, bool Value_1, uint8 Pin_2, bool Value_2, 
			uint8 Pin_3, bool Value_3);
	void dWrite(uint8 Pin_0, bool Value_0, uint8 Pin_1, bool Value_1, uint8 Pin_2, bool Value_2, 
			uint8 Pin_3, bool Value_3, uint8 Pin_4, bool Value_4);
	void dWrite(uint8 Pin_0, bool Value_0, uint8 Pin_1, bool Value_1, uint8 Pin_2, bool Value_2, 
			uint8 Pin_3, bool Value_3, uint8 Pin_4, bool Value_4, uint8 Pin_5, bool Value_5);
	

private:
	uint8 SR_STCP;
	uint8 SR_SHCP;
	uint8 SR_DS;
	bool SR_Data[8];

	void sRWrite(bool * Data);

};

ShiftRegister::ShiftRegister(uint8 ST_Pin,uint8 SH_Pin,uint8 DS_Pin){
	pinMode(ST_Pin, OUTPUT);
	pinMode(SH_Pin, OUTPUT);
	pinMode(DS_Pin, OUTPUT);
	SR_STCP = ST_Pin;
	SR_SHCP = SH_Pin;
	SR_DS = DS_Pin;
	digitalWrite(ST_Pin, LOW);
	digitalWrite(SH_Pin, LOW);
	digitalWrite(DS_Pin, LOW);
}

void ShiftRegister::sRWrite(bool * Data){
	digitalWrite(SR_STCP,LOW);
	for(int i=0;i<8;i++){
		digitalWrite(SR_SHCP,LOW);
		digitalWrite(SR_DS,Data[i]);
		digitalWrite(SR_SHCP,HIGH);
		delay(2);
	}
	digitalWrite(SR_STCP,HIGH);
}

void ShiftRegister::dWriteAll(uint8 Data[8]){
	digitalWrite(SR_STCP,LOW);
	for(int i=0;i<8;i++){
		digitalWrite(SR_SHCP,LOW);
		if(Data[i]<2) digitalWrite(SR_DS,Data[i]);
		digitalWrite(SR_SHCP,HIGH);
		delay(2);
	}
	digitalWrite(SR_STCP,HIGH);
}

void ShiftRegister::dWrite(uint8 Pin_0, bool Value_0){
	SR_Data[Pin_0] = Value_0;
	sRWrite(SR_Data);
} 

void ShiftRegister::dWrite(uint8 Pin_0, bool Value_0, uint8 Pin_1, bool Value_1){
	SR_Data[Pin_0] = Value_0;
	SR_Data[Pin_1] = Value_1;
	sRWrite(SR_Data);
}


void ShiftRegister::dWrite(uint8 Pin_0, bool Value_0, uint8 Pin_1, bool Value_1, uint8 Pin_2, bool Value_2){
	SR_Data[Pin_0] = Value_0;
	SR_Data[Pin_1] = Value_1;
	SR_Data[Pin_2] = Value_2;
	sRWrite(SR_Data);
}

void ShiftRegister::dWrite(uint8 Pin_0, bool Value_0, uint8 Pin_1, bool Value_1, uint8 Pin_2, bool Value_2, 
			uint8 Pin_3, bool Value_3){
	SR_Data[Pin_0] = Value_0;
	SR_Data[Pin_1] = Value_1;
	SR_Data[Pin_2] = Value_2;
	SR_Data[Pin_3] = Value_3;
	sRWrite(SR_Data);
}

void ShiftRegister::dWrite(uint8 Pin_0, bool Value_0, uint8 Pin_1, bool Value_1, uint8 Pin_2, bool Value_2, 
			uint8 Pin_3, bool Value_3, uint8 Pin_4, bool Value_4){
	SR_Data[Pin_0] = Value_0;
	SR_Data[Pin_1] = Value_1;
	SR_Data[Pin_2] = Value_2;
	SR_Data[Pin_3] = Value_3;
	SR_Data[Pin_4] = Value_4;
	sRWrite(SR_Data);
}

void ShiftRegister::dWrite(uint8 Pin_0, bool Value_0, uint8 Pin_1, bool Value_1, uint8 Pin_2, bool Value_2, 
			uint8 Pin_3, bool Value_3, uint8 Pin_4, bool Value_4, uint8 Pin_5, bool Value_5){
	SR_Data[Pin_0] = Value_0;
	SR_Data[Pin_1] = Value_1;
	SR_Data[Pin_2] = Value_2;
	SR_Data[Pin_3] = Value_3;
	SR_Data[Pin_4] = Value_4;
	SR_Data[Pin_5] = Value_5;
	sRWrite(SR_Data);
}

ShiftRegister SR(PB3,PA15,PB4);

#endif
