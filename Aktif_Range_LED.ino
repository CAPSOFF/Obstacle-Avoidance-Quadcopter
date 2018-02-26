void Aktif_Range_LED() 
{
 if ((Depan < 150) && (Depan > 0))
 {
  digitalWrite(37, HIGH);
 }
 else
 {
  digitalWrite(37, LOW);
 } 

 if ((Kanan < 150) && (Kanan > 0))
 {
  digitalWrite(39, HIGH);
 }
 else
 {
  digitalWrite(39, LOW);
 } 

 if ((Belakang < 150) && (Belakang > 0))
 {
  digitalWrite(41, HIGH);
 }
 else
 {
  digitalWrite(41, LOW);
 } 

 if ((Kiri < 150) && (Kiri > 0))
 {
  digitalWrite(43, HIGH);
 }
 else
 {
  digitalWrite(43, LOW);
 } 
}
