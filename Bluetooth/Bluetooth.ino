/*
 * Author : Hank
 * CoAuthor : Del
 * Instructions:
 * 1) Upload the code
 * 2)Enjoy yourself!
 * 
*/
#define BUTTON    2
#define L298N_ENA 5
#define L298N_ENB 6
#define L298N_IN1 7
#define L298N_IN2 9
#define L298N_IN3 10
#define L298N_IN4 11

int state; //state of the robot, moving, reverse,turn left,turn right etc
int flag = 0;
void setup()
{
  Serial.begin(9600);
  //pinMode(BUTTON, INPUT_PULLUP);   //enable the button at pin 2 (only works for pin 2)
  pinMode(L298N_ENA, OUTPUT);
  pinMode(L298N_ENB, OUTPUT);
  pinMode(L298N_IN1, OUTPUT);
  pinMode(L298N_IN2, OUTPUT);
  pinMode(L298N_IN3, OUTPUT);
  pinMode(L298N_IN4, OUTPUT);
}

/*
Makes the robot move forward with motor driver as the head of direction
*/
void robotForward(int robotSpeed)
{
  analogWrite(L298N_ENA, robotSpeed); //To change speed on one of the motors
  digitalWrite(L298N_IN1, LOW);       //To change direction on one of the motors
  digitalWrite(L298N_IN2, HIGH);      //To change direction on one of the motors as well, IN1 and IN2 are relative to each other

  analogWrite(L298N_ENB, robotSpeed);
  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);
}

void robotReverse(int robotSpeed)
{
  analogWrite(L298N_ENA, robotSpeed);
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);

  analogWrite(L298N_ENB, robotSpeed);
  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, HIGH);
}

void robotTurnLeft(int robotSpeed)
{
  analogWrite(L298N_ENA, robotSpeed);
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, LOW);

  analogWrite(L298N_ENB, robotSpeed);
  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, LOW);
}

void robotTurnRight(int robotSpeed)
{
  analogWrite(L298N_ENA, robotSpeed);
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, HIGH);

  analogWrite(L298N_ENB, robotSpeed);
  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, HIGH);
}

void robotStop()
{
  digitalWrite(L298N_ENA, LOW);
  digitalWrite(L298N_IN1, LOW);
  digitalWrite(L298N_IN2, LOW);

  digitalWrite(L298N_ENB, LOW);
  digitalWrite(L298N_IN3, LOW);
  digitalWrite(L298N_IN4, LOW);
}

void robotBrake()
{
  digitalWrite(L298N_ENA, HIGH);
  digitalWrite(L298N_IN1, HIGH);
  digitalWrite(L298N_IN2, HIGH);

  digitalWrite(L298N_ENB, HIGH);
  digitalWrite(L298N_IN3, HIGH);
  digitalWrite(L298N_IN4, HIGH);
}

void loop()
{

  if(Serial.available()>0){
    state = Serial.read();
    flag = 0;
    if (state == '0'){
      robotForward(100);
      Serial.println("forward");
      delay(100);
      Serial.flush();
      
    }
    else if (state == '1'){
      robotTurnRight(100);
      Serial.println("Right");
      delay(100);
      Serial.flush();
    
      
    }
    else if (state == '2'){
      robotTurnLeft(100); 
      Serial.println("Left");
      delay(100);
      Serial.flush();
      
    }
    else if (state == '3'){
      robotReverse(100);
      Serial.println("reverse");
     delay(100);
     Serial.flush();
    }    
    else{
      robotStop();
      delay(100);
      Serial.flush();
    }
  }
}
