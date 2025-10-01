// Open loop motor control example
 #include <SimpleFOC.h>

// ============================ 핀 매핑 설정 ============================
// DRV8302 보드 핀 연결 (기본 예시)
#define INH_A    14     // 하이사이드 PWM A
#define INH_B    27     // 하이사이드 PWM B
#define INH_C    26     // 하이사이드 PWM C
#define EN_GATE  13     // 드라이버 활성화
#define M_PWM    33     // 3pwm 모드 설정
#define M_OC     25     // 오버커런트 보호
#define OC_ADJ   32     // 오버커런트 조정
#define OC_GAIN  5      // DRV8302 내부 증폭기 게인 선택 핀

// 로사이드 전류 센싱 핀 (ESP32 ADC 핀)
#define IOUTA 4         // ADC2_CH0
#define IOUTB 12        // ADC2_CH5
#define IOUTC 15        // ADC2_CH3

// ============================= 모터, 드라이버, 센서 =============================

// 1) 모터 객체
//  - BLDCMotor( pole_pairs ): pole_pairs = 극수(pole) / 2
//  - 예: 22극 모터 -> pole_pairs=11
BLDCMotor motor = BLDCMotor(21);

// 2) 드라이버 객체
BLDCDriver3PWM driver = BLDCDriver3PWM(INH_A, INH_B, INH_C, EN_GATE);

// 3) 로사이드 전류센싱
//  - 샨트저항: 0.005Ω
//  - 증폭기 게인: 12.22 V/V (DRV8302 내부 증폭 + 외부 회로에 따라 측정)
LowsideCurrentSense cs = LowsideCurrentSense(0.005f, 12.22f, IOUTA, IOUTB, IOUTC);

// 4) 엔코더 (AS5600 I2C 예시)
MagneticSensorI2C encoder = MagneticSensorI2C(AS5600_I2C);

// 5) 시리얼 커맨드 인터페이스
Commander command = Commander(Serial);
// void onMotor(char* cmd) { command.motor(&motor, cmd); }

//target variable
float target_position = 0;

// instantiate the commander
void doTarget(char* cmd) { command.scalar(&target_position, cmd); }
void doLimit(char* cmd) { command.scalar(&motor.voltage_limit, cmd); }
void doVelocity(char* cmd) { command.scalar(&motor.velocity_limit, cmd); }

void setup() {

  // use monitoring with serial 
  Serial.begin(115200);
  // enable more verbose output for debugging
  // comment out if not needed
  SimpleFOCDebug::enable(&Serial);

    // ========== DRV8302 관련 핀 설정 ==========
  pinMode(M_OC, OUTPUT);
  digitalWrite(M_OC, LOW);
  pinMode(M_PWM, OUTPUT);
  digitalWrite(M_PWM, HIGH);
  pinMode(OC_ADJ, OUTPUT);
  digitalWrite(OC_ADJ, HIGH);
  pinMode(OC_GAIN, OUTPUT);
  digitalWrite(OC_GAIN, LOW); // LOW 상태에서 특정 게인 (약 10~12배)


  // driver config
  // power supply voltage [V]
  driver.voltage_power_supply = 12;
  // limit the maximal dc voltage the driver can set
  // as a protection measure for the low-resistance motors
  // this value is fixed on startup
  driver.voltage_limit = 6;
  if(!driver.init()){
    Serial.println("Driver init failed!");
    return;
  }
  // link the motor and the driver
  motor.linkDriver(&driver);

  // limiting motor movements
  // limit the voltage to be set to the motor
  // start very low for high resistance motors
  // currnet = resistance*voltage, so try to be well under 1Amp
  motor.voltage_limit = 3;   // [V]
  // limit/set the velocity of the transition in between 
  // target angles
  motor.velocity_limit = 5; // [rad/s] cca 50rpm
  // open loop control config
  motor.controller = MotionControlType::angle_openloop;

  // init motor hardware
  if(!motor.init()){
    Serial.println("Motor init failed!");
    return;
  }

  // add target command T
  command.add('T', doTarget, "target angle");
  command.add('L', doLimit, "voltage limit");
  command.add('V', doLimit, "movement velocity");

  Serial.println("Motor ready!");
  Serial.println("Set target position [rad]");
  _delay(1000);
}

void loop() {
  // open  loop angle movements
  // using motor.voltage_limit and motor.velocity_limit
  // angles can be positive or negative, negative angles correspond to opposite motor direction
  motor.move(target_position);
  
  // user communication
  command.run();
}