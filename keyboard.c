//Code for using 32 key 8*4 matrix as MIDI controller.
//Written by Jake Charman

//Define global variables.
//Output pins.
int oPins[] = {2,3,4,5,6,7,8,9};
//Input pins.
int iPins[] = {10,11,12,13};
//List of keys and their states  
bool keysOn[] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};

//One time setup function.
void setup() 
{
  //Start the serial port with a baud of 31250.
  Serial.begin(31250);   

  //Set oPins to outputs and set the value to LOW.
  for (int oPin = 0; oPin <= 8; oPin++)
  {
    pinMode(oPins[oPin], OUTPUT);
    digitalWrite(oPins[oPin], LOW);
  }
  
  //Set iPins as inputs.
  for (int iPin = 0; iPin < 4; iPin++)
  {
    pinMode(iPins[iPin], INPUT); 
  }
}

//Function to lookup the key number given the two pins.
int lookupKey(int o, int i)
{
  int key;

  //[TODO] Replace this with something neater.
  if((o == 2) && (i == 10))
  {
    key = 0;
  }
  if((o == 3) && (i == 10))
  {
    key = 1;
  }
  if((o == 4) && (i == 10))
  {
    key = 2;
  }
  if((o == 5) && (i == 10))
  {
    key = 3;
  }
  if((o == 6) && (i == 10))
  {
    key = 4;
  }
  if((o == 7) && (i == 10))
  {
    key = 5;
  }
  if((o == 8) && (i == 10))
  {
    key = 6;
  }
  if((o == 9) && (i == 10))
  {
    key = 7;
  }
  if((o == 2) && (i == 11))
  {
    key = 8;
  }
  if((o == 3) && (i == 11))
  {
    key = 9;
  }
  if((o == 4) && (i == 11))
  {
    key = 10;
  }
  if((o == 5) && (i == 11))
  {
    key = 11;
  }
  if((o == 6) && (i == 11))
  {
    key = 12;
  }
  if((o == 7) && (i == 11))
  {
    key = 13;
  }
  if((o == 8) && (i == 11))
  {
    key = 14;
  }
  if((o == 9) && (i == 11))
  {
    key = 15;
  }
  if((o == 2) && (i == 12))
  {
    key = 16;
  }
  if((o == 3) && (i == 12))
  {
    key = 17;
  }
  if((o == 4) && (i == 12))
  {
    key = 18;
  }
  if((o == 5) && (i == 12))
  {
    key = 19;
  }
  if((o == 6) && (i == 12))
  {
    key = 20;
  }
  if((o == 7) && (i == 12))
  {
    key = 21;
  }
  if((o == 8) && (i == 12))
  {
    key = 22;
  }
  if((o == 9) && (i == 12))
  {
    key = 23;
  }
  if((o == 2) && (i == 13))
  {
    key = 24;
  }
  if((o == 3) && (i == 13))
  {
    key = 25;
  }
  if((o == 4) && (i == 13))
  {
    key = 26;
  }
  if((o == 5) && (i == 13))
  {
    key = 27;
  }
  if((o == 6) && (i == 13))
  {
    key = 28;
  }
  if((o == 7) && (i == 13))
  {
    key = 29;
  }
  if((o == 8) && (i == 13))
  {
    key = 30;
  }
  if((o == 9) && (i == 13))
  {
    key = 31;
  }

  //Return the key number.
  return key;
}

//Send the MIDI on command for the given key.
void noteOn(int key)
{
  //MIDI constants.
  int midiKeys[] = {53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84};
  int midiVelocity = 127;
  int command;
  //Set the key to true.
  keysOn[key] = true;
  //Send the MIDI commands.
  Serial.write(0x91);
  Serial.write(midiKeys[key]);
  Serial.write(midiVelocity);
}

//Send the MIDI off command for the given key.
void noteOff(int key)
{
  //MIDI constants.
  int midiKeys[] = {53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84};
  int midiVelocity = 0;
  int command;
  //Set the key to false.
  keysOn[key] = false;
  //Send the MIDI commands
  Serial.write(0x91);
  Serial.write(midiKeys[key]);
  Serial.write(midiVelocity);
}

//Loop function, scan the matrix and call the relevant functions.
void loop() 
{
  //For every oPin.
  for(int oPin = 0; oPin < 8; oPin ++)
  {
    //Set the pin to HIGH.
    digitalWrite(oPins[oPin], HIGH);
    //For every iPin.
    for(int iPin = 0; iPin < 4; iPin ++)
    {
      //If the pin reads LOW.
      if(digitalRead(iPins[iPin]) == LOW)
      {
        //If the key is true.
        if (keysOn[lookupKey(oPins[oPin], iPins[iPin])] == true)
        {
          //Send the note off command for the key.
          noteOff(lookupKey(oPins[oPin], iPins[iPin]));
        }
      }

      //If the pin is HIGH.
      else if (digitalRead(iPins[iPin]) == HIGH)
      {
        //If the key is false.
        if (keysOn[lookupKey(oPins[oPin], iPins[iPin])] == false)
        {
          //Send the note on command for the key.
          noteOn(lookupKey(oPins[oPin], iPins[iPin]));
        }
      }
    }
    //Set the oPin back to LOW
    digitalWrite(oPins[oPin], LOW);
  }
}
