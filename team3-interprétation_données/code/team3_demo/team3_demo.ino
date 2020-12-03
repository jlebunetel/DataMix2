
// configuration
#define LED_STRIP_PIN       8
#define LED_STRIP_LENGTH   10
#define BUTTON_PIN          5
#define SERVO_PIN           9
#define ANIMATION_DELAY  3000 // millisecondes




// MP3 Player

#include "Serial_MP3_Player.h"
MP3Player player;



// bouton

#include "button.h"
Button bouton;


// ruban de led

// HTML colors
#define COLOR_WHITE   0xFFFFFF
#define COLOR_SILVER  0xC0C0C0
#define COLOR_GRAY    0x808080
#define COLOR_BLACK   0x000000
#define COLOR_RED     0xFF0000
#define COLOR_MAROON  0x800000
#define COLOR_YELLOW  0xFFFF00
#define COLOR_OLIVE   0x808000
#define COLOR_LIME    0x00FF00
#define COLOR_GREEN   0x008000
#define COLOR_AQUA    0x00FFFF
#define COLOR_TEAL    0x008080
#define COLOR_BLUE    0x0000FF
#define COLOR_NAVY    0x000080
#define COLOR_FUCHSIA 0xFF00FF
#define COLOR_PURPLE  0x800080

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel Strip = Adafruit_NeoPixel(LED_STRIP_LENGTH, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);



// Servomoteur

#include <Servo.h>
Servo servo;



// mode d'affichage

int mode = 0;
long mode_color[] = {COLOR_RED, COLOR_PURPLE, COLOR_LIME};
int mode_position[] = {10,90,170};



void setup() {
  // MP3 Player
  player.begin();
  player.setEqualizer(EQUALIZER_NORMAL);
  player.setVolume(30);

  // bouton
  bouton.begin(BUTTON_PIN, HIGH);

  // ruban de led
  Strip.begin();
  Strip.show(); // Initialize all pixels to 'off'

  // servomoteur
  servo.attach(SERVO_PIN);
  servo.write(90); // position milieu
}

void loop() {

  bouton.read();
  if (bouton.isJustOn()) {// on appuie sur le bouton
    // on joue un son
    int folder = 1;
    int track = mode + 1;
    player.playTrack(folder, track);

    // on allume le ruban de led
    for (int i = 0 ; i < LED_STRIP_LENGTH; i++) {
      Strip.setPixelColor(i, mode_color[mode]);
    }
    Strip.show();

    // on bouge le servomoteur
    servo.write(mode_position[mode]);

    // on attend un peu
    delay(ANIMATION_DELAY);

    // on éteint le ruban de led
    for (int i = 0 ; i < LED_STRIP_LENGTH; i++) {
      Strip.setPixelColor(i, COLOR_BLACK);
    }
    Strip.show();

    // on passe au mode suivant
    mode += 1;
    if (mode > 2) {
      mode = 0;
    }
  }

  delay(1); // pour la stabilité ...
}
