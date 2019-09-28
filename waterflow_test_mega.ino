#include <OneWire.h>
#include <DallasTemperature.h>

// which pin to use for reading the sensor? can use any pin!
#define FLOWSENSORPIN1 3
#define FLOWSENSORPIN2 4
#define FLOWSENSORPIN3 5
#define FLOWSENSORPIN4 2
#define FLOWSENSORPIN5 6
#define ONE_WIRE_BUS 8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;

// count how many pulses!
volatile uint16_t pulses = 0;
volatile uint16_t pulses2 = 0;
volatile uint16_t pulses3 = 0;
volatile uint16_t pulses4 = 0;
volatile uint16_t pulses5 = 0;
// track the state of the pulse pin
volatile uint8_t lastflowpinstate;
volatile uint8_t lastflowpinstate2;
volatile uint8_t lastflowpinstate3;
volatile uint8_t lastflowpinstate4;
volatile uint8_t lastflowpinstate5;
// you can try to keep time of how long it is between pulses
volatile uint32_t lastflowratetimer = 0;
volatile uint32_t lastflowratetimer2 = 0;
volatile uint32_t lastflowratetimer3 = 0;
volatile uint32_t lastflowratetimer4 = 0;
volatile uint32_t lastflowratetimer5 = 0;
// and use that to calculate a flow rate
volatile float flowrate;
volatile float flowrate2;
volatile float flowrate3;
volatile float flowrate4;
volatile float flowrate5;
// Interrupt is called once a millisecond, looks for any pulses from the sensor!
SIGNAL(TIMER0_COMPA_vect) {
  uint8_t x = digitalRead(FLOWSENSORPIN1);

  if (x == lastflowpinstate) {
    lastflowratetimer++;
    return; // nothing changed!
  }

  if (x == HIGH) {
    //low to high transition!
    pulses++;
  }
  lastflowpinstate = x;
  flowrate = 1000.0;
  flowrate /= lastflowratetimer;  // in hertz
  lastflowratetimer = 0;
}
SIGNAL(TIMER1_COMPA_vect) {
  uint8_t x = digitalRead(FLOWSENSORPIN2);

  if (x == lastflowpinstate2) {
    lastflowratetimer2++;
    return; // nothing changed!
  }

  if (x == HIGH) {
    //low to high transition!
    pulses2++;
  }
  lastflowpinstate2 = x;
  flowrate2 = 1000.0;
  flowrate2 /= lastflowratetimer2;  // in hertz
  lastflowratetimer2 = 0;
}
SIGNAL(TIMER2_COMPA_vect) {
  uint8_t x = digitalRead(FLOWSENSORPIN3);

  if (x == lastflowpinstate3) {
    lastflowratetimer3++;
    return; // nothing changed!
  }

  if (x == HIGH) {
    //low to high transition!
    pulses3++;
  }
  lastflowpinstate3 = x;
  flowrate3 = 1000.0;
  flowrate3 /= lastflowratetimer3;  // in hertz
  lastflowratetimer3 = 0;
}
SIGNAL(TIMER3_COMPA_vect) {
  uint8_t x = digitalRead(FLOWSENSORPIN4);

  if (x == lastflowpinstate4) {
    lastflowratetimer4++;
    return; // nothing changed!
  }

  if (x == HIGH) {
    //low to high transition!
    pulses4++;
  }
  lastflowpinstate4 = x;
  flowrate4 = 1000.0;
  flowrate4 /= lastflowratetimer4;  // in hertz
  lastflowratetimer4 = 0;
}
////////

SIGNAL(TIMER4_COMPA_vect) {
  uint8_t x = digitalRead(FLOWSENSORPIN5);

  if (x == lastflowpinstate5) {
    lastflowratetimer5++;
    return; // nothing changed!
  }

  if (x == HIGH) {
    //low to high transition!
    pulses5++;
  }
  lastflowpinstate5 = x;
  flowrate5 = 1000.0;
  flowrate5 /= lastflowratetimer5;  // in hertz
  lastflowratetimer5 = 0;
}


void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
  }
}
void useInterrupt2(boolean w) {
  if (w) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK1 |= _BV(OCIE0A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK1 &= ~_BV(OCIE0A);
  }
}

