
class Sensor {
public:
  Sensor(int triggerPin, int echoPin);
  int getDistance();

private:
  int triggerPin;
  int echoPin;
};
