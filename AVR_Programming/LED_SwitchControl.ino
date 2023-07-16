void setup() {
  DDRD=0xFF; //D포트 출력(LED)
  DDRB=0x00; //B포트 입력(스위치)
  PORTD=0xFF;
}

void loop() {
  int i=0;
  //2번
  if((PINB|0xFD)==0xFD) {
    while((PINB|0xEF)!=0xEF) {
      if(i==8) {
        PORTD=0xFF;
        i=0; 
        delay(500);
      }
      PORTD=0x7F>>i;
      i++;
      delay(500);
    }
  }
  //1번
  else if((PINB|0xFE)==0xFE) {
    while((PINB|0xEF)!=0xEF) {
      if(i==8) {
        PORTD=0xFF;
        i=0;
        delay(500);
      }
      PORTD=0xFE<<i;
      i++;
      delay(500);
    }
  }
  //대기상태
  else PORTD=0xFF;

  //5번 눌렀을때(탈출 후)
  if((PINB|0xEF)==0xEF) {
    for(int i=0;i<1;i++) {
      PORTD=0xFF;
      delay(500);
      PORTD=0x00;
      delay(500);
    }
  }
}