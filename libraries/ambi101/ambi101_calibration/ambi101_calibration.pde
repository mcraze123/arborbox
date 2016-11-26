void setup() {
  // use digital pin 2 to power second ambi
  pinMode(2, OUTPUT);
  digitalWrite(2,HIGH);
  Serial.begin(9600);
}

void loop() {
  int nSamples=100;
  float a0_avg=0;
  float a1_avg=0;
  float a2_avg=0;
  float total_avg=0;
  for(int i=0;i<nSamples;i++){
    a0_avg += analogRead(0) / nSamples;
    a1_avg += analogRead(1) / nSamples;
    a2_avg += analogRead(2) / nSamples;
  }
  total_avg=(a0_avg+a1_avg)/2;
  Serial.print("A0=");
  Serial.print((int)a0_avg);
  Serial.print("  A1=");
  Serial.print((int)a1_avg);
  Serial.print("  A2=");
  Serial.print((int)a2_avg);
  Serial.print("   AVG=");
  Serial.print(total_avg);
  Serial.print("   %DIFF=");
  Serial.print(100*(abs(a0_avg - a1_avg)/((a0_avg+a1_avg)/2)));
  Serial.print("   LUX=");
  //Serial.println(0.6415*exp(0.0117*total_avg));
  // modified 04-27-2013
  Serial.println(0.4743*exp(0.0123*total_avg));
  delay(1000);
}