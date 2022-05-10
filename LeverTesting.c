#include <TaskScheduler.h> // for scheduling tasks


Scheduler runner;

void front_sensor_distance_check();
void back_sensor_distance_check();
void motor_run();
void lever_check();

Task front_sensor_distance_check_task(20, TASK_FOREVER, &front_sensor_distance_check, &runner, true);  // read front sensor distance
Task back_sensor_distance_check_task(25, TASK_FOREVER, &back_sensor_distance_check, &runner, true);   // read back sensor distance
Task lever_check_task(50, TASK_FOREVER, &lever_check, &runner, true); // run both the motors
Task motor_run_task(100, TASK_FOREVER, &motor_run, &runner, true); // run both the motors

#define trigPin_front 18
#define echoPin_front 23

#define trigPin_back 19
#define echoPin_back 22

// Left Motor (motor 1)
#define motor_left_Pin1 25
#define motor_left_Pin2 26
#define motor_left_enable 27 

// Right Motor (motor 2)
#define motor_right_Pin1 14
#define motor_right_Pin2 12 
#define motor_right_enable 13

//for lever
#define L_minus 5
#define R_minus 17

//speed variable
int motor_speed = 0; //0 = 0 speed and 255 = max speed

//sensors
long duration_front, distance_front;
long duration_back, distance_back;

void setup() {
  // put your setup code here, to run once: // Add the task to the task scheduler
  runner.addTask(front_sensor_distance_check_task);
  runner.addTask(back_sensor_distance_check_task);
  runner.addTask(lever_check_task);
  runner.addTask(motor_run_task);

   // Activate the task
  front_sensor_distance_check_task.enable();
  back_sensor_distance_check_task.enable();
  lever_check_task.enable();
  motor_run_task.enable();
  
  Serial.begin (9600);
  pinMode(trigPin_front, OUTPUT);
  pinMode(echoPin_front, INPUT);
  pinMode(trigPin_back, OUTPUT);
  pinMode(echoPin_back, INPUT);

  // set all the motor control pins to outputs

  pinMode(motor_left_Pin1, OUTPUT);
  pinMode(motor_left_Pin2, OUTPUT);
  pinMode(motor_left_enable, OUTPUT);
  pinMode(motor_right_Pin1, OUTPUT);
  pinMode(motor_right_Pin2, OUTPUT);
  pinMode(motor_right_enable, OUTPUT);
  // Initialize channels 
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  ledcSetup(1, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 12000, 8);
  ledcAttachPin(motor_left_enable, 1); //assign pins to pwm channels
  ledcAttachPin(motor_right_enable, 2);


  //for lever
  pinMode(L_minus, INPUT); 
  pinMode(R_minus, INPUT); 
  
}

void loop() {
  
runner.execute(); 
  
}

void front_sensor_distance_check(){
  
  digitalWrite(trigPin_front, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin_front, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin_front, LOW);
  duration_front = pulseIn(echoPin_front, HIGH);
  distance_front = (duration_front/2) / 29.1;

   
    /*Serial.print ( "Sensor_front  ");
    Serial.print ( distance_front);
    Serial.println("cm");*/
}


void back_sensor_distance_check(){
  
  digitalWrite(trigPin_back, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin_back, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_back, LOW);
  duration_back = pulseIn(echoPin_back, HIGH);
  distance_back = (duration_back/2) / 29.1;

   
  /*  Serial.print ( "Sensor_back  ");
    Serial.print ( distance_back);
    Serial.println("cm");*/
}

void motor_run(){
  digitalWrite(motor_left_Pin1, HIGH);
  digitalWrite(motor_left_Pin2, LOW); 
  digitalWrite(motor_right_Pin1, HIGH);
  digitalWrite(motor_right_Pin2, LOW); 

  ledcWrite(1, motor_speed);
  ledcWrite(2, motor_speed);

  motor_speed += 5;

  if(motor_speed >= 255){
    motor_speed = 0;
  }
}

void lever_check(){
  if( (digitalRead(L_minus) == LOW)){
    //f1 or f2
    if((digitalRead(R_minus) == LOW)){
      //f2
      Serial.println("Forward 2");
    }
    else{
      //f1
      Serial.println("Forward 1");
    }
  }
  else if((digitalRead(L_minus) == HIGH)){
    //reverse
    Serial.println("Reverse");
  }
}

