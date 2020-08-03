
class Button {
  private:
    const byte pin;
    const char* name;

    byte state;
    uint32_t debounceMs;
    static const uint32_t DEBOUNCE_ms = 50;

  public:
    Button(const char *name, const byte pin) : pin(pin), name(name) {}

    void setup() {
      pinMode(pin, INPUT_PULLUP);
      Serial.print("Button ");
      Serial.print(name);
      Serial.println(" set up.");

      state = digitalRead(pin);
      debounceMs = millis();
      BUTTON_EVENTPROCESSED[pin] = true;
    }

    void loop() {
      if (millis() - debounceMs < DEBOUNCE_ms) return;
      byte prevState = state;
      state = digitalRead(pin);
      if (state != prevState) {
        debounceMs = millis();
      }

      if (state == HIGH && prevState == LOW) {
        debug( String(name) + " released");
        BUTTON_ISPRESSED[pin] = false;
        handleButtonRelease(pin, millis() - BUTTON_LASTDOWN[pin]);
      }
      else if (state == LOW && prevState == HIGH) {
        debug( String(name) + " pushed");
        BUTTON_LASTDOWN[pin] = millis();
        BUTTON_ISPRESSED[pin] = true;
        BUTTON_EVENTPROCESSED[pin] = false;
        handleButtonGoesDown(pin);
      }
      else if (state == LOW && prevState == LOW) {
        handleButtonHold(pin, millis() - BUTTON_LASTDOWN[pin]);
      }
    }
};
