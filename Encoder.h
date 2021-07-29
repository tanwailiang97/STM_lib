#ifndef _RTR_ENCODER_H_
#define _RTR_ENCODER_H_

#include <HardwareTimer.h>

class Encoder{

public: 
  /**
   * @brief Construst a new Encoder instance
   * @param encoderNum number of encoder interface (1 to 4 for STM32F103C8T6)
   */
	Encoder(uint8 encoderNum);
  /**
   * @brief Initialize the encoder, put inside void setup()
   * @param dir direction of encoder counting (0 or 1)
   */
  void init(bool dir);
  /**
   * @brief get reading of the encoder
   * @return encoder count (-2^32 to +2^32-1)
   */
  signed long int getReading(void);
  /**
   * @brief get rpm of the encoder
   */
  float getRpm(void);
  /**
   * @brief swap the direction of encoder reading
   * 
   */
  void chgDir(void);

  static int flowCount[4];
  float gearRatio = 1;
  int ppr = 1;

private:
  unsigned long prevTime;
  signed long int prevEncoderValue;
  uint8 m_encoderNum;
  uint8 m_dir;
  HardwareTimer timer;
  static void encoderInterrupt1(){flowCount[0]=Timer1.getCount()>32768?flowCount[0]-1:flowCount[0]+1;}
  static void encoderInterrupt2(){flowCount[1]=Timer2.getCount()>32768?flowCount[1]-1:flowCount[1]+1;}
  static void encoderInterrupt3(){flowCount[2]=Timer3.getCount()>32768?flowCount[2]-1:flowCount[2]+1;}
  static void encoderInterrupt4(){flowCount[3]=Timer4.getCount()>32768?flowCount[3]-1:flowCount[3]+1;}

  void interrupt(uint8 encoderNum);
  
};



void Encoder::interrupt(uint8 encoderNum){
  if(encoderNum == 1)timer.attachInterrupt(0,encoderInterrupt1);
  else if(encoderNum == 2)timer.attachInterrupt(0,encoderInterrupt2);
  else if(encoderNum == 3)timer.attachInterrupt(0,encoderInterrupt3);
  else if(encoderNum == 4)timer.attachInterrupt(0,encoderInterrupt4);
}


Encoder::Encoder(uint8 encoderNum):timer(encoderNum)
{
  m_encoderNum = encoderNum;
}

void Encoder::init(bool dir){
  m_dir = dir;
  timer.pause();
  timer.setMode(m_encoderNum,TIMER_ENCODER);
  timer.setEdgeCounting(3);
  timer.setPolarity(1,m_dir);
  timer.setPolarity(2,0);
  interrupt(m_encoderNum);
  timer.refresh();  
  timer.resume();
  delay(50);
  flowCount[m_encoderNum-1] = 0;
}

signed long int Encoder::getReading(){
  return (flowCount[m_encoderNum-1]<<16 | timer.getCount());
}

float Encoder::getRpm(){
  unsigned long  time = micros() - prevTime;
  prevTime = micros();
  float pulse = ((flowCount[m_encoderNum-1]<<16 | timer.getCount()) 
    - prevEncoderValue)/gearRatio/ppr;
  prevEncoderValue = flowCount[m_encoderNum-1]<<16 | timer.getCount();
  return pulse * 60 * 1000 * 1000 / time;
}

void Encoder::chgDir(){
  int count = flowCount[m_encoderNum-1];
  m_dir = !m_dir;
  timer.pause();
  timer.setPolarity(1,m_dir);
  timer.setPolarity(2,0); 
  timer.resume();
  flowCount[m_encoderNum-1] = count;
}

int Encoder::flowCount[4];

Encoder ENC1(1);
Encoder ENC2(2);
Encoder ENC3(3);
Encoder ENC4(4);

#endif
