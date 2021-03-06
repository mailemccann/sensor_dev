/*
 * THIS CODE IS FOR AGUACLARA SENSOR_DEV
 * This code's function is to take the input voltage from the turbidity sensor
 * and translate it into a numerical value for turbidity
 */

int ledPin = 13;  //declaration for LED
int button_input = 11;   //digital input of the pushbutton
int offset = 0;  //set the offset as zero for now
int turb_input = A0; //input in A0 from sensor
int flag = 0; //if flag is 1, start loop

void setup() {
  //SETUP
  Serial.begin(9600); //Baud rate: 9600 
  pinMode(ledPin, OUTPUT);  //This is to set up the LED
  pinMode(turb_input, INPUT);  //This is to set up the turbidity input from sensor
  pinMode(button_input, INPUT);  //This is to set up the input from pushbutton

  //CALIBRATION   
  //set up so that the difference between the clear water turbidity
  //and the usual 0 turbidity value and set this as the constant offset 
  //as Hannah pointed out, this will also take care of the temp difference
  //(this will be used in the conversion)
  
  Serial.println("Please calibrate the sensor by pressing the button");  //clear water calibration
  
  //PUSHBUTTON
  //set it up with a push button
  if (digitalRead(button_input)==LOW){ //don't remember if pushbutton high or low when pressed
    flag = 0;
  }
  else if(digitalRead(button_input) == HIGH){
    flag = 1;
    offset = analogRead(turb_input);
    Serial.println("this is the offset value");
    Serial.print(offset);
  }
  }


void loop() {

  if (flag == 1){
    int sensorValue = analogRead(A0);// read the input on A0:

    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage = sensorValue * (5.0 / 1024.0); 
    Serial.println("____________________________________");
    Serial.println("this is the voltage reading:");
    Serial.print(voltage); // print out the value you read:
  

    // Convert voltage to turbidity
    // relation from page is -1120.4x^2 +5742.3x-4352.9
    float turbidity = ((voltage*voltage)*(-1120.4))+(voltage*5742.3)-4352.9-(offset);
 
    Serial.println("this is the turbidity reading:");
    Serial.print(turbidity); // print out the value you read:

    delay(500);
  
    //threshold value to compare to light up LED
    //later add breadboard stuff with display
  }
}
