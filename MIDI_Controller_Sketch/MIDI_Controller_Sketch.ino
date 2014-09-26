// Pin Values for each Button
int Button[4][4] = 
{
  { 0,  2,  3,  4},
  { 5,  6,  7,  8},
  { 9, 10, 11, 12},
  {14, 15, 16, 17}
};

// The note corrisponding to the button
int Note[4][4] = 
{
  {0x30, 0x31, 0x32, 0x33},
  {0x2C, 0x2D, 0x2E, 0x2F},
  {0x28, 0x29, 0x2A, 0x2B},
  {0x24, 0x25, 0x26, 0x27}
};

// Saved state for each Button (1=on,0=off)
int State[4][4] = 
{
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0}
};

// Turn on a note of pitch though MIDI serial
void noteOn(int pitch) {
  Serial.write(0x90); // Channel
  Serial.write(pitch); // Pitch
  Serial.write(0x45); // 100% Velocity
}

// Turn off a note of pitch though MIDI serial
void noteOff(int pitch) {
  Serial.write(0x90); // Channel
  Serial.write(pitch); // Pitch
  Serial.write(0x00); // 0% Velocity
}

void setup() {
  Serial.begin(31250);
  // Assign INPUTS to delcared pins
  for (int row = 0; row < 4; row ++){
    for (int col = 0; col < 4; col ++){
      pinMode(Button[row][col], INPUT_PULLUP);
    }
  }
}

void loop(){
  for (int row = 0; row < 4; row ++){
    for (int col = 0; col < 4; col ++){
      if (digitalRead(Button[row][col]) == LOW){
        if (State[row][col] == 0){
          // Button is down, wasn't last cycle
          State[row][col] = 1;
          noteOn(Note[row][col]);
          delay(50);
        }
      } else {
        if (State[row][col] == 1){
          // Button is up, wasn't last cycle
          State[row][col] = 0;
          noteOff(Note[row][col]);
        }
      }
    }
  }
}
