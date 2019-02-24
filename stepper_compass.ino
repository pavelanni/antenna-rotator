#include <CheapStepper.h>
#include <Wire.h>
#include <WiFi.h>
#include <aREST.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

// Assign a unique ID to this sensor at the same time
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

// declare the stepper
// and connect pins 12, 13, 14, 15 to IN1,IN2,IN3,IN4 on ULN2003 board

CheapStepper stepper (12, 13, 14, 15);  

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "ElmStreet-G";
const char* password = "grabthiscoolhotspot";

// Create an instance of the server
WiFiServer server(80);

int turn_to_azimuth(String azstr);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  stepper.setRpm(12);

  if(!mag.begin()) {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }

  // Function to be exposed
  rest.function("turn",turn_to_azimuth);
  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("1");
  rest.set_name("esp32"); 
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP()); 
}

void loop() {
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}

int turn_to_azimuth(String azstr) {
  float Pi = 3.14159;
  float diff;
  sensors_event_t event; 
  mag.getEvent(&event);

  int azimuth = azstr.toInt();
  
  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
  if (heading < 0) {
    heading = 360 + heading;
  }
  Serial.print("Heading: "); Serial.println(heading);

  while (abs(heading - azimuth) > 1) {
    diff = heading - azimuth;
    if ((diff > 0 && abs(diff) <=180) || (diff < 0 && abs(diff) >= 180)) {
      stepper.stepCCW();
    } else {
      stepper.stepCW();
    }
    mag.getEvent(&event);
    heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
    if (heading < 0) {
    heading = 360 + heading;
    }
 //   Serial.println(heading);
 //   Serial.println(diff);
  }
  return(int(heading));
}

void test() {
  String az;

  az = "45";
  Serial.print("Turning to azimuth: "); Serial.println(az);
  turn_to_azimuth(az);
  if (Serial.available() > 0) exit;
  delay(2000);
  az = "315"; 
  Serial.println("Turning to azimuth: "); Serial.println(az);
  turn_to_azimuth(az);
  if (Serial.available() > 0) exit;
  delay(2000);
  az = "15"; 
  Serial.println("Turning to azimuth: "); Serial.println(az);  
  turn_to_azimuth(az);
  if (Serial.available() > 0) exit;
  delay(2000);
  az = "300"; 
  Serial.println("Turning to azimuth: "); Serial.println(az);
  turn_to_azimuth(az);
  delay(2000); 
}
