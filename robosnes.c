
//the pins that we will solder to the snes
const int data = 23;
const int clock = 22;
const int latch = 21;

//these pins we do not solder to the snes
const int led = 20;
const int recordButton = 19;
const int playButton = 18;

//allocate memory for the movie (14 KILOBYTES!!!)
word movieBuffer[7200];
word *movieIndex;

void setup(){
	//set the clock speed
	//will do this please

	//set the pinmodes for the pins that don't change modes
	pinMode(led, OUTPUT);
	pinMode(recordButton, INPUT);
	pinMode(playButton, INPUT);
	pinMode(clock, INPUT)
	pinMode(latch, INPUT)

	//initialize movie buffer to 0
	for(int i=0;i<movieBuffer.length;i++){
		movieBuffer[i] = 0;
	}

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

	//do stuff
}

void playMovie(){
	//set data pin to WRITE
	pintMode(DATA, OUTPUT);

	//do stuff
}

//keeping code DRY since 2017.
void prepareMovie(){
	digitalWrite(led, LOW);
	*movieIndex = &movieBuffer;
}