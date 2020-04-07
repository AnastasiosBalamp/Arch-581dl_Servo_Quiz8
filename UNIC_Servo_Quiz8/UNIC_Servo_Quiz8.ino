
#include <Servo.h>

Servo servo1; //create servo object

int pot1 = A0; //I add the A to help distinguish Analog pin vs. Digital pin
               //This is where the position potentiometer is connected
               
int pot2 = A1; //I add the A to help distinguish Analog pin vs. Digital pin
               //This is where the speed potentiometer is connected
               
int oldpos=0; //This declares a value in integer form, this will be used as a variable for position data to send to the servo.
               
int map_pot1; //This declares a value in integer form, this will be used to map the servo position to a range
int map_pot2; //This declares a value in integer form, this will be used to map the servo position to a range
int newval;  //This will be used to save a value for the next iteration of a loop


// the setup routine runs once when you press reset:
void setup() {
  
  servo1.attach(9); // attach pin to servo object 
 // initialize serial communication at 115200 bits per second:
  Serial.begin(115200); // * Speacial Note Here * most sketches run on 9600 baud, I found at this baud, less jerky motion was in the servo movement at low speeds

}

// the loop routine runs over and over again forever:
void loop() {
  
  // read the input on analog pin 0 and pin 1:
  map_pot1 = analogRead(pot1); //read pot. 1
  map_pot2 = analogRead(pot2); //read pot. 2

  map_pot1 = map(map_pot1, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 179)
  map_pot2 = map(map_pot2, 0, 1023, 100, 0);     // maps pot. values to 100ms to 0ms when the delay is used.

                 // sets the servo position according to the scaled value
                 
Serial.print("Current Speed ");  // Serieal prints what the speed is set at
Serial.print(map_pot2);
Serial.println("");


if(newval>oldpos){ // If the servo value chnaged since last check do this
  delay(10); // This helps add a buffer for dirty signals
  for(oldpos = servo1.read(); oldpos < newval; oldpos +=1){  // Ok, we're creating a variable that gets the current servo position. Then we are going to move the different to the new value, one degree at a time dictated by the += 1
  servo1.write(oldpos); // Move one degree towards the new pot. value
  delay(map_pot2); // delayed before going to the next degree, this delay is mapped to the second trim. pot.
  //
  Serial.println(""); // Just some user feedback in the serial terminal
  Serial.print("Moving to: ");
  Serial.print(newval);
  Serial.print(" Currently at ");
  Serial.print(oldpos);
  //
  }
}

if(newval<oldpos){  // Same as above, but if the new value is less than the old, it reverses whats above.
  delay(10);
  for(oldpos =servo1.read(); oldpos > newval; oldpos -=1){
  servo1.write(oldpos);
  delay(map_pot2);
  //
  Serial.println("");
  Serial.print("Moving to: ");
  Serial.print(newval);
  Serial.print(" Currently at ");
  Serial.print(oldpos);
  //
  }
}else{
     Serial.println("\n Nothing Changed"); // No change has been made on the position pot.
  }

delay(1000); //wait 1 second to check for a new trimpot(servo) position
                            
newval = map_pot1; //Store value of servo pot to help detect change in the next loop

}//
