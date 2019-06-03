#define PIEZO 9



// middle 도에서 부터 1 옥타브 음정과 주기값. 이 중에 우리가 쓸 것은 솔, 라, 미

#define c4 3822 // 261.63Hz 도
#define d4 3405 // 293.67Hz 레
#define e4 3034 // 329.63Hz 미
#define f4 2863 // 349.23Hz 파
#define g4 2551 // 392.11Hz 솔
#define g4s 2408 // 415.30Hz 솔#
#define a4 2273 // 440.11Hz 라
#define b4 2025 // 493.88Hz 시
#define c5 1910 // 523.25Hz 도
#define d5 1703 // 587.33Hz 레

#define d5s 1607 // 584.37Hz 레#
#define e5 1517 // 659.26Hz 미
#define f5 1432 // 698.46Hz 파
#define g5 1276 // 783.99Hz 솔
#define a5 1136 // 880.11Hz 라
#define b5 1012 // 987.77Hz 시


// middle 도에서 부터 1 옥타브 음정과 주기값. 이 중에 우리가 쓸 것은 솔, 라, 미
#define do0 3822 // 261Hz
#define re 3405 // 294Hz
#define mi 3034 // 329Hz
#define fa 2863 // 349Hz
#define sol 2551 // 392Hz
#define la 2273 // 440Hz
#define ti 2025 // 493Hz
#define do1 1910 // 523Hz


//int song[] = { e5, d5s, e5, d5s, e5, b4, d5, c5, a4, c4, e4, a4, b4, e4, g4s, b4, c5, e4, e5, d5s, e5, d5s, e5, b4, d5, c5, a4, c4, e4, a4, b4, e4, c5, b4, a4 };


 
void gameOverSing() { 
  pinMode(PIEZO, OUTPUT);  
  int song[] = { c4, e4, a4, b4, e4, g4s, b4, c5, e4, e5, d5s, e5, d5s, e5, b4, d5, c5, a4, c4, e4, a4, b4, e4, c5, b4, a4 };
  int i;
  for(i=0; i< 25; i++) {
    tone(PIEZO, song[i], 125);
    delay(125);
  }
}
