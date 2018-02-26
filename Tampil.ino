void tampil() 
{
 if (pwm_value_Mod >= 1600)
 {
  Serial.print(" Depan: "); Serial.print(Depan);
  Serial.print(" ");
  Serial.print(" Belakang: "); Serial.print(Belakang);
  Serial.print(" ");
  Serial.print(" PWM PITCH: "); Serial.print(outfrekuensi_PITCH);
  
  Serial.print(" |||");
  
  Serial.print(" Kanan: "); Serial.print(Kanan); 
  Serial.print(" ");
  Serial.print(" Kiri: "); Serial.print(Kiri);
  Serial.print(" ");
  Serial.print(" PWM ROLL: "); Serial.print(outfrekuensi_ROLL);
  
  Serial.println();   
 }
 else
 {
  Serial.print(" Depan: "); Serial.print(Depan);
  Serial.print(" ");
  Serial.print(" Belakang: "); Serial.print(Belakang);
  Serial.print(" ");
  Serial.print(" PWM PITCH: "); Serial.print("UNMODE");
  
  Serial.print(" |||");
  
  Serial.print(" Kanan: "); Serial.print(Kanan); 
  Serial.print(" ");
  Serial.print(" Kiri: "); Serial.print(Kiri);
  Serial.print(" ");
  Serial.print(" PWM ROLL: "); Serial.print("UNMODE");;
  
  Serial.println();  
 }
 
}
