void setup() {
  pinMode(A0, OUTPUT);
  Serial.begin(9600); //Set serial begin
}

void loop() {
  Serial.println (analogRead(A0)); // Read and print the values.
}