void useInterrupt3(boolean x) {
  if (x) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK2 |= _BV(OCIE0A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK2 &= ~_BV(OCIE0A);
  }
}
void useInterrupt4(boolean y)
{
  if (y) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK3 |= _BV(OCIE0A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK3 &= ~_BV(OCIE0A);
  }
}
///
void useInterrupt5(boolean a)
{
  if (a) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK4 |= _BV(OCIE0A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK4 &= ~_BV(OCIE0A);
  }
}


void setup() {
  Serial.begin(9600);

  pinMode(FLOWSENSORPIN1, INPUT);
  digitalWrite(FLOWSENSORPIN1, HIGH);
  lastflowpinstate = digitalRead(FLOWSENSORPIN1);
  useInterrupt(true);
  pinMode(FLOWSENSORPIN2, INPUT);
  digitalWrite(FLOWSENSORPIN2, HIGH);
  lastflowpinstate = digitalRead(FLOWSENSORPIN2);
  useInterrupt2(true);
  pinMode(FLOWSENSORPIN3, INPUT);
  digitalWrite(FLOWSENSORPIN3, HIGH);
  lastflowpinstate = digitalRead(FLOWSENSORPIN3);
  useInterrupt3(true);
  pinMode(FLOWSENSORPIN4, INPUT);
  digitalWrite(FLOWSENSORPIN4, HIGH);
  lastflowpinstate = digitalRead(FLOWSENSORPIN4);
  useInterrupt4(true);

  pinMode(FLOWSENSORPIN5, INPUT);
  digitalWrite(FLOWSENSORPIN5, HIGH);
  lastflowpinstate = digitalRead(FLOWSENSORPIN5);
  useInterrupt5(true);
  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  // assign address manually.  the addresses below will beed to be changed
  // to valid device addresses on your bus.  device address can be retrieved
  // by using either oneWire.search(deviceAddress) or individually via
  // sensors.getAddress(deviceAddress, index)
  //insideThermometer = { 0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0 };

  // Method 1:
  // search for devices on the bus and assign based on an index.  ideally,
  // you would do this to initially discover addresses on the bus and then
  // use those addresses and manually assign them (see above) once you know
  // the devices on your bus (and assuming they don't change).
  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");

  // method 2: search()
  // search() looks for the next device. Returns 1 if a new address has been
  // returned. A zero might mean that the bus is shorted, there are no devices,
  // or you have already retrieved all of them.  It might be a good idea to
  // check the CRC to make sure you didn't get garbage.  The order is
  // deterministic. You will always get the same devices in the same order
  //
  // Must be called before search()
  //oneWire.reset_search();
  // assigns the first address found to insideThermometer
  //if (!oneWire.search(insideThermometer)) Serial.println("Unable to find address for insideThermometer");

  // show the addresses we found on the bus
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(insideThermometer, 9);

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC);
  Serial.println();

}
// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{

  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Fish Tank Temperature F: ");
  Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
}

void loop()                     // run over and over again
{
  //  Serial.print("Freq: "); Serial.println(flowrate);
  //  Serial.print("Pulses: "); Serial.println(pulses, DEC);

  // if a plastic sensor use the following calculation
  // Sensor Frequency (Hz) = 7.5 * Q (Liters/min)
  // Liters = Q * time elapsed (seconds) / 60 (seconds/minute)
  // Liters = (Frequency (Pulses/second) / 7.5) * time elapsed (seconds) / 60
  // Liters = Pulses / (7.5 * 60)
  float liters = pulses;
  liters /= 7.5;
  liters /= 60.0;
  float liters2 = pulses2;
  liters2 /= 7.5;
  liters2 /= 60.0;
  float liters3 = pulses3;
  liters3 /= 7.5;
  liters3 /= 60.0;
  float liters4 = pulses4;
  liters4 /= 7.5;
  liters4 /= 60.0;

  float liters5 = pulses5;
  liters5 /= 7.5;
  liters5 /= 60.0;
  Serial.print(liters); Serial.println("L Water Flow Sensor 1");
  Serial.print(liters2); Serial.println("L Water Flow Sensor 2");
  Serial.print(liters3); Serial.println("L Water Flow Sensor 3");
  Serial.print(liters4); Serial.println("L Water Flow Sensor 4");
  Serial.print(liters5); Serial.println("L Water Flow Sensor 5");
  pulses = 0;
  pulses2 = 0;
  pulses3 = 0;
  pulses4 = 0;
  pulses5 = 0;
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  //sensors.requestTemperatures(); // Send the command to get temperatures

  // It responds almost immediately. Let's print out the data
  // printTemperature(insideThermometer); // Use a simple function to print out the data
  delay(1000);
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
