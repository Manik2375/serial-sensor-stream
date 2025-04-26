#include <DHT.h>

#define DHTPIN 2        
#define DHTTYPE DHT11   
#define MQ135_PIN A0    // Analog pin where MQ135 is connected

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);      
  dht.begin();
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Temperature, Humidity, and Air Quality Monitor");
}

void loop() {
  float temp = dht.readTemperature();    
  float humidity = dht.readHumidity();
  int airQualityRaw = analogRead(MQ135_PIN); // Read raw analog value from MQ135

  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT11 sensor!");
    delay(1000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("°C\tHumidity: ");
  Serial.print(humidity);
  Serial.print("%\tAir Quality (Raw): ");
  Serial.println(airQualityRaw);

  const char state = Serial.read();

  if (state == 'f') {
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (state == 't') {
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(1000); 
}
