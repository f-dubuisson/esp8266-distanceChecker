
class Sensor {
public:
  Sensor(int triggerPin, int echoPin);
  float getDistance();

private:
  int triggerPin;
  int echoPin;
};
