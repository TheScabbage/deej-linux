const int NUM_SLIDERS = 6;
const int DAMP = 6;

const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A4, A5};

int analogSliderValues[NUM_SLIDERS];

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
  String builtString = String("");

  for (int i = NUM_SLIDERS - 1; i >= 0; i--) 
  {
    builtString += String((int)(analogSliderValues[i] / DAMP));

    if (i > 0) 
      builtString += String("|");
  }
  
  Serial.println(builtString);
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