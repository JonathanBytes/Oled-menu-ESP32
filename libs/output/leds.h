// use 12 bit precision for LEDC timer
#define LEDC_TIMER_10_BIT 12

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ 5000

// fade LED PIN (replace with LED_BUILTIN constant for built-in LED)
#define LED1_PIN 14
#define LED2_PIN 12
#define LED3_PIN 13

bool LED_CHANGE = false;
bool LED1_ON = false;
bool LED2_ON = false;
bool LED3_ON = false;
bool prevLED1_ON = false;
bool prevLED2_ON = false;
bool prevLED3_ON = false;

bool fading = false;

// define starting duty, target duty and maximum fade time
#define LEDC_START_DUTY (0)
#define LEDC_TARGET_DUTY (256)
#define LEDC_FADE_TIME (200)

void fadeLed(int led_pin, bool LED_ON, bool prevLED_ON) {
  if (LED_ON != prevLED_ON) {
    fading = true; // Iniciamos un nuevo fade
    if (LED_ON) {
      ledcFade(led_pin, LEDC_START_DUTY, LEDC_TARGET_DUTY, LEDC_FADE_TIME);
    } else {
      ledcFade(led_pin, LEDC_TARGET_DUTY, LEDC_START_DUTY, LEDC_FADE_TIME);
    }
  }
}

void handleLeds() {
  if (LED_CHANGE && !fading) {
    // Hacer fade solo en los LEDs cuyo estado ha cambiado
    fadeLed(LED1_PIN, LED1_ON, prevLED1_ON);
    fadeLed(LED2_PIN, LED2_ON, prevLED2_ON);
    fadeLed(LED3_PIN, LED3_ON, prevLED3_ON);

    // Guardar el estado actual como el estado previo para la próxima vez
    prevLED1_ON = LED1_ON;
    prevLED2_ON = LED2_ON;
    prevLED3_ON = LED3_ON;

    LED_CHANGE = false;
  }

  // delay(LEDC_FADE_TIME);
  fading = false; // Todos los fades han terminado
}

void setupLeds() {
  // Setup timer with given frequency, resolution and attach it to a led pin
  // with auto-selected channel
  ledcAttach(LED1_PIN, LEDC_BASE_FREQ, LEDC_TIMER_10_BIT);
  ledcAttach(LED2_PIN, LEDC_BASE_FREQ, LEDC_TIMER_10_BIT);
  ledcAttach(LED3_PIN, LEDC_BASE_FREQ, LEDC_TIMER_10_BIT);
}
