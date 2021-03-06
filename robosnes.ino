
//the pins that we will solder to the snes
const short dataPin = 23;
const short clockPin = 22;
const short latchPin = 21;

//these pins we do not solder to the snes
const short ledPin = 13;
const short recordButton = 19;
const short playButton = 14;

//how many frames per second we are running at
//unsigned because it's never going to be zero
const unsigned int FRAMERATE = 60;

//this value represents the number of frames we will be keeping in the buffer
const int MOVIELENGTH = FRAMERATE * 45;
            //the last number in this line is how many seconds the movie lasts

//allocate memory for the movie
//an int would probably work here but I don't want to deal with negative numbers
//int is two bytes and we need two bytes for frames so this just works
unsigned int movieBuffer[MOVIELENGTH];
unsigned int *movie = movieBuffer;
 int recordState = digitalRead(recordButton);
  int playState = digitalRead(playButton);
void setup(){
  //set the clock speed
  //will do this please
  //we might not need to

  //set the pinmodes for the pins that don't change modes
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  pinMode(recordButton, INPUT);
  pinMode(playButton, INPUT);
  pinMode(clockPin, INPUT);
  pinMode(latchPin, INPUT);
  digitalWrite(ledPin, LOW);
  
  //initialize movie buffer to 0
  emptyBuffer();
}


void recordMovie(){
  //set data pin to read
  pinMode(dataPin, INPUT);

  //i represents the current frame
  for(int i = 0;i<MOVIELENGTH;i++){
    pulseIn(latchPin, HIGH);
    digitalWrite(ledPin, HIGH);

    for(int currentBit=0;currentBit<16;currentBit++){
      pulseIn(clockPin, HIGH);

      //read data pin status (1 or 0)
      //this will give us HIGH or LOW
      //HIGH casts as an int to 1 and as a bool to true
      //LOW casts as an int to 0 and as a bool to false
      int pinStatus = digitalRead(dataPin);

      //every frame we write the inputs to the buffer
      bitWrite(*(movie + i), currentBit, pinStatus);


    }
    digitalWrite(ledPin, LOW);
  }
}

void playMovie(){
  //set data pin to WRITE
  pinMode(dataPin, OUTPUT);

  //i represents the current frame
  for(int i = 0;i<MOVIELENGTH;i++){
    pulseIn(latchPin,HIGH );
    digitalWrite(ledPin, HIGH);

    for(int currentBit=0;currentBit<16;currentBit++){
      pulseIn(clockPin,HIGH );

      //read data pin status (1 or 0)
      //this will give us HIGH or LOW
      //HIGH casts as an int to 1 and as a bool to true
      //LOW casts as an int to 0 and as a bool to false
      int pinStatus = bitRead(*(movie + i), currentBit);
      digitalWrite(dataPin, pinStatus);
    }
    digitalWrite(ledPin, LOW);
  }
}


void emptyBuffer(){
  for(int i=0;i<MOVIELENGTH;i++){
    movieBuffer[i] = 15; //that sets the bits to 0000000000001111
               //the first twelve bits are the inputs
               //the inputs are sent in the following order:
                //BY*E^v<>AXLR it sends 16 bits and the next four are just junk data
                //* = STARt
                  //E = sElEct
  }
}


void loop(){
  //listen to buttons
  recordState = digitalRead(recordButton);
  playState = digitalRead(playButton);

  //respond to buttons
  digitalWrite(ledPin, HIGH);
  if (recordState == HIGH){
    digitalWrite(ledPin, LOW);
    recordMovie();
  }
  else if (playState == HIGH){
    digitalWrite(ledPin, LOW);
    playMovie();
  }
}

