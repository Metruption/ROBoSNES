
//the pins that we will solder to the snes
const short dataPin = 23;
const short clockPin = 22;
const short latchPin = 21;

//these pins we do not solder to the snes
const short ledPin = 20;
const short recordButton = 19;
const short playButton = 18;

//how many frames per second we are running at
//unsigned because it's never going to be zero
const unsigned int FRAMERATE = 60

//this value represents the number of frames we will be keeping in the buffer
const unsigned int MOVIELENGTH = FRAMERATE * 120;
						//the last number in this line is how many seconds the movie lasts

//allocate memory for the movie
word movieBuffer[MOVIELENGTH];
word *movie = &movieBuffer;

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

void loop(){
	//listen to buttons
	recordState = digitalRead(recordButton);
	playState = digitalRead(playButton);

	//respond to buttons
	digitalWrite(led, HIGH);
	if (recordState == HIGH){
		prepareMovie();
		recordMovie();
	}
	else if (playState == HIGH){
		prepareMovie():
		playMovie();
	}
}

void recordMovie(){
	//set data pin to read
	pinMode(data, INPUT);

	//i represents the current frame
	for(int i = 0;i<MOVIELENGTH;i++){
		//@todo(will): wait for latch

		for(int currentBit=0;currentBit<11;currentBit++){
			//@todo(will): wait for the clock

			//read data pin status (1 or 0)
			//this will give us HIGH or LOW
			//HIGH casts as an int to 1 and as a bool to true
			//LOW casts as an int to 0 and as a bool to false
			pinStatus = (int)digitalRead(data);

			//every frame we write the inputs to the buffer
			bitWrite(*(movie + i), currentBit, pinStatus);


		}
	}
}

void playMovie(){
	//set data pin to WRITE
	pintMode(DATA, OUTPUT);

	//i represents the current frame
	for(int i = 0;i<MOVIELENGTH;i++){
		//@todo(will): wait for latch

		for(int currentBit=0;currentBit<11;currentBit++){
			//@todo(will): wait for the clock

			//read data pin status (1 or 0)
			//this will give us HIGH or LOW
			//HIGH casts as an int to 1 and as a bool to true
			//LOW casts as an int to 0 and as a bool to false
			pinStatus = bitRead(*(movie + i), currentBit);
			digitalWrite(dataPin, pinStatus);
}

//keeping code DRY since 2017.
void prepareMovie(){
	digitalWrite(ledPin, LOW);
	//*movieIndex = &movieBuffer;
}

void emptyBuffer(){
	for(int i=0;i<movieBuffer.length;i++){
		movieBuffer[i] = 15; //that sets the bits to 0000000000001111
							 //the first twelve bits are the inputs
							 //the inputs are sent in the following order:
							 	//BY*E^v<>AXLR it sends 16 bits and the next four are just junk data
								//* = STARt
									//E = sElEct
	}
}
