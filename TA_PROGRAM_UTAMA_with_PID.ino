// ----------------PID---------------- //
float Ts = 0.05            , // <== Waktu Sampling
      FX = 3.41333333      , // <== Faktor Pengali Frekuensi
      setpoint;
      
//Pitch
//P = 0.88442
//I = 0.071951
//D = 2.6694
//Roll
//P = 0.88592
//I = 0.12243
//D = 1.4708
      
float Kp_PITCH = 1.5, // <== Kp Pitch
      Ki_PITCH = 0 , // <== Ki Pitch
      Kd_PITCH = 0 ; // <== Kd Pitch
      
float Kp_ROLL = 1.5  , // <== Kp Roll
      Ki_ROLL = 0  , // <== Ki Roll
      Kd_ROLL = 0 ; // <== Kd Roll
           
int R_PITCH                 = -1  , // <== Pembalik Error (1 atau -1) untuk Pitch
    threshold_jrk_PITCH = 150     ; // <== Batas Pembacaan Sensor untuk Kalkulasi PID Pitch
    
int R_ROLL                 = 1  , // <== Pembalik Error (1 atau -1) untuk Roll
    threshold_jrk_ROLL = 150     ; // <== Batas Pembacaan Sensor untuk Kalkulasi PID Roll

//Definisi variabel untuk perhitungan PID
float feedback_PITCH,
      error_PITCH,
      errorD_PITCH, errorD1_PITCH,
      errorI_PITCH, errorIsekarang_PITCH, errorIsekarang1_PITCH, errorIsekarang2_PITCH,
      outP_PITCH, outI_PITCH, outD_PITCH, outPIDsebelum_PITCH,
      errorsebelum_PITCH = 0,
      errorIsebelum_PITCH = 0;

float feedback_ROLL,
      error_ROLL,
      errorD_ROLL, errorD1_ROLL,
      errorI_ROLL, errorIsekarang_ROLL, errorIsekarang1_ROLL, errorIsekarang2_ROLL,
      outP_ROLL, outI_ROLL, outD_ROLL, outPIDsebelum_ROLL,
      errorsebelum_ROLL = 0,
      errorIsebelum_ROLL = 0;      

int Depan_PID,Belakang_PID,
    rDepan, rBelakang,
    outPIDfrekuensi_PITCH, outfrekuensi_PITCH;

int Kanan_PID,Kiri_PID,
    rKanan, rKiri,
    outPIDfrekuensi_ROLL, outfrekuensi_ROLL;    
// ****************PID**************** //

// ----------------SENSOR EZ3---------------- //
int ultraSoundTriggerPin = 7; 
int arraysize_Depan = 9;
int rangevalue_Depan[] = {  0, 0, 0, 0, 0, 0, 0, 0, 0};
int Depan;
int arraysize_Kanan = 9;
int rangevalue_Kanan[] = {  0, 0, 0, 0, 0, 0, 0, 0, 0};
int Kanan;
int arraysize_Belakang = 9;
int rangevalue_Belakang[] = {  0, 0, 0, 0, 0, 0, 0, 0, 0};
int Belakang;
int arraysize_Kiri = 9;
int rangevalue_Kiri[] = {  0, 0, 0, 0, 0, 0, 0, 0, 0};
int Kiri;
// ****************SENSOR EZ3**************** //

// ----------------Interrupt---------------- //
#include <Servo.h>
Servo Ail, Ele;

#include <PinChangeInt.h>

#define inAil A10 // Aileron (Kanan - Kiri)
volatile int pwm_value_Ail = 0;
volatile int prev_time_Ail = 0;
uint8_t latest_interrupted_pin_Ail;

#define inEle A9 // Elevator (Depan - Belakang)
volatile int pwm_value_Ele = 0;
volatile int prev_time_Ele = 0;
uint8_t latest_interrupted_pin_Ele;

#define inMod A8 // Mode
volatile int pwm_value_Mod = 0;
volatile int prev_time_Mod = 0;
uint8_t latest_interrupted_pin_Mod;

volatile int pwm_value_Depan = 0;
volatile int prev_time_Depan = 0;
volatile int pwm_value_Kanan = 0;
volatile int prev_time_Kanan = 0;
volatile int pwm_value_Belakang = 0;
volatile int prev_time_Belakang = 0;
volatile int pwm_value_Kiri = 0;
volatile int prev_time_Kiri = 0;
// ****************Interrupt**************** //

void rising_Ail()
{
  latest_interrupted_pin_Ail=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin_Ail, &falling_Ail, FALLING);
  prev_time_Ail = micros();
}
 
void falling_Ail() 
{
  latest_interrupted_pin_Ail=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin_Ail, &rising_Ail, RISING);
  pwm_value_Ail = micros()-prev_time_Ail;
}

void rising_Ele()
{
  latest_interrupted_pin_Ele=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin_Ele, &falling_Ele, FALLING);
  prev_time_Ele = micros();
}
 
void falling_Ele() 
{
  latest_interrupted_pin_Ele=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin_Ele, &rising_Ele, RISING);
  pwm_value_Ele = micros()-prev_time_Ele;
}

