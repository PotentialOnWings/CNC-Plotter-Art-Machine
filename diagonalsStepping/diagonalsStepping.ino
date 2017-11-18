#include <Stepper.h>
#include <Servo.h>
#include <stdbool.h>
#include <stdio.h>

const int stepsPerRevolution = 20; 
Servo penServo;//initiates servo
int servoPin = 6;//pin servo is connected to

Stepper xAxis(stepsPerRevolution, 2,3,10,11); //pins x axis motor are connected to
Stepper yAxis(stepsPerRevolution, 4,5,8,9); //pins y axis motor are connected to

bool draw = true;

int xstep;
int ystep;
int xold;
int yold;
int altXRatio; //how often it alternates between x and y
int altYRatio;
 
int penLiftThreshold;

void setup()
{
	penServo.attach(servoPin);//attach servo to arduino
  
}
 
void loop() 
{
	xAxis.setSpeed(100);
	yAxis.setSpeed(100);
	//max 250 steps for dvd/cd stepper motors 
 
	while (draw == true){
		penServo.write(0);//pulls pen down      
		delay(5000); //pause for 5 seconds
    
		for (int i = 0; i < numlines; i++){
      xstep = coords[i][0] - xold;
      ystep = coords[i][1] - yold;
      if (xstep > 5 || ystep > 5){ //too far, make new line
        penUp();
        altYRatio = ystep/xstep;
        makeLoop(xstep, altYRatio);
        penDown();
      } else if (xstep > 0){ //close enough, it's a line, draw
        altYRatio = ystep/xstep;
        makeLoop(xstep, altYRatio);
      } else { //x is 0, can't divide by 
        makeLoop(1, ystep);
      }
		}
		
		penServo.write(70); //pulls pen up      
		delay(5000); //pause for 5 seconds
		
		draw = false;
	}
	
}



void makeLoop(int n, int altYStep){
  for (int i = 0; i < n; i++){
    xAxis.step(1);
    delay(1);
    yAxis.step(altYStep);
    delay(1);
  }
}



void penUp()
{
  penServo.write(70);//pulls pen up 
  delay(3000); //pause for 3 seconds
}


void penDown()
{
  penServo.write(0);//pulls pen up
  delay(3000); //pause for 3 seconds 
}