const int NUM_SLIDERS = 6;
const int DAMP = 6;
const int HEADER_LENGTH = 2;

const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A4, A5};

int analogSliderValues[NUM_SLIDERS];

// AA55 defined here as the header
byte messageBuf[] = { 0xAA, 0x55,
                      0, 0, // slider 0
                      0, 0, // slider 1
                      0, 0, // slider 2
                      0, 0, // slider 3
                      0, 0, // slider 4
                      0, 0, // slider 5
                    };

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }

  Serial.begin(19200);
}

void loop() {
  updateSliderValues();
  sendSliderValues();
  delay(10);
}

void updateSliderValues() {
  int newValue;
  for (int i = 0; i < NUM_SLIDERS; i++) {
    analogSliderValues[i] *= DAMP - 1;
    analogSliderValues[i] /= DAMP;
    newValue = analogRead(analogInputs[i]);
    analogSliderValues[i] += newValue;
  }
}

void sendSliderValues() {
  int offset = HEADER_LENGTH;
  for (int i = NUM_SLIDERS - 1; i >= 0; i--) 
  {
    int newValue = analogSliderValues[i] / DAMP;
    messageBuf[offset] = (newValue >> 8) & 0xFF;
    messageBuf[offset + 1] = newValue & 0xFF;

    offset += 2;
  }

  Serial.write(messageBuf, HEADER_LENGTH + NUM_SLIDERS * 2);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}
