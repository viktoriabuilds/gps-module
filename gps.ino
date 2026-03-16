#include <TinyGPSPlus.h>

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);   // Monitor output
  Serial1.begin(9600);  // GPS module serial
  Serial.println("GPS Debug Start");
}

void loop() {
  // Feed GPS data into TinyGPSPlus
  while (Serial1.available()) {
    char c = Serial1.read();
    gps.encode(c);
  }

  // Print location if updated
  if (gps.location.isUpdated()) {
    Serial.print("Latitude: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(" | Longitude: ");
    Serial.println(gps.location.lng(), 6);
  }

  // Explain fix status
  Serial.print("Fix quality: ");
  switch (gps.hdop.value()) {  // HDOP correlates with fix quality roughly
    case 0:
      Serial.println("No fix");
      break;
    default:
      Serial.println("Fix acquired (HDOP: " + String(gps.hdop.value()) + ")");
  }

  // Satellites visible
  Serial.print("Satellites visible: ");
  Serial.println(gps.satellites.value());

  // Speed and course
  if (gps.speed.isUpdated()) {
    Serial.print("Speed (km/h): ");
    Serial.println(gps.speed.kmph());
  }

  if (gps.course.isUpdated()) {
    Serial.print("Course: ");
    Serial.println(gps.course.deg());
  }

  // Altitude
  if (gps.altitude.isUpdated()) {
    Serial.print("Altitude (m): ");
    Serial.println(gps.altitude.meters());
  }

  Serial.println("-----------------------");
  delay(1000); // Update every second
}