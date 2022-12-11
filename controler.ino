#include <Adafruit_MPU6050.h>//MPU6050を動かすためのヘッダファイル
#include <Adafruit_Sensor.h>//センサそのものを動かすためのヘッダファイル
#include <Wire.h>//I2C通信の設定を定義するヘッダファイル


#define MPU6050_ADDR 0x68//mpu6050本体のアドレス
#define MPU6050_AX  0x3B
#define MPU6050_AY  0x3D
#define MPU6050_AZ  0x3F
#define MPU6050_TP  0x41    //  data not used
#define MPU6050_GX  0x43
#define MPU6050_GY  0x45
#define MPU6050_GZ  0x47
#define PI 3.14159265358979

const int vol_pin = 14;//圧力センサ用アナログピン
const int led_pin = 25;//LEDを接続するピン

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);//シリアル通信速度

 //led_pinを出力ピンに設定
  pinMode(led_pin, OUTPUT);
  
  while (!Serial)
    delay(10); //シリアルコンソールが開くまで待つ

  Serial.println("Adafruit MPU6050 test!");

  // 初期化
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");//MPU6050認識失敗
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

//加速度の感度範囲設定
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  //ジャイロの感度設定
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

//バンドパスフィルタ帯域設定
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(1000);
}

void loop() {

// アナログピンの入力値を読み込み。
  int sensorValue = analogRead(vol_pin);
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float rotY=(g.gyro.y*180/PI)+0.64;
  float rotZ=(g.gyro.z*180/PI)+0.63;

 // 読み込んだ状態をシリアルモニターに表示する文。
  Serial.print("Rotation Y: ");
  Serial.print(rotY);
  Serial.print(", Z: ");
  Serial.print(rotZ);
  Serial.println(" deg/s");
  Serial.println(sensorValue);

  Serial.println("");
  delay(10);
}
