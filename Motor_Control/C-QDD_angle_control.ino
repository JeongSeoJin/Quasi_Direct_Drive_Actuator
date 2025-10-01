/**
 *
 * Position/angle motion control example
 * Steps:
 * 1) Configure the motor and magnetic sensor
 * 2) Run the code
 * 3) Set the target angle (in radians) from serial terminal
 *
 */
#include <SimpleFOC.h>

// magnetic sensor instance - SPI
// MagneticSensorSPI sensor = MagneticSensorSPI(AS5147_SPI, 10);
// magnetic sensor instance - MagneticSensorI2C
MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
// magnetic sensor instance - analog output
// MagneticSensorAnalog sensor = MagneticSensorAnalog(A1, 14, 1020);

// BLDC motor & driver instance
BLDCMotor motor = BLDCMotor(21);
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
#define IOUTC 15        // ADC2_CH3// Stepper motor & driver instance
//StepperMotor motor = StepperMotor(50);
//StepperDriver4PWM driver = StepperDriver4PWM(9, 5, 10, 6,  8);

BLDCDriver3PWM driver = BLDCDriver3PWM(INH_A, INH_B, INH_C, EN_GATE);


// angle set point variable
float target_angle = 0;
// instantiate the commander
Commander command = Commander(Serial);
void doTarget(char* cmd) { command.scalar(&target_angle, cmd); }

void setup() {

  // use monitoring with serial 
  Serial.begin(115200);
  // enable more verbose output for debugging
  // comment out if not needed
  SimpleFOCDebug::enable(&Serial);

  pinMode(M_OC, OUTPUT);
  digitalWrite(M_OC, LOW);
  pinMode(M_PWM, OUTPUT);
  digitalWrite(M_PWM, HIGH);
  pinMode(OC_ADJ, OUTPUT);
  digitalWrite(OC_ADJ, HIGH);
  pinMode(OC_GAIN, OUTPUT);
  digitalWrite(OC_GAIN, LOW); // LOW 상태에서 특정 게인 (약 10~12배)


  // initialise magnetic sensor hardware
  sensor.init();
  // link the motor to the sensor
  motor.linkSensor(&sensor);

  // driver config
  // power supply voltage [V]
  driver.voltage_power_supply = 24; 
  driver.init();
  // link the motor and the driver
  motor.linkDriver(&driver);

  motor.voltage_sensor_align = 0.5f; // [V]

  // choose FOC modulation (optional)
  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;

  // set motion control loop to be used
  motor.controller = MotionControlType::angle;

  // contoller configuration
  // default parameters in defaults.h

  // velocity PI controller parameters
  motor.PID_velocity.P = 0.2f;
  motor.PID_velocity.I = 0;
  motor.PID_velocity.D = 0;
  // maximal voltage to be set to the motor
  motor.voltage_limit = 10;

  // velocity low pass filtering time constant
  // the lower the less filtered
  motor.LPF_velocity.Tf = 0.01f;

  // angle P controller
  motor.P_angle.P = 4;
  // maximal velocity of the position control
  motor.velocity_limit = 25;
  
  // comment out if not needed
  motor.useMonitoring(Serial);


  // initialize motor
  motor.init();
  // align sensor and start FOC
  motor.initFOC();

  // add target command T
  command.add('T', doTarget, "target angle");

  Serial.println(F("Motor ready."));
  Serial.println(F("Set the target angle using serial terminal:"));
  _delay(1000);
}


void loop() {

  // main FOC algorithm function
  // the faster you run this function the better
  // Arduino UNO loop  ~1kHz
  // Bluepill loop ~10kHz
  motor.loopFOC();

  // Motion control function
  // velocity, position or voltage (defined in motor.controller)
  // this function can be run at much lower frequency than loopFOC() function
  // You can also use motor.move() and set the motor.target in the code
  motor.move(target_angle);


  // function intended to be used with serial plotter to monitor motor variables
  // significantly slowing the execution down!!!!
  // motor.monitor();

  // user communication
  command.run();
}