void EZ3() 
{
 for (int i = 0; i < arraysize_Depan; i++)
 {
  rangevalue_Depan[i] = pwm_value_Depan / 58;
  delay(3);
 }

 for (int i = 0; i < arraysize_Kanan; i++)
 {
  rangevalue_Kanan[i] = pwm_value_Kanan / 58;
  delay(3);
 }

 for (int i = 0; i < arraysize_Belakang; i++)
 {
  rangevalue_Belakang[i] = pwm_value_Belakang / 58;
  delay(3);
 }

 for (int i = 0; i < arraysize_Kiri; i++)
 {
  rangevalue_Kiri[i] = pwm_value_Kiri / 58;
  delay(3);
 }

// Realnya
// Serial.println("----------------------------------");
// Serial.print("Unsorted: ");
// printArray(rangevalue_Depan, arraysize_Depan);
// isort(rangevalue_Depan, arraysize_Depan);
// Serial.print("Sorted: ");
// printArray(rangevalue_Depan, arraysize_Depan);
// Depan = mode(rangevalue_Depan, arraysize_Depan);
// Serial.print("The mode/median is: ");
// Serial.print(Depan);
// Serial.println();
// Serial.println("----------------------------------");  
// delay(3000);
  
  isort(rangevalue_Depan, arraysize_Depan);
  Depan = mode(rangevalue_Depan, arraysize_Depan);
  isort(rangevalue_Kanan, arraysize_Kanan);
  Kanan = mode(rangevalue_Kanan, arraysize_Kanan);
  isort(rangevalue_Belakang, arraysize_Belakang);
  Belakang = mode(rangevalue_Belakang, arraysize_Belakang);
  isort(rangevalue_Kiri, arraysize_Kiri);
  Kiri = mode(rangevalue_Kiri, arraysize_Kiri);        

  if (Depan > threshold_jrk_PITCH)
  {
   Depan = threshold_jrk_PITCH;
  }
  else if (Depan <= 0)
  {
   Depan = 0;
  }

  if (Kanan > threshold_jrk_ROLL)
  {
   Kanan = threshold_jrk_ROLL;
  }
  else if (Kanan <= 0)
  {
   Kanan = 0;
  }

  if (Belakang > threshold_jrk_PITCH)
  {
   Belakang = threshold_jrk_PITCH;
  }
  else if (Belakang <= 0)
  {
   Belakang = 0;
  }
     
  if (Kiri > threshold_jrk_ROLL)
  {
   Kiri = threshold_jrk_ROLL;
  }
  else if (Kiri <= 0)
  {
   Kiri = 0;
  }

//  Serial.print(" Depan: ");
//  Serial.print(Depan); Serial.print(" ");
//  Serial.print(" Kanan: ");
//  Serial.print(Kanan); Serial.print(" ");
//  Serial.print(" Belakang: ");
//  Serial.print(Belakang); Serial.print(" ");
//  Serial.print(" Kiri: "); Serial.print(" ");
//  Serial.print(Kiri);
//  Serial.println();  

//  delay(500);
}
