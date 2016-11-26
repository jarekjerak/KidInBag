#include <SPI.h>
//Add the SdFat Libraries
#include <SdFat.h>
#include <SdFatUtil.h>
//and the MP3 Shield Library
#include <SFEMP3Shield.h>
#include <NewPing.h>
#include <Servo.h>
#include <AFMotor.h>

#define ECHO_PIN 9
#define TRIGGER_PIN 10
#define MAX_DISTANCE 600

#define SERVO1_PWM 10

// DC motor on M2
AF_DCMotor motor(2);

SdFat sd;
SFEMP3Shield MP3player;
byte result = 0;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo servo_1;


void setup() {
	Serial.begin(115200);
	//Initialize the SdCard.
	if (!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
	if (!sd.chdir("/")) sd.errorHalt("sd.chdir");

	//Initialize the MP3 Player Shield
	result = MP3player.begin();

	servo_1.attach(SERVO1_PWM);
}

void loop() {
	delay(500);
	int uS = sonar.ping() / US_ROUNDTRIP_CM;
	Serial.println(uS);
	if ((uS < 100) && (uS >10)) {
		char trackName[] = "track007.mp3";
		sd.chvol(); // assign desired sdcard's volume.
					//MP3player.setVolume(0,100);
		result = MP3player.playMP3(trackName);
		delay(5000);
		for (int i = 0; i <= 60; i++) {
			motor.run(FORWARD);
			motor.setSpeed(200);
			delay(150);
			motor.run(BACKWARD);
			motor.setSpeed(150);
			delay(100);

			Serial.println(i);
		}
		Serial.println("DONE FOR");
	}
	Serial.println("DONE LOOP");
}