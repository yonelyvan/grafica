#include <Stepper.h>
#define STEPS 2048

const int cam_enfoque_2 = 2;
const int cam_video_4 = 4;
const int laser_7 = 7;
const int video_status_12 = 12 ;
Stepper stepper(STEPS, 8, 9, 10, 11);
 
void setup() {
	stepper.setSpeed(4);//alta presicion 3-8 3(20s) 4(15s) 5(12s)
	pinMode(cam_enfoque_2, OUTPUT);
	pinMode(cam_video_4, OUTPUT);
	pinMode(laser_7, OUTPUT);
	pinMode(video_status_12, OUTPUT);
}

void press_button_cam(){
	digitalWrite(cam_enfoque_2, HIGH);//enfoque
	delay(20);
	digitalWrite(cam_video_4, HIGH);//captura video
	delay(100);
	digitalWrite(cam_video_4, LOW);
	delay(20);
	digitalWrite(cam_enfoque_2, LOW); 
}


void rodar(){
	int pausa_conectar_camara=10000;//10s
	int cam_retardo=800;
	int pasos = 2048;//equivalente a una vuelta
	delay(pausa_conectar_camara); //tiempo para conectar camara fisicamente

	digitalWrite(laser_7, HIGH); //iniciar laser
	//iniciar video
	digitalWrite(video_status_12, HIGH);//video status
	press_button_cam(); //inicio video
	delay(cam_retardo);
	stepper.step(pasos);//girar motor una vuelta
	press_button_cam(); //fin video

	digitalWrite(video_status_12, LOW);//video status
	delay(cam_retardo);//apagar laser
	digitalWrite(laser_7, LOW); //apagar laser  
}

void loop() {
	rodar();
	delay(60000);//1m pausa
}