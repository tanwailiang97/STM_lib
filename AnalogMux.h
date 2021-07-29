#ifndef _RTR_ANALOGMUX_H_
#define _RTR_ANALOGMUX_H_

class Mux{

public:
	Mux(uint8 S0,uint8 S1,uint8 S2,uint8 muxInput);

	bool dRead(uint8 Pin);

	uint16 aRead(uint8 Pin);

private:
	uint8 pinOutS0;
	uint8 pinOutS1;
	uint8 pinOutS2;
	uint8 pinInMux;
};

Mux::Mux(uint8 S0,uint8 S1,uint8 S2,uint8 muxInput){
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(muxInput, INPUT_PULLUP);
	pinOutS0 = S0;
	pinOutS1 = S1;
	pinOutS2 = S2;
	pinInMux = muxInput;
}

bool Mux::dRead(uint8 Pin){
	digitalWrite(pinOutS0,Pin&1);
	digitalWrite(pinOutS1,Pin&2);
	digitalWrite(pinOutS2,Pin&4);
	delay(1);
	return digitalRead(pinInMux);
}

uint16 Mux::aRead(uint8 Pin){
	digitalWrite(pinOutS0,Pin&1);
	digitalWrite(pinOutS1,Pin&2);
	digitalWrite(pinOutS2,Pin&4);
	return analogRead(pinInMux);
}

Mux MUX(PA10,PB9,PB8,PB1);


#endif