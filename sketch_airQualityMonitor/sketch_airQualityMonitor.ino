#include <DHT.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define MQ135_PIN A0

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);

float temp;
float humidity;
int airQualityRaw;

void setup() {
  Serial.begin(9600);

  pinMode(DHTPIN, INPUT);
  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  display.clearDisplay();

  display.display();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(50, 0);
  display.println("Air");
  display.setTextSize(1);
  display.setCursor(23, 20);
  display.println("Quality monitor");
  display.display();

  delay(1200);

  display.clearDisplay();

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println(F("Temperature, Humidity, and Air Quality Monitor"));
}

void dhtSensorRead() {
  temp = dht.readTemperature();
  humidity = dht.readHumidity();

  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }


  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 26);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");

  display.setCursor(0, 36);
  display.print("Humidity: ");
  display.print(humidity);
  display.print(" %");
}



void airSensorRead() {
  airQualityRaw = analogRead(MQ135_PIN);

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 5);
  display.print("Air Quality: ");
  display.println(airQualityRaw);
}


void loop() {

  display.clearDisplay();
  dhtSensorRead();
  airSensorRead();
  display.display();


  Serial.print(F("Temperature: "));
  Serial.print(temp);
  Serial.print(F("°C\tHumidity: "));
  Serial.print(humidity);
  Serial.print(F("%\tAir Quality (Raw): "));
  Serial.println(airQualityRaw);

  const char state = Serial.read();

  if (state == 'f') {
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (state == 't') {
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(500);
}
