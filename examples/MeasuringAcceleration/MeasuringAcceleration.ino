// 获取三轴加速度计ADXL335值

#include <ADXL335/ADXL335.h>

ADXL335 accelerometer;

void setup()
{
    Serial.begin(115200);
    accelerometer.begin();  // 初始化加速度计
}
void loop()
{
    int x,y,z;
    accelerometer.getXYZ(&x,&y,&z);         // 获取三轴加速度计上的模拟值
    Serial.println("value of X/Y/Z: ");
    Serial.println(x);
    Serial.println(y);
    Serial.println(z);
    float ax,ay,az;
    accelerometer.getAcceleration(&ax,&ay,&az);   // 获取三轴加速度值
    Serial.println("accleration of X/Y/Z: ");
    Serial.print(ax);
    Serial.println(" g");
    Serial.print(ay);
    Serial.println(" g");
    Serial.print(az);
    Serial.println(" g");
    delay(500);
}
