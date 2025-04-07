#define IR 33  // Analog input pin
int val = 0;

HardwareSerial mySerial(1);  // Create Serial1 for TX/RX communication

void setup() {
    Serial.begin(9600);  // Debugging Serial (USB)
    mySerial.begin(9600, SERIAL_8N1, 17, 16);  // TX=17, RX=16 (ESP32 Hardware Serial)
    pinMode(IR, INPUT);
}

void loop() {
    val = analogRead(IR);
    float voltage = val * (3.3 / 4095.0);  // Convert ADC value to voltage
    
    Serial.print("Debug: ");
    Serial.println(voltage, 2);  // Print float with 2 decimal places

    // Send float data as 4 bytes (binary transmission)
    mySerial.write((byte*)&voltage, sizeof(voltage));

    delay(1000);
}
