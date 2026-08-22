#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64          
#define SCREEN_ADDRESS 0x3C 
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int x = 0;
int y = 0;
int color = 1;
void setup() {
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.display();
  Serial.begin(115200);
}
void loop() {
  int SEL = !digitalRead(7);
  int SEL2 = !digitalRead(8);
  int valY = analogRead(A0);
  int valX = analogRead(A1);
  if (valY > 1000) {
    y--;
  } else if (valY < 20) {
    y++;
  }
  if (valX < 20) {
    x++;
  } else if (valX > 1000) {
    x--;
  }  
  if (!digitalRead(8) || SEL == 1) {
    delay(10);
    display.clearDisplay();
    display.drawPixel(0, 0, color);
    display.clearDisplay();
  }
  if (display.getPixel(x, y) == WHITE) {
    display.drawPixel(x, y, !color);
  } else {
    display.drawPixel(x, y, color);
  }
  x = constrain(x, 0, 127);
  y = constrain(y, 0, 63);
  display.drawPixel(x, y, color);
  display.display();
  Serial.print("X: "); Serial.println(x);
  Serial.print("Y: "); Serial.println(y);
  Serial.print("Sel: "); Serial.println(SEL);
  Serial.print("Current pixel color: "); Serial.println(display.getPixel(x, y));
  Serial.print("Draw color: "); Serial.println(color);
  Serial.flush();
  delay(10);
}
