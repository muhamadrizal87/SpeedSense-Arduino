#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttons[] = {2, 3, 4};
const int leds[] = {8, 9, 10};
const int buzzer = 11;

int score = 0;
int gameSpeed = 1000; 
bool gameRunning = false;
int gameMode = 0; // 1: Latihan, 2: Lomba

// Nada lagu Happy Birthday
int melody[] = {
  262, 262, 294, 262, 349, 330,      
  262, 262, 294, 262, 392, 349,      
  262, 262, 523, 440, 349, 330, 294, 
  466, 466, 440, 349, 392, 349       
};
int durations[] = {
  8, 8, 4, 4, 4, 2,
  8, 8, 4, 4, 4, 2,
  8, 8, 4, 4, 4, 4, 4,
  8, 8, 4, 4, 4, 2
};

void setup() {
  lcd.init();
  lcd.backlight();
  for (int i = 0; i < 3; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
  pinMode(buzzer, OUTPUT);
  showMenu();
}

void loop() {
  if (!gameRunning) {
    // MENU UTAMA
    if (digitalRead(buttons[0]) == LOW) { // TOMBOL KIRI
      gameMode = 1; 
      delay(200); 
      startGame(); 
    }
    if (digitalRead(buttons[1]) == LOW) { // TOMBOL TENGAH
      gameMode = 2; 
      delay(200); 
      selectLevel(); // Masuk ke pemilihan level
    }
    if (digitalRead(buttons[2]) == LOW) { // TOMBOL KANAN
      delay(200);
      playMusicOnly(); 
    }
  } else {
    // FITUR EXIT: Pencet 3 tombol bareng selama 3 detik
    if (digitalRead(buttons[0]) == LOW && digitalRead(buttons[1]) == LOW && digitalRead(buttons[2]) == LOW) {
      checkExit();
    }
    if (gameRunning) playGame(); 
  }
}

// FUNGSI BARU: PILIH LEVEL UNTUK MODE RANK
void selectLevel() {
  lcd.clear();
  lcd.print("1=ROMAWI 2=GLORY");
  lcd.setCursor(0, 1);
  lcd.print("3=IMMORTAL");
  
  while (true) {
    if (digitalRead(buttons[0]) == LOW) { gameSpeed = 1200; break; } // Level 1 (Slow)
    if (digitalRead(buttons[1]) == LOW) { gameSpeed = 800; break; }  // Level 2 (Medium)
    if (digitalRead(buttons[2]) == LOW) { gameSpeed = 450; break; }  // Level 3 (Dewa)
  }
  delay(200);
  startGame();
}

void checkExit() {
  unsigned long holdTime = millis();
  while (digitalRead(buttons[0]) == LOW && digitalRead(buttons[1]) == LOW && digitalRead(buttons[2]) == LOW) {
    if (millis() - holdTime > 3000) { 
      lcd.clear();
      lcd.print("   EXITING...   ");
      tone(buzzer, 1500, 500);
      delay(1000);
      showMenu();
      break;
    }
  }
}

void showMenu() {
  gameRunning = false;
  digitalWrite(leds[0], LOW); digitalWrite(leds[1], LOW); digitalWrite(leds[2], LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1=CLASSIC 2=RANK");
  lcd.setCursor(0, 1);
  lcd.print(" 3= MUSIK ULTAH ");
}

void playMusicOnly() {
  lcd.clear();
  lcd.print(" SELAMAT HARI ");
  lcd.setCursor(0, 1);
  lcd.print(" BROJOL SAYANG ");
  
  for (int i = 0; i < 3; i++) digitalWrite(leds[i], HIGH);
  for (int i = 0; i < 25; i++) {
    int duration = 1000 / durations[i];
    tone(buzzer, melody[i], duration);
    delay(duration * 1.30);
    noTone(buzzer);
    if (digitalRead(buttons[2]) == LOW && i > 2) break; 
  }
  showMenu();
}

void startGame() {
  score = 0;
  // Jika Classic, speed default 1000. Jika Rank, sudah diatur di selectLevel.
  if(gameMode == 1) gameSpeed = 1000; 
  
  gameRunning = true;
  lcd.clear();
  if(gameMode == 1) lcd.print("MODE: CLASSIC");
  else lcd.print("MODE: RANK");
  delay(1000);
  lcd.clear();
  lcd.print("GASKAN CUY!");
  delay(500);
}

void playGame() {
  int target = random(0, 3);
  digitalWrite(leds[target], HIGH);
  
  lcd.setCursor(0, 0);
  lcd.print("Score: "); lcd.print(score);
  lcd.setCursor(0, 1);
  if(gameMode == 2) {
    lcd.print("Tersisa: "); lcd.print(20 - score); 
  } else {
    lcd.print("EXIT=TEKAN BARENG"); 
  }

  unsigned long startTime = millis();
  bool hit = false;
  bool wrong = false;

  while (millis() - startTime < gameSpeed) {
    for (int i = 0; i < 3; i++) {
      if (digitalRead(buttons[i]) == LOW) {
        if (i == target) { hit = true; break; } 
        else { wrong = true; break; }
      }
    }
    if (hit || wrong) break;
  }

  digitalWrite(leds[target], LOW);

  if (hit) {
    score++;
    tone(buzzer, 1000, 100); 
    if (gameMode == 2 && score >= 20) { youWin(); return; }
    
    if (score % 4 == 0) {
      gameSpeed = max(200, gameSpeed - 100);
      if(gameMode == 2) {
        lcd.setCursor(0,1);
        lcd.print(" SPEED UP!!     ");
        delay(300);
      }
    } else {
      gameSpeed = max(200, gameSpeed - 15);
    }
    delay(200); 
  } else if (wrong || (millis() - startTime >= gameSpeed)) {
    if (gameMode == 2) gameOver();
    else { tone(buzzer, 150, 100); delay(200); }
  }
}

void youWin() {
  gameRunning = false;
  lcd.clear();
  lcd.print(" CONGRATS BOY! ");
  lcd.setCursor(0, 1);
  lcd.print(" MENANG CUY ");
  for (int i = 0; i < 3; i++) digitalWrite(leds[i], HIGH);
  for (int i = 0; i < 25; i++) {
    int duration = 1000 / durations[i];
    tone(buzzer, melody[i], duration);
    delay(duration * 1.30);
    noTone(buzzer);
  }
  delay(2000);
  showMenu();
}

void gameOver() {
  gameRunning = false;
  tone(buzzer, 150, 600);
  lcd.clear();
  lcd.print(" KALAH JIR :( ");
  lcd.setCursor(0, 1);
  lcd.print("Score: "); lcd.print(score);
  delay(3000);
  showMenu();
}