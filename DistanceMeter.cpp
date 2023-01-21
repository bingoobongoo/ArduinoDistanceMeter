#include <LiquidCrystal.h>
#define ledPin 10
#define buzzPin 11
#define trigPin 12
#define echoPin 13

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int cm;
long czas;

void pomiarOdleglosci()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    digitalWrite(echoPin, HIGH);

    czas = pulseIn(echoPin, HIGH);
    cm = czas / 58;
}

void sygnalOn(int duration)
{
    if (duration<=0 || duration > 100) return 0;
    for (int i=1; i<=100/duration; i++)
    {
        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzPin, HIGH);
        delay(10);
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzPin, LOW);
        delay(duration*10);
    }

}

void setup()
{
    lcd.begin(16, 2);

    pinMode(ledPin, OUTPUT);
    pinMode(buzzPin, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    digitalWrite(ledPin, LOW);
    digitalWrite(buzzPin, LOW);
    digitalWrite(trigPin, LOW);
    digitalWrite(echoPin, LOW);
}

void loop()
{
    pomiarOdleglosci();
    while (cm>100)
        pomiarOdleglosci();
    lcd.setCursor(0, 0);
    lcd.print("Odleglosc: ");
    lcd.setCursor(0, 1);
    lcd.print(cm);
    lcd.print(" cm");
    sygnalOn(cm);
    lcd.clear();
}