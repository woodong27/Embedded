void setup() {
  DDRB=0xFF; //D1, D2, D3 선택
  DDRD=0xFF; //DP A~G
  DDRC=0x00; //button 입력 
  TCCR0A=0x02; //CTC 모드
  TCCR0B=0x03; //64분주
  OCR0A=249; //TOP=249
  TCNT0=0; //초기화
  TIMSK0=0x02; //타이머0 compare match interupt 활성화
  TIFR0=0x02;
  sei();
}

volatile int i=0;
volatile int n=0;
volatile int t=0;
volatile float c[]={0,0,0,0,0,0};
int num[]={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x72,0x7F,0x7B}; //0~9

void button() {
  if((PINC|0xFE)==0xFE) t=1; 
  else if((PINC|0xFD)==0xFD) t=2; 
  else if((PINC|0xFB)==0xFB) t=0;
}

void display(int arr[]) {
  PORTB=~(0x01<<i);
  if(i==4||i==5) {
    PORTD=arr[int(c[i]/6)];
  }
  else {
    PORTD=arr[int(c[i])];
  }
  if(i==2||i==4) {
    PORTD=PORTD|0x80;
  } 
}

ISR(TIMER0_COMPA_vect) {
  if(n==6) n=0;
  i=n++;

  if(t==1) { //1번 start
    c[0]=c[0]+0.1; c[1]=c[1]+0.01; c[2]=c[2]+0.001;
    c[3]=c[3]+0.0001; c[4]=c[4]+0.0001; c[5]=c[5]+0.00001;
    if(c[0]>=10) c[0]=0;
    if(c[1]>=10) c[1]=0;
    if(c[2]>=10) c[2]=0;
    if(c[3]>=6) c[3]=0;
    if(c[4]>=60) c[4]=0;
    if(c[5]>=36) c[4]=0; 
  }
  else if(t==2) {//2번 stop
    c[0]=c[0]; c[1]=c[1]; c[2]=c[2]; c[3]=c[3]; c[4]=c[4]; c[5]=c[5];
  }
  else {//3번 stop
    c[0]=c[1]=c[2]=c[3]=c[4]=c[5]=0;
  }
}

void loop() {
  button();
  display(num);
  while((PINC|0xF7)==0xF7) {}; //4번 hold
}
