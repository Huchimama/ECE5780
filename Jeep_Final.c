#include <TaskScheduler.h> // for scheduling tasks


Scheduler runner;

void front_sensor_distance_check();
void back_sensor_distance_check();

Task front_sensor_distance_check_task(20, TASK_FOREVER, &front_sensor_distance_check, &runner, true);  //to read front sensor distance
Task back_sensor_distance_check_task(25, TASK_FOREVER, &back_sensor_distance_check, &runner, true);   //to read back sensor distance


#define trigPin_front 18
#define echoPin_front 23

#define trigPin_back 19
#define echoPin_back 22

long duration_front, distance_front;
long duration_back, distance_back;

void setup() {
 
  // Add the task to the task scheduler
  runner.addTask(front_sensor_distance_check_task);
  runner.addTask(back_sensor_distance_check_task);

   // Activate the task
  front_sensor_distance_check_task.enable();
  back_sensor_distance_check_task.enable();
  
  Serial.begin (9600);
  pinMode(trigPin_front, OUTPUT);
  pinMode(echoPin_front, INPUT);
  pinMode(trigPin_back, OUTPUT);
  pinMode(echoPin_back, INPUT);
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

   
    Serial.print ( "Sensor_front  ");
    Serial.print ( distance_front);
    Serial.println("cm");
}


void back_sensor_distance_check(){
  
  digitalWrite(trigPin_back, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin_back, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin_back, LOW);
  duration_back = pulseIn(echoPin_back, HIGH);
  distance_back = (duration_back/2) / 29.1;

   
    Serial.print ( "Sensor_back  ");
    Serial.print ( distance_back);
    Serial.println("cm");
}
