// #include <Arduino.h>
// #include <SD.h>
// #include <SPI.h>
// #include <AudioFileSourceSD.h>
// #include <AudioGeneratorMP3.h>
// #include <AudioOutputI2S.h>
// #include <Adafruit_NeoPixel.h>

// #define SD_CS 5
// #define I2S_BCLK 26
// #define I2S_LRC 25
// #define I2S_DOUT 22
// #define LED_PIN 13
// #define NUM_LEDS 90

// Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
// AudioGeneratorMP3 *mp3 = NULL;
// AudioFileSourceSD *file = NULL;
// AudioOutputI2S *out = NULL;

// void setMoodLight(int r, int g, int b) {
//   for (int i = 0; i < NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(r, g, b));
//   strip.show();
// }

// void stopPlaying() {
//   if (mp3) { mp3->stop(); delete mp3; mp3 = NULL; }
//   if (file) { file->close(); delete file; file = NULL; }
// }

// void playAudio(const char *filename) {
//   stopPlaying();
//   if (!SD.exists(filename)) {
//     Serial.printf("❌ Missing: %s\n", filename);
//     return;
//   }
//   file = new AudioFileSourceSD(filename);
//   mp3 = new AudioGeneratorMP3();
//   mp3->begin(file, out);
// }

// void setup() {
//   Serial.begin(115200);
//   strip.begin();
//   strip.setBrightness(50);
//   setMoodLight(0, 0, 0);

//   SPI.begin(18, 19, 23, SD_CS);
//   if (!SD.begin(SD_CS)) {
//     Serial.println("❌ SD Mount Failed");
//     while (1);
//   }

//   out = new AudioOutputI2S();
//   out->SetPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
//   out->SetGain(1.0);
//   Serial.println("✅ Ready");
// }

// void loop() {
//   if (mp3 && mp3->isRunning()) {
//     if (!mp3->loop()) {
//       stopPlaying();
//       Serial.println("✅ Song Finished");
//       setMoodLight(0, 0, 0);
//     }
//   }

//   if (Serial.available()) {
//     String cmd = Serial.readStringUntil('\n');
//     cmd.trim();

//     if (cmd == "INTRO") { setMoodLight(255,255,255); playAudio("/intro.mp3"); }
//     else if (cmd == "ASK_HAPPY") { setMoodLight(255,200,0); playAudio("/happyq.mp3"); }
//     else if (cmd == "ASK_SAD") { setMoodLight(0,0,255); playAudio("/sadq.mp3"); }
//     else if (cmd == "PLAY_HAPPY") { setMoodLight(255,255,0); playAudio("/happy.mp3"); }
//     else if (cmd == "PLAY_SAD") { setMoodLight(0,0,100); playAudio("/sad.mp3"); }
//     else if (cmd == "SAY_QUIET") { setMoodLight(20,20,20); playAudio("/response.mp3"); }
//     else if (cmd == "ASK_SURPRISED") { setMoodLight(0,0,150); playAudio("/surprisedq.mp3"); }
//     else if (cmd == "PLAY_SURPRISED") { setMoodLight(0,0,100); playAudio("/surprised.mp3"); }
//     else if (cmd == "ASK_ANGRY") { setMoodLight(0,0,150); playAudio("/angryq.mp3"); }
//     else if (cmd == "PLAY_ANGRY") { setMoodLight(0,0,100); playAudio("/angry.mp3"); }
//     else if (cmd == "STOP") { stopPlaying(); setMoodLight(0,0,0); }
//   }
// }









#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>
#include <Adafruit_NeoPixel.h>

#define SD_CS 5
#define I2S_BCLK 26
#define I2S_LRC 25
#define I2S_DOUT 22
#define LED_PIN 13
#define NUM_LEDS 90

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
AudioGeneratorMP3 *mp3 = NULL;
AudioFileSourceSD *file = NULL;
AudioOutputI2S *out = NULL;

void setMoodLight(int r, int g, int b) {
  for (int i = 0; i < NUM_LEDS; i++) strip.setPixelColor(i, strip.Color(r, g, b));
  strip.show();
}

void stopPlaying() {
  if (mp3) { mp3->stop(); delete mp3; mp3 = NULL; }
  if (file) { file->close(); delete file; file = NULL; }
}

void playAudio(const char *filename) {
  stopPlaying();
  if (!SD.exists(filename)) {
    Serial.printf("❌ Missing: %s\n", filename);
    return;
  }
  file = new AudioFileSourceSD(filename);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(file, out);
  Serial.printf("🎵 Playing: %s\n", filename);
}

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(50);
  setMoodLight(0, 0, 0);

  SPI.begin(18, 19, 23, SD_CS);
  if (!SD.begin(SD_CS)) {
    Serial.println("❌ SD Mount Failed");
    while (1);
  }

  out = new AudioOutputI2S();
  out->SetPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  out->SetGain(0.8);
  Serial.println("✅ System Ready");
}

void loop() {
  if (mp3 && mp3->isRunning()) {
    if (!mp3->loop()) {
      stopPlaying();
      Serial.println("✅ Song Finished");
      setMoodLight(0, 0, 0);
    }
  }

  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    // EMOTION: HAPPY (Yellow/Orange)
    if (cmd == "ASK_HAPPY") { setMoodLight(255,150,0); playAudio("/happyq.mp3"); }
    else if (cmd == "PLAY_HAPPY") { setMoodLight(255,200,0); playAudio("/happy.mp3"); }
    
    // EMOTION: SAD (Blue)
    else if (cmd == "ASK_SAD") { setMoodLight(0,0,255); playAudio("/sadq.mp3"); }
    else if (cmd == "PLAY_SAD") { setMoodLight(0,0,150); playAudio("/sad.mp3"); }
    
    // EMOTION: ANGRY (Red)
    else if (cmd == "ASK_ANGRY") { setMoodLight(255,0,0); playAudio("/angryq.mp3"); }
    else if (cmd == "PLAY_ANGRY") { setMoodLight(150,0,0); playAudio("/angry.mp3"); }

    // EMOTION: SURPRISED (Purple)
    else if (cmd == "ASK_SURPRISED") { setMoodLight(200,0,200); playAudio("/surprisedq.mp3"); }
    else if (cmd == "PLAY_SURPRISED") { setMoodLight(150,0,150); playAudio("/surprised.mp3"); }

    // OTHER COMMANDS
    else if (cmd == "INTRO") { setMoodLight(255,255,255); playAudio("/intro.mp3"); }
    else if (cmd == "SAY_QUIET") { setMoodLight(20,20,20); playAudio("/response.mp3"); }
    else if (cmd == "STOP") { stopPlaying(); setMoodLight(0,0,0); }
  }
}