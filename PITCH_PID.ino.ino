void PITCH_PID() 
{
 Depan_PID = Depan;
 Belakang_PID = Belakang;

 // Depan Sumbu (+)
 Depan_PID = (1*(Depan));
    
 // Belakang Sumbu (-)    
 Belakang_PID = (-1*(Belakang_PID));

 // Mapping Jarak Hanya 0 - threshold_jrk_PITCH 
 if (Depan_PID > threshold_jrk_PITCH)
 {
  Depan_PID = 0;
 }
 
 if (Belakang_PID < -threshold_jrk_PITCH)
 {
  Belakang_PID = 0;
 } 


 if (Depan_PID == 0)
 {
  rDepan = 0; // Kondisi Ketika Depan == 0
 }
 else
 {
  rDepan = threshold_jrk_PITCH - Depan_PID; // Kondisi Ketika Depan != 0
 }
   
 if (Belakang_PID == 0) 
 {
  rBelakang = 0; // Kondisi Ketika Belakang == 0
 }
 else
 {
  rBelakang = ((-threshold_jrk_PITCH) - Belakang_PID); // Kondisi Ketika Belakang != 0
 } 


 setpoint = 0; // Setpoint 
 feedback_PITCH = rDepan+rBelakang; // Feedback (Pemodelan 2 Sensor)
    
 //Hitung Error
 error_PITCH = ((setpoint - feedback_PITCH)*R_PITCH); // R Sebagai Faktor Pembalik (1 atau -1)

 //Hitung Error Integral
 errorIsekarang_PITCH = error_PITCH + errorsebelum_PITCH;
 errorIsekarang1_PITCH = errorIsekarang_PITCH/2;
 errorIsekarang2_PITCH = errorIsekarang1_PITCH*Ts;
 errorI_PITCH = errorIsekarang2_PITCH + errorIsebelum_PITCH;

 //Hitung Error Diferensial
 errorD1_PITCH = error_PITCH-errorsebelum_PITCH;
 errorD_PITCH = errorD1_PITCH/Ts;

 //Kendali PID
 outP_PITCH = Kp_PITCH*error_PITCH;
 outI_PITCH = Ki_PITCH*errorI_PITCH;
 outD_PITCH = Kd_PITCH*errorD_PITCH;
 outPIDsebelum_PITCH = outP_PITCH + outI_PITCH + outD_PITCH; 
 outPIDfrekuensi_PITCH = (outPIDsebelum_PITCH*FX);
 outfrekuensi_PITCH = (1500+outPIDfrekuensi_PITCH);

// membatasi nilai PID agar PID tidak melebihi 2012 kurang dari 988 microsecond
 if(outfrekuensi_PITCH >= 2012)
 {
  outfrekuensi_PITCH = 2012;
 }
 else if(outfrekuensi_PITCH <= 988)
 {
  outfrekuensi_PITCH = 988;
 }
 else
 {
  outfrekuensi_PITCH = outfrekuensi_PITCH;
 } 

 //Deklarasi Error
 errorsebelum_PITCH = error_PITCH;
 errorIsebelum_PITCH = errorI_PITCH;

// Serial.print(" FDep: ");
// Serial.println(rDepan);   
// Serial.print(" FBel: ");
// Serial.println(rBelakang);   
// Serial.print(" Fee: ");
// Serial.println(feedback_PITCH);    
// Serial.println();      
// Serial.print(" Dep: ");
// Serial.println(Depan_PID);     
// Serial.print(" Bel: ");
// Serial.println(Belakang_PID);
// Serial.print(" Err: ");
// Serial.println(error_PITCH);     
// Serial.print(" P  : ");
// Serial.println(outP_PITCH);  
// Serial.print(" I  : ");
// Serial.println(outI_PITCH); 
// Serial.print(" D  : ");
// Serial.println(outD_PITCH); 
// Serial.print(" PID: ");
// Serial.println(outPIDsebelum_PITCH);   
// Serial.print(" Mic: ");
// Serial.println(outPIDfrekuensi_PITCH);
//        
// Serial.print(" PWM: ");
// Serial.println(outfrekuensi_PITCH);
//
// Serial.println("----------------------------------------");
// Serial.println("");

// delay(2000);
}
