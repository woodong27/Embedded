//PD0~7 : D0~7
//PB0~3 : RS, RW, E

int busycheck() {
  DDRD=0x00;
  int AC;
  PORTB=(PORTB&0xFC)|0x02; //RW=1, RS=0
  delay(1);
  PORTC=PORTC|0x04; //Enable=1
  delay(1);
  while((PIND&0x80)==0x00) { //busy이면 loop
    AC=PIND&0x7F;
  }
  PORTC=PORTC&0xFB; //Enable=0
  DDRD=0xFF;
  return AC;
}

void enable() {
  delay(1);
  PORTB=PORTB|0x04; //Enable on
  delay(1);
  PORTB=PORTB&0xFB; //Enable off
}

void initializing() {
  busycheck();
  PORTB=PORTB&0xFC; //RW, RS=0
  PORTD=0x02; //return home
  enable();

  busycheck();
  PORTB=PORTB&0xFC; //RW, RS=0
  PORTD=0x01; //display clear
  enable();

  busycheck();
  PORTB=PORTB&0xFC; //RW, RS=0
  PORTD=0x3A; //D6=1, DL=1(8bit), N=1(2line), F=0(5*8 dots) : function set
  enable();

  busycheck();
  PORTB=PORTB&0xFC; //RW, RS=0
  PORTD=0x0C; //D3=1, D=1(display on), C=0(cursor x), B=0(blink x)
  enable();

  busycheck();
  PORTB=PORTB&0xFC; //RW, RS=0
  PORTD=0x06; //D2=1, I/D=1(increment mode), S=0(shift x)
  enable();
}

void cursor_display_shift() {
  busycheck();
  PORTB=PORTB&0xFC; //RW, RS=0
  PORTD=0x1C; //SC=1(display shift on) RL=1(Shift to right)
  enable();
}

void setDDRAM(int ADD) {
  busycheck();
  PORTB=PORTB&0xFC; //RW, RS=0
  PORTD=0x80|ADD;
  enable();
}

void setCGRAM(int ACG) {
  busycheck();
  PORTB=PORTB&0xFC; //RW, RS=0
  PORTD=0x40|ACG;
  enable();
}

void write(int a) {
  busycheck();
  PORTB=(PORTB&0xFC)|0x01; //RS=1, Rw=0
  PORTD=a;
  enable();
}

void write_Kor_Name() {
  setCGRAM(0x00); //CGRAM address
  //최
  write(0x09); //0b 0000 1001
  write(0x1D); //0b 0001 1101
  write(0x09); //0b 0000 1001
  write(0x15); //0b 0001 0101
  write(0x01); //0b 0000 0001
  write(0x09); //0b 0000 1001
  write(0x1D); //0b 0001 1101
  write(0x00); //0b 0000 0000
  //동
  write(0x0E);// 0b 0000 1110
  write(0x08);// 0b 0000 1000
  write(0x0E);// 0b 0000 1110
  write(0x04);// 0b 0000 0100
  write(0x1F);// 0b 0001 1111
  write(0x00);// 0b 0000 0000  
  write(0x04);// 0b 0000 0100
  write(0x00);// 0b 0000 0000
  //우
  write(0x04); //0b 0000 0100
  write(0x0A); //0b 0000 1010
  write(0x04); //0b 0000 0100
  write(0x00); //0b 0000 0000
  write(0x1F); //0b 0001 1111
  write(0x04); //0b 0000 0100
  write(0x04); //0b 0000 0100
  write(0x00); //0b 0000 0000
}


void display() {
  setDDRAM(0x00); //첫번째 줄
  write(0x45); //E
  write(0x49); //I
  write(0x45); //E
  write(0x4E); //N
  write(0x20); //빈칸
  write(0x32); //2
  write(0x30); //0
  write(0x31); //1
  write(0x36); //6
  write(0x32); //2
  write(0x37); //7
  write(0x30); //0
  write(0x34); //4
  write(0x32); //2
  write(0x39); //9

  setDDRAM(0x40); //두번째 줄 
  write(0x43); //C
  write(0x48); //H
  write(0x4F); //O
  write(0x49); //I
  write(0x20); //빈칸
  write(0x44); //D
  write(0x4F); //O
  write(0x4E); //N
  write(0x47); //G
  write(0x57); //W
  write(0x4F); //O
  write(0x4F); //O
  write(0x20); //빈칸
  write(0x00); //최
  write(0x01); //동
  write(0x02); //우
  }


void setup() {
  DDRD=0xFF;
  DDRB=0xFF;
  delay(1000); //켜지는거 대기
  initializing(); //초기화(기본설정)
  write_Kor_Name(); 
  display();
}

void loop() {

}