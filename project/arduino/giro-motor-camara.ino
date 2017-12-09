// Definimos el pin que utilizará nuestro LED, en este caso 13.
const int let8 = 8;
const int let7 = 7;

void setup() {
      // Definimos let13 como un pin de salida
      pinMode(let8, OUTPUT);
      pinMode(let7, OUTPUT);
}
 
 void loop() {
    int motor_on=25;
    int pausa=500;
    int tomar_foto=20;
    int pausa_final=60000; //un minuto para desconectar arduino
     Serial.begin(9600);
     Serial.println("OK inicia 10s");
     delay(10000);
     
     int it = 0;
     while(it <= 106){//104 106
      Serial.println(it);
      // motor
      digitalWrite(let7, HIGH);
      delay(motor_on); 
      digitalWrite(let7, LOW);
      delay(pausa);
  
      // camara
      digitalWrite(let8, HIGH);
      delay(tomar_foto); 
      digitalWrite(let8, LOW);
      delay(pausa);

      it++;
    }
    delay(pausa_final);
}
