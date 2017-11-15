// 校准加速度计，通过Serial输出建议的参数，这个参数需要写入ADX335.h相应的宏里

#include <ADXL335.h>

void calibrate(int* _x,int* _y,int* _z);
int zero_x;
int zero_y;
int zero_z;
int max_x,max_y,max_z;
float sensitivity;
ADXL335 accelerometer;

void setup()
{
    Serial.begin(115200);
    accelerometer.begin(); // 初始化
    int x,y,z;
    for(int i = 0;i < 20; i++)
    {
        accelerometer.getXYZ(&x,&y,&z);
    }
    Serial.println("The calibration starts: ");
    Serial.println("First, make sure that Z-axis direction is straight up");    // 提示加速度计z轴向上
    Serial.println("please type any charactor if you are ready");
    while(Serial.available() == 0);
    delay(100);
    while(Serial.available() > 0) Serial.read();
    calibrate(&x,&y,&z);
    zero_x = x;
    zero_y = y;
    max_z = z;
    Serial.println("Second, make sure that X-axis direction is straight up");   // 提示加速度计x轴向上
    Serial.println("please type any charactor again if you are ready");
    while(Serial.available() == 0);
    delay(100);
    while(Serial.available() > 0)Serial.read();
    calibrate(&x,&y,&z);
    zero_z = z;
    float zero_xv,zero_yv,zero_zv;
    zero_xv = (float)zero_x*ADC_REF/ADC_AMPLITUDE;                                  // 加速度计转换
    zero_yv = (float)zero_y*ADC_REF/ADC_AMPLITUDE;
    zero_zv = (float)zero_z*ADC_REF/ADC_AMPLITUDE;
    sensitivity =(float)(max_z - zero_z)*ADC_REF/ADC_AMPLITUDE;
    Serial.print("ZERO_X = ");                                                   // 输出相应的加速度校准参数信息
    Serial.println(zero_xv);
    Serial.print("ZERO_Y = ");
    Serial.println(zero_yv);
    Serial.print("ZERO_Z = ");
    Serial.println(zero_zv);
    Serial.print("SENSITIVITY = ");
    Serial.println(sensitivity,2);
    Serial.println("please modified the macro definitions with these results in ADXL335.h");
}

void loop()
{

}

void calibrate(int* _x,int* _y,int* _z)
{
    int x,y,z;
    int sum_x,sum_y,sum_z;
    accelerometer.getXYZ(&x,&y,&z);
    float ax,ay,az;
    accelerometer.getAcceleration(&ax,&ay,&az);
    if((abs(ax) < 0.06)&&(abs(ay) < 0.06))
    {

        *_x = x;
        *_y = y;
        *_z = z;
    }
    else if((abs(ax) < 0.06)&&(abs(az) < 0.06))
    {
        *_x = x;
        *_y = y;
        *_z = z;
    }
    else if((abs(az) < 0.06)&&(abs(ay) < 0.06))
    {
        *_x = x;
        *_y = y;
        *_z = z;
    }
    else Serial.println("calibrate error");
}
