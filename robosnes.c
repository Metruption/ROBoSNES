
//the pins that we will solder to the snes
const short dataPin = 23;
const short clockPin = 22;
const short latchPin = 21;

//these pins we do not solder to the snes
const short ledPin = 13;
const short recordButton = 19;
const short playButton = 18;

//how many frames per second we are running at
//unsigned because it's never going to be zero
const unsigned int FRAMERATE = 60;

//this value represents the number of frames we will be keeping in the buffer
const int MOVIELENGTH = FRAMERATE * 120;
						//the last number in this line is how many seconds the movie lasts

//allocate memory for the movie
//an int would probably work here but I don't want to deal with negative numbers
//int is two bytes and we need two bytes for frames so this just works
unsigned int movieBuffer[MOVIELENGTH];
unsigned int *movie = movieBuffer;

void setup(){
	//set the clock speed
	//will do this please
	//we might not need to

	//set the pinmodes for the pins that don't change modes
	pinMode(ledPin, OUTPUT);
	pinMode(recordButton, INPUT);
	pinMode(playButton, INPUT);
	pinMode(clockPin, INPUT);
	pinMode(latchPin, INPUT);

	//initialize movie buffer to 0
	emptyBuffer();
}

//preconditions:
//		waitingPin is a pin set to input mode
//postconditions:
//		makes the program wait until the waitingPin is set to HIGH
void waitFor(int waitingPin){
	int pinStatus;
	do {
		pinStatus= digitalRead(waitingPin);
	} while(pinStatus != HIGH);
}

void recordMovie(){
	//set data pin to read
	pinMode(dataPin, INPUT);

	//i represents the current frame
	for(int i = 0;i<MOVIELENGTH;i++){
		waitFor(latchPin);

		for(int currentBit=0;currentBit<11;currentBit++){
			waitFor(clockPin);

			//read data pin status (1 or 0)
			//this will give us HIGH or LOW
			//HIGH casts as an int to 1 and as a bool to true
			//LOW casts as an int to 0 and as a bool to false
			int pinStatus = digitalRead(dataPin);

			//every frame we write the inputs to the buffer
			bitWrite(*(movie + i), currentBit, pinStatus);


		}
	}
}

void playMovie(){
	//set data pin to WRITE
	pinMode(dataPin, OUTPUT);

	//i represents the current frame
	for(int i = 0;i<MOVIELENGTH;i++){
		waitFor(latchPin);

		for(int currentBit=0;currentBit<11;currentBit++){
			waitFor(clockPin);

			//read data pin status (1 or 0)
			//this will give us HIGH or LOW
			//HIGH casts as an int to 1 and as a bool to true
			//LOW casts as an int to 0 and as a bool to false
			int pinStatus = bitRead(*(movie + i), currentBit);
			digitalWrite(dataPin, pinStatus);
		}
	}
}


void emptyBuffer(){
	for(int i=0;i<MOVIELENGTH;i++){
		movieBuffer[i] = 0; //it is 0 now because I say so!!!!
		/*
		'Multiple exclamation marks,' he went on, shaking his head, 'are a sure sign of a diseased mind.'
		- Eric (Terry Pratchett)
		*/
	}
}

//preconditions: presspin will sometimes be true (like a button)
//postconditions: returns true when it held for .5 seconds
//which we define as being true 10 times in a row within 50ms increments
bool longPress(int pressPin){
	int pressState = digitalRead(pressPin);
	for(int i=0;i<10;i++){
		if(pressState != HIGH){
			return false;
		}
		delay(50);
	}
	return true;
}

void loop(){
	//listen to and respond to buttons
	digitalWrite(ledPin, HIGH);
	if (longPress(recordButton)){
		digitalWrite(ledPin, LOW);
		recordMovie();
	}
	else if (longpress(playButton)){
		digitalWrite(ledPin, LOW);
		playMovie();
	}
}

