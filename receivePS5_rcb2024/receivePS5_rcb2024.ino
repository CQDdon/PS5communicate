#include <PS5BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the PS5BT class in two ways */
// This will start an inquiry and then pair with the PS5 controller - you only have to do this once
// You will need to hold down the PS and Share button at the same time, the PS5 controller will then start to blink rapidly indicating that it is in pairing mode
PS5BT PS5(&Btd, PAIR);

// After that you can simply create the instance like so and then press the PS button on the device
//PS5BT PS5(&Btd);

bool printAngle = false, printTouch = false;
uint16_t lastMessageCounter = -1;
uint8_t player_led_mask = 0;
bool microphone_led = false;
uint32_t ps_timer;

int previousL2Value = 0;
int previousR2Value = 0;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    while (1); // Halt
  }
}

void loop() {
  Usb.Task();

  if (PS5.connected() && lastMessageCounter != PS5.getMessageCounter()) {
    lastMessageCounter = PS5.getMessageCounter();

    int currentL2Value = PS5.getAnalogButton(L2);

    // Đọc giá trị analog của R2 (trigger phải)
    int currentR2Value = PS5.getAnalogButton(R2);

    // Kiểm tra sự thay đổi của giá trị L2
    if (currentL2Value != previousL2Value) {
        Serial.print(F("L2:"));
        Serial.println(currentL2Value);
        previousL2Value = currentL2Value;  // Cập nhật giá trị trước đó của L2
    }

    // Kiểm tra sự thay đổi của giá trị R2
    if (currentR2Value != previousR2Value) {
        Serial.print(F("R2:"));
        Serial.println(currentR2Value);
        previousR2Value = currentR2Value;  // Cập nhật giá trị trước đó của R2
    }

    int leftHatX = PS5.getAnalogHat(LeftHatX);
    int leftHatY = PS5.getAnalogHat(LeftHatY);
    int rightHatX = PS5.getAnalogHat(RightHatX);
    int rightHatY = PS5.getAnalogHat(RightHatY);

    // Left Joystick
    if (leftHatX > 137 || leftHatX < 117 || leftHatY > 137 || leftHatY < 117) {
        Serial.print(F("LX:"));
        Serial.print(leftHatX);
        Serial.print(F(",LY:"));
        Serial.print(leftHatY);
        Serial.print(F("\n"));  
    }

    // Right Joystick
    if (rightHatX > 137 || rightHatX < 117 || rightHatY > 137 || rightHatY < 117) {
        Serial.print(F("RX:"));
        Serial.print(rightHatX);
        Serial.print(F(",RY:"));
        Serial.print(rightHatY);
        Serial.print(F("\n")); 
    }

    // Hold the PS button for 1 second to disconnect the controller
    // This prevents the controller from disconnecting when it is reconnected,
    // as the PS button is sent when it reconnects
    if (PS5.getButtonPress(PS)) {
      if (millis() - ps_timer > 1000)
        PS5.disconnect();
    } else
      ps_timer = millis();

    if (PS5.getButtonClick(CREATE))
    Serial.print(F("CRT\n"));
    if (PS5.getButtonClick(OPTIONS))
        Serial.print(F("OPT\n"));
    if (PS5.getButtonClick(TOUCHPAD))
        Serial.print(F("TPD\n"));
    if (PS5.getButtonClick(L1))
        Serial.print(F("L1\n"));
    if (PS5.getButtonClick(R1))
        Serial.print(F("R1\n"));
    if (PS5.getButtonClick(L3))
        Serial.print(F("L3\n"));
    if (PS5.getButtonClick(R3))
        Serial.print(F("R3\n"));
    if (PS5.getButtonClick(UP))
        Serial.print(F("DU\n"));
    if (PS5.getButtonClick(DOWN))
        Serial.print(F("DD\n"));
    if (PS5.getButtonClick(LEFT))
        Serial.print(F("DL\n"));
    if (PS5.getButtonClick(RIGHT))
        Serial.print(F("DR\n"));

    if (PS5.getButtonClick(TRIANGLE))
        Serial.print(F("GT\n"));
    if (PS5.getButtonClick(CIRCLE))
        Serial.print(F("GC\n"));
    if (PS5.getButtonClick(CROSS))
        Serial.print(F("GX\n"));
    if (PS5.getButtonClick(SQUARE))
        Serial.print(F("GS\n"));
  }
}
