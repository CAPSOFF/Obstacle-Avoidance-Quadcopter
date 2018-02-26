void ROLL_PID() 
{
 Kanan_PID = Kanan;
 Kiri_PID = Kiri;

 // Kanan Sumbu (+)
 Kanan_PID = (1*(Kanan));
    
 // Kiri Sumbu (-)    
 Kiri_PID = (-1*(Kiri_PID));

 // Mapping Jarak Hanya 0 - threshold_jrk_ROLL 
 if (Kanan_PID > threshold_jrk_ROLL)
 {
  Kanan_PID = 0;
 }
 
 if (Kiri_PID < -threshold_jrk_ROLL)
 {
  Kiri_PID = 0;
 } 


 if (Kanan_PID == 0)
 {
  rKanan = 0; // Kondisi Ketika Kanan == 0
 }
 else
 {
  rKanan = threshold_jrk_ROLL - Kanan_PID; // Kondisi Ketika Kanan != 0
 }
   
 if (Kiri_PID == 0) 
 {
  rKiri = 0; // Kondisi Ketika Kiri == 0
 }
 else
 {
  rKiri = ((-threshold_jrk_ROLL) - Kiri_PID); // Kondisi Ketika Kiri != 0
 } 


 setpoint = 0; // Setpoint 
 feedback_ROLL = rKanan+rKiri; // Feedback (Pemodelan 2 Sensor)
    
 //Hitung Error
 error_ROLL = ((setpoint - feedback_ROLL)*R_ROLL); // R Sebagai Faktor Pembalik (1 atau -1)

 //Hitung Error Integral
 errorIsekarang_ROLL = error_ROLL + errorsebelum_ROLL;
 errorIsekarang1_ROLL = errorIsekarang_ROLL/2;
 errorIsekarang2_ROLL = errorIsekarang1_ROLL*Ts;
 errorI_ROLL = errorIsekarang2_ROLL + errorIsebelum_ROLL;

 //Hitung Error Diferensial
 errorD1_ROLL = error_ROLL-errorsebelum_ROLL;
 errorD_ROLL = errorD1_ROLL/Ts;

 //Kendali PID
 outP_ROLL = Kp_ROLL*error_ROLL;
 outI_ROLL = Ki_ROLL*errorI_ROLL;
 outD_ROLL = Kd_ROLL*errorD_ROLL;
 outPIDsebelum_ROLL = outP_ROLL + outI_ROLL + outD_ROLL; 
 outPIDfrekuensi_ROLL = (outPIDsebelum_ROLL*FX);
 outfrekuensi_ROLL = (1500+outPIDfrekuensi_ROLL);

// membatasi nilai PID agar PID tidak melebihi 2012 kurang dari 988 microsecond
 if(outfrekuensi_ROLL >= 2012)
 {
  outfrekuensi_ROLL = 2012;
 }
 else if(outfrekuensi_ROLL <= 988)
 {
  outfrekuensi_ROLL = 988;
 }
 else
 {
  outfrekuensi_ROLL = outfrekuensi_ROLL;
 } 

 //Deklarasi Error
 errorsebelum_ROLL = error_ROLL;
 errorIsebelum_ROLL = errorI_ROLL;

// Serial.print(" FDep: ");
// Serial.println(rKanan);   
// Serial.print(" FBel: ");
// Serial.println(rKiri);   
// Serial.print(" Fee: ");
// Serial.println(feedback_ROLL);    
// Serial.println();      
// Serial.print(" Dep: ");
// Serial.println(Kanan_PID);     
// Serial.print(" Bel: ");
// Serial.println(Kiri_PID);
// Serial.print(" Err: ");
// Serial.println(error_ROLL); 
// Serial.print(" P  : ");
// Serial.println(outP_ROLL);  
// Serial.print(" I  : ");
// Serial.println(outI_ROLL); 
// Serial.print(" D  : ");
// Serial.println(outD_ROLL); 
// Serial.print(" PID: ");
// Serial.println(outPIDsebelum_ROLL);   
// Serial.print(" Mic: ");
// Serial.println(outPIDfrekuensi_ROLL);
//        
// Serial.print(" PWM: ");
// Serial.println(outfrekuensi_ROLL);
//
// Serial.println("----------------------------------------");
// Serial.println("");

// delay(2000);
}
