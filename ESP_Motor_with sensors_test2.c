#include <TaskScheduler.h> // for scheduling tasks

// create the Scheduler that will be in charge of managing the tasks
Scheduler runner;

void front_sensor_distance_check();
void back_sensor_distance_check();
void motor_run();

Task front_sensor_distance_check_task(20, TASK_FOREVER, &front_sensor_distance_check, &runner, true);  //to read front sensor distance
Task back_sensor_distance_check_task(25, TASK_FOREVER, &back_sensor_distance_check, &runner, true);   //to read back sensor distance
Task motor_run_task(100, TASK_FOREVER, &motor_run, &runner, true); // to run both the motors

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

//speed variable
int motor_speed = 0; //0 = 0 speed and 255 = max speed

//sensors
long duration_front, distance_front;
long duration_back, distance_back;

void setup() {
  // put your setup code here, to run once:
  // We add the task to the task scheduler
  runner.addTask(front_sensor_distance_check_task);
  runner.addTask(back_sensor_distance_check_task);
  runner.addTask(motor_run_task);

   // We activate the task
  front_sensor_distance_check_task.enable();
  back_sensor_distance_check_task.enable();
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

  
}

void loop() {
  // put your main code here, to run repeatedly:
runner.execute(); 
  
}

void front_sensor_distance_check(){
  
  digitalWrite(trigPin_front, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin_front, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin_front, LOW);
  duration_front = pulseIn(echoPin_front, HIGH);
  distance_front = (duration_front/2) / 29.1;

   
    Serial.print ( "Sensor_front  ");
    Serial.print ( distance_front);
    Serial.println("cm");
}


void back_sensor_distance_check(){
  
  digitalWrite(trigPin_back, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin_back, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin_back, LOW);
  duration_back = pulseIn(echoPin_back, HIGH);
  distance_back = (duration_back/2) / 29.1;

   
    Serial.print ( "Sensor_back  ");
    Serial.print ( distance_back);
    Serial.println("cm");
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

