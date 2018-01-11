
#include <Time.h>

int b_ini = 0, b_motor = 1, b_sub = 2, b_baja = 3;
int btn_inicio = 0, btn_motor = 0, btn_sub = 0, btn_baja = 0;

// =====================  TIME  ========================
boolean ban_iniciar = false, ban_h = false, ban_seg = false;
int relayMotor = 13;
int cont_horas = 2;
int cont_ini = 0;
int set_dia = 17, set_hora = 23, set_min = 59, set_seg = 55;
time_t t;
// =====================  TIME  ========================

// =====================  LOGICA  ======================

// =====================  LOGICA  ======================


void setup() {
  Serial.begin(9600);
  // =====================  TIME  ========================
  pinMode(relayMotor, OUTPUT);
  digitalWrite(relayMotor, HIGH);
  //t = now();
  //setTime(set_hora, set_min, set_seg, set_dia, 0, 0); // se establece en HH0 MM0 SS0 DD0 M0 AA0

  // =====================  LOGICA  ======================
}

void loop() {
  // =====================  BOTONES  ========================
  btn_inicio = analogRead(b_ini);
  btn_motor = analogRead(b_motor);
  btn_sub = analogRead(b_sub);
  btn_baja = analogRead(b_baja);
  if (btn_inicio > 900) {
    ban_iniciar = true;
    cont_ini = 1;
  }
  if (btn_motor > 900) digitalWrite(relayMotor, LOW);
  else digitalWrite(relayMotor, HIGH);
  if (btn_sub > 900) subir_tem();
  if (btn_baja > 900) baja_tem();
  // =====================  BOTONES  ========================

  // =====================  TIME  ========================
  if ((ban_iniciar) && (cont_ini < 2)) {
    cont_ini = 2;
    t = now();
    setTime(set_hora, set_min, set_seg, set_dia, 0, 0); // se establece en HH0 MM0 SS0 DD0 M0 AA0
  }
  if ((ban_iniciar)) {
    t = now();
    if (day(t) > 18) {
      Serial.print("Dia: ");
      Serial.println(day(t));
      setTime(set_hora, set_min, set_seg, set_dia, 0, 0); // se establece en HH0 MM0 SS0 DD0 M0 AA0
    } else {
      if (minute(t) == 59) {
        ban_h = true;
        if (second(t) > 58) {
          ban_seg = true;
          cont_horas++;
          delay(1000);
        }
      }
    }
    if (ban_h && ban_seg && (cont_horas == 3)) {
      acti_motor();
    }
  }
  // =====================  TIME  ========================



}

void subir_tem() {
  Serial.println("SUBIR TEMP") ;
}

void baja_tem() {
  Serial.println("BAJAR TEMP") ;
}
void acti_motor() {
  digitalWrite(relayMotor, LOW);
  //Serial.print(second(t));
  //Serial.println("MOTOR: Encendido");
  if (second(t) == 10) {
    Serial.println("MOTOR: Apagado");
    digitalWrite(relayMotor, HIGH);
    //Serial.print("CONTADOR: ");
    //Serial.println(cont_horas);
    ban_h = false;
    ban_seg = false;
    cont_horas = 0;
  }
}
