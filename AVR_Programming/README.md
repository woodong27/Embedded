# AVR Programming

Arduino IDE를 사용해서 간단하게 AVR Programming을 실습했음<br>

<br>

## ISR_Timer

Atmega328/p의 clock cycle을 64분주하고 적절한 TOP을 설정한 뒤, 7 segment를 연결하여 타이머를 구현<br>
Interrupt Service Routine을 통해 매 시간마다 interrupt가 발생하여 원하는 동작을 실행<br>
1번(start), 2번(stop), 3번(clear), 4번(hold) 버튼을 통해 타이머 기능을 구현<br>


<br>

## LCD_Display

HITACHI사의 HD44780를 사용해서 전원이 연결되면 학번과 이름이 출력되도록 구현<br>

<br>

## LED_SwitchControl

D포트와 B포트에 LED8개와 스위치를 연결해서, 각 스위치를 누를 때 마다 LED에 다른 방식으로 불이 들어오게 구현<br>