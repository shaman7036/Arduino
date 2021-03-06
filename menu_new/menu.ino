/* Main.ino file generated by New Project wizard
 *
 * Created:   Thu Sep 5 2013
 * Processor: ATmega328P
 * Compiler:  Arduino AVR
 */

//Пример простого меню для Arduino
//В меню используется 4 экрана
//за номер отображаемого экрана отвечает переменная m
//Значения переменных р1,р2 меняются циклически от 0-10 затем опять 0, р3(LED) только 0 или 1 

#include <LiquidCrystal.h> //Библиотека LCD
// инициализация LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int m=0; //переменная для экранов меню
int p1=0; // переменная для переменной 1
int p2=0; // -//- 2
int p3=0; // -//- 3

byte nextPin = 6; //кнопка NEXT на 6 входе
byte prevPin = 7; //кнопка PREV
byte upPin = 9; //увеличение значения (UP) отображаемого параметра
byte downPin = 10; //уменьшение значения (DOWN)
byte ledPin =13; //Светодиод (исполнительное устройство)

long previousMillis = 0; //счетчик прошедшего времени для AutoMainScreen
long interval = 3000; //задержка автовозврата к MainScreen 3сек

void setup() {
  //Настройка входов
  pinMode(nextPin, INPUT);
  pinMode(prevPin, INPUT);
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  //Настройка выходов
  pinMode(ledPin, OUTPUT);
  //Настройка дисплея
  //Установка количества столбцов и строк дисплея
  lcd.begin(16, 2);
  // Вывод приветствия при включении питания если нужно
  lcd.setCursor(3, 0);
  lcd.print("DEMO MENU");
  delay (300);//Задержка приветствия
}

void loop() {
  unsigned long currentMillis = millis();
  //Обработка нажатия кнопки NEXT
  if (digitalRead(nextPin)== HIGH)
  {
  m++;//увеличиваем переменную уровня меню
  previousMillis = currentMillis; //если кнопка была нажата сбросить счетчик автовозврата к главному экрану
  delay (100);
  //lcd.clear();
  if (m>3)//если уровень больше 3
  {
  m=0;// то вернуться к началу
  }
  }
  //Обработка нажатия кнопки PREV
  if (digitalRead(prevPin)== HIGH)
  {
  m--;
  previousMillis = currentMillis;
  delay (100);
  //lcd.clear();
  if (m<0)
  {
  m=3;
  }
  }
  
  //Обработка нажатия UP для р1
    if (digitalRead(upPin)== HIGH && m==1)//если находимся на экране с переменной р1
  {
  p1++;      //то при нажатии кнопки + увеличиваем переменную р1 на единицу
  previousMillis = currentMillis;
  delay (100);
  //lcd.clear();
  if (p1>10) //устанавливаем придел изменения переменной = 10
  {          //если больше предела
  p1=0;      //то возвращаем ее к 0 (тут код условия что делать при достижении приделов)
  }
  }
  //UP для р2
    if (digitalRead(upPin)== HIGH && m==2)
  {
  p2++;
  previousMillis = currentMillis;
  delay (100);
  //lcd.clear();
  if (p2>10)
  {
  p2=0;
  }
  }
    //UP для р3
    if (digitalRead(upPin)== HIGH && m==3)
  {
  p3++;
  previousMillis = currentMillis;
  delay (100);
  //lcd.clear();
  if (p3>1)
  {
  p3=0;
  }
  digitalWrite(ledPin, p3);
  }
  //сдесь код для уменьшения значений
  //аналогичен коду увеличения если нужно
  
  //Вывод меню
  //Описание экранов меню
  lcd.clear();
  if (m==0)                 //переменная m=0
  {                         //отображаем
  lcd.setCursor(3, 0);      //******************* 
  lcd.print("Main Screen"); //*Main Screen      *
  lcd.setCursor(0, 1);      //*P1=p1 P2=p2 LED=0*
  lcd.print("P1=");         //*******************    
  lcd.print(p1);
  lcd.print(" P2=");
  lcd.print(p2);
  lcd.print(" LED=");
  lcd.print(p3);
  } 
  else if (m==1)            //переменная m=1
  {                         //отображаем
  lcd.setCursor(0, 0);      //*******************
  lcd.print("Parametr-1");  //*Parametr-1       *
  lcd.setCursor(0, 1);      //*P1=p1            *
  lcd.print("P1 = ");       //*******************
  lcd.print(p1);
  }
 else if (m==2)             //переменная m=2
  {                         //отображаем
  lcd.setCursor(0, 0);      //*******************
  lcd.print("Parametr-2");  //*Parametr-2       *
  lcd.setCursor(0, 1);      //*P2=p2            *
  lcd.print("P2 = ");       //*******************
  lcd.print(p2);
  }
 else if (m==3)             //переменная m=3
  {                         //отображаем
  lcd.setCursor(0, 0);      //*******************
  lcd.print("LED Control"); //LED Control       *
  lcd.setCursor(0, 1);      //LED = p3          *
  lcd.print("LED = ");      //*******************
  lcd.print(p3);
  }
  //Проверка автовозврата
  if(currentMillis - previousMillis > interval)  //Если счетчик
  {
    previousMillis = currentMillis;              //достиг интервала 
    m=0;                                         //то отобразить главный экран
    //lcd.clear();
  }
//yul-i-an@gmail.com форум allduino.forum2x2.ru
}