void rising_Mod()
{
  latest_interrupted_pin_Mod=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin_Mod, &falling_Mod, FALLING);
  prev_time_Mod = micros();
}
 
void falling_Mod() 
{
  latest_interrupted_pin_Mod=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin_Mod, &rising_Mod, RISING);
  pwm_value_Mod = micros()-prev_time_Mod;
}

void rising_Depan() 
{
 attachInterrupt(2, falling_Depan, FALLING);
 prev_time_Depan = micros();
}

void falling_Depan() 
{
 attachInterrupt(2, rising_Depan, RISING);
 pwm_value_Depan = micros()-prev_time_Depan;
}

void rising_Kanan() 
{
 attachInterrupt(3, falling_Kanan, FALLING);
 prev_time_Kanan = micros();
}

void falling_Kanan() 
{
 attachInterrupt(3, rising_Kanan, RISING);
 pwm_value_Kanan = micros()-prev_time_Kanan;
}

void rising_Belakang() 
{
 attachInterrupt(4, falling_Belakang, FALLING);
 prev_time_Belakang = micros();
}

void falling_Belakang() 
{
 attachInterrupt(4, rising_Belakang, RISING);
 pwm_value_Belakang = micros()-prev_time_Belakang;
}

void rising_Kiri() 
{
 attachInterrupt(5, falling_Kiri, FALLING);
 prev_time_Kiri = micros();
}

void falling_Kiri() 
{
 attachInterrupt(5, rising_Kiri, RISING);
 pwm_value_Kiri = micros()-prev_time_Kiri;
}

void setup() 
{
 Serial.begin(57600);

 Ail.attach(5);
 Ele.attach(6);
 
 pinMode(ultraSoundTriggerPin, OUTPUT);
 delay(250); 
 digitalWrite(ultraSoundTriggerPin, HIGH); 
 delayMicroseconds(30); 
 digitalWrite(ultraSoundTriggerPin, LOW); 
 pinMode(ultraSoundTriggerPin, INPUT);
 delay(50); 
   
 pinMode(inAil, INPUT); digitalWrite(inAil, HIGH);
 PCintPort::attachInterrupt(inAil, &rising_Ail, RISING);

 pinMode(inEle, INPUT); digitalWrite(inEle, HIGH);
 PCintPort::attachInterrupt(inEle, &rising_Ele, RISING); 

 pinMode(inMod, INPUT); digitalWrite(inMod, HIGH);
 PCintPort::attachInterrupt(inMod, &rising_Mod, RISING); 
 
 attachInterrupt(2, rising_Depan, RISING);
 attachInterrupt(3, rising_Kanan, RISING);
 attachInterrupt(4, rising_Belakang, RISING);
 attachInterrupt(5, rising_Kiri, RISING);
 
 pinMode(37, OUTPUT); // Depan
 pinMode(39, OUTPUT); // Kanan
 pinMode(41, OUTPUT); // Belakang
 pinMode(43, OUTPUT); // Kiri
 delay(500);
}

void loop() 
{
 EZ3();
 tampil();
 
 digitalWrite(37, LOW);  
 digitalWrite(39, LOW);  
 digitalWrite(41, LOW);  
 digitalWrite(43, LOW);

 if (pwm_value_Mod < 1000)
 {
  ByPass2AxisRemote();
 }
    
 if ((pwm_value_Mod >= 1000) && (pwm_value_Mod < 1600))
 {
  ByPass2AxisRemote();
  Aktif_Range_LED();
 }
    
 if (pwm_value_Mod >= 1600)
 {
  Aktif_Range_LED();
//  PITCH_PID(M);
  ROLL_PID();
  ByPassPID();
 }

}  


//Function to print the arrays.
void printArray(int *a, int n)
{
 for (int i = 0; i < n; i++)
 {
  Serial.print(a[i], DEC);
  Serial.print(' ');
 }

 Serial.println();
}

//Sorting function
void isort(int *a, int n) 
{
 for (int i = 1; i < n; ++i)
 {
  int j = a[i];
  int k;
  
  for (k = i - 1; (k >= 0) && (j < a[k]); k--)
  {
   a[k + 1] = a[k];
  }
  a[k + 1] = j;
 }
}

//Mode function, returning the mode or median.
int mode(int *x, int n) 
{
 int i = 0;
 int count = 0;
 int maxCount = 0;
 int mode = 0;
 int bimodal;
 int prevCount = 0;

 while (i < (n - 1)) 
 {
  prevCount = count;
  count = 0;
  
  while (x[i] == x[i + 1]) 
  {
   count++;
   i++;
  }

  if (count > prevCount & count > maxCount) 
  {
   mode = x[i];
   maxCount = count;
   bimodal = 0;
  }
  
  if (count == 0) 
  {
   i++;
  }
  
  if (count == maxCount) 
  { //If the dataset has 2 or more modes.
   bimodal = 1;
  }
 
  if (mode == 0 || bimodal == 1) 
  { //Return the median if there is no mode.
   mode = x[(n / 2)];
  }
  return mode;
 }
}
