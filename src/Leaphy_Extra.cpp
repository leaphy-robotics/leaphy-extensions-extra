#include "Leaphy_Extra.h"

float getDistanceSonar(int trigPin, int echoPin)
{
    float duration, distance;
    int tries = 0;

    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH, 30000);
    distance = 0.034 * duration / 2;
    if(distance == 0 ){
      distance = distance + 1313;
    }

    return distance;
}