//
//    FILE: i2cEncoderLibV2.h
// VERSION: 0.1..
// PURPOSE: Libreary for the i2c encoder board with arduinp
// LICENSE: GPL v3 (http://www.gnu.org/licenses/gpl.html)
//
// DATASHEET:
//
//     URL:
//
// AUTHOR:
// Simone Caron
//

#ifndef i2cEncoderLibV2_H
#define i2cEncoderLibV2_H

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

/*Encoder register definition*/
enum I2C_Register {
  REG_GCONF   =  0x00,
  REG_GP1CONF  = 0x01,
  REG_GP2CONF   = 0x02,
  REG_GP3CONF  = 0x03,
  REG_INTCONF  = 0x04,
  REG_ESTATUS  = 0x05,
  REG_I2STATUS = 0x06,
  REG_FSTATUS  = 0x07,
  REG_CVALB4  = 0x08,
  REG_CVALB3  = 0x09,
  REG_CVALB2  = 0x0A,
  REG_CVALB1  = 0x0B,
  REG_CMAXB4  = 0x0C,
  REG_CMAXB3  = 0x0D,
  REG_CMAXB2  = 0x0E,
  REG_CMAXB1  = 0x0F,
  REG_CMINB4  = 0x10,
  REG_CMINB3  = 0x11,
  REG_CMINB2  = 0x12,
  REG_CMINB1  = 0x13,
  REG_ISTEPB4 = 0x14,
  REG_ISTEPB3 = 0x15,
  REG_ISTEPB2 = 0x16,
  REG_ISTEPB1 = 0x17,
  REG_RLED    = 0x18,
  REG_GLED = 0x19,
  REG_BLED = 0x1A,
  REG_GP1REG = 0x1B,
  REG_GP2REG = 0x1C,
  REG_GP3REG = 0x1D,
  REG_ANTBOUNC = 0x1E,
  REG_DPPERIOD = 0x1F,
  REG_FADERGB  = 0x20,
  REG_FADEGP = 0x21,
  REG_EEPROMS  = 0x80,
};

/* Encoder configuration bit. Use with GCONF */
enum GCONF_PARAMETER {
  FLOAT_DATA  = 0x01,
  INT_DATA  = 0x00,

  WRAP_ENABLE = 0x02,
  WRAP_DISABLE = 0x00,

  DIRE_LEFT = 0x04,
  DIRE_RIGHT  = 0x00,

  IPUP_DISABLE =  0x08,
  IPUP_ENABLE = 0x00,

  RMOD_X2 = 0x10,
  RMOD_X1 = 0x00,

  RGB_ENCODER = 0x20,
  STD_ENCODER = 0x00,

  EEPROM_BANK1 =  0x40,
  EEPROM_BANK2 =  0x00,
  
  RESET =  0x80,
};

/* Encoder status bits and setting. Use with: INTCONF for set and with ESTATUS for read the bits  */
enum Int_Status {
  PUSHR = 0x01,
  PUSHP = 0x02,
  PUSHD = 0x04,
  RINC  = 0x08,
  RDEC  = 0x10,
  RMAX  = 0x20,
  RMIN  = 0x40,
  INT2  = 0x80,
};

/* Encoder Int2 bits. Use to read the bits of I2STATUS  */
enum Int2_Status {
  GP1_POS  = 0x01,
  GP1_NEG  = 0x02,
  GP2_POS  = 0x04,
  GP2_NEG  = 0x08,
  GP3_POS  = 0x10,
  GP3_NEG  = 0x20,
  FADE_INT = 0x40,
};

/* Encoder Fade status bits. Use to read the bits of FSTATUS  */
enum Fade_Status {
  FADE_R = 0x01,
  FADE_G = 0x02,
  FADE_B = 0x04,
  FADES_GP1 = 0x08,
  FADES_GP2 = 0x10,
  FADES_GP3 = 0x20,
};

/* GPIO Configuration. Use with GP1CONF,GP2CONF,GP3CONF */
enum GP_PARAMETER {
  GP_PWM = 0x00,
  GP_OUT = 0x01,
  GP_AN = 0x02,
  GP_IN = 0x03,

  GP_PULL_EN = 0x04,
  GP_PULL_DI = 0x00,

  GP_INT_DI = 0x00,
  GP_INT_PE = 0x08,
  GP_INT_NE = 0x10,
  GP_INT_BE = 0x18,
};


/* Interrupt source for the callback. Use with attachInterrupt */
enum SourceInt {
  BUTTON_RELEASE,
  BUTTON_PUSH,
  BUTTON_DOUBLE_PUSH,
  ENCODER_INCREMENT,
  ENCODER_DECREMENT,
  ENCODER_MAX,
  ENCODER_MIN,
  GP1_POSITIVE,
  GP1_NEGATIVE,
  GP2_POSITIVE,
  GP2_NEGATIVE,
  GP3_POSITIVE,
  GP3_NEGATIVE,
  FADE,
  SOURCE_INT_NUMB,
};


union Data_v {
  float fval;
  int32_t val;
  uint8_t bval[4];
};

class i2cEncoderLibV2
{
  public:

    uint8_t id = 0x00;
    typedef void (*InterruptFunction) (i2cEncoderLibV2* , SourceInt);

    /** Configuration function **/
    i2cEncoderLibV2(uint8_t add);
	void begin( uint8_t conf);
    void reset(void);
    
    /** Configuration of callback **/
    void attachInterrupt(InterruptFunction function, SourceInt event );
    void deattachInterrupt(SourceInt event );
    void autoconfigInterrupt(void);

    /**    Read functions   **/
    uint8_t readGP1conf(void);
    uint8_t readGP2conf(void);
    uint8_t readGP3conf(void);
    uint8_t readInterruptConfig(void);

    /** Status function **/
    bool updateStatus(void);
    bool readStatus(Int_Status s);
    uint8_t readStatus(void);

    bool readInt2(Int2_Status s);
    uint8_t readInt2(void);

    bool readFadeStatus(Fade_Status s);
    uint8_t readFadeStatus(void);

    /** Encoder functions **/
    float readCounterFloat(void);
    int32_t readCounterLong(void);
    int16_t readCounterInt(void);
    int8_t readCounterByte(void);

    int32_t readMax(void);
    float readMaxFloat(void);

    int32_t readMin(void);
    float readMinFloat(void);

    int32_t readStep(void);
    float readStepFloat(void);

    /** RGB LED Functions **/
    uint8_t readLEDR(void);
    uint8_t readLEDG(void);
    uint8_t readLEDB(void);

    /** GP LED Functions **/
    uint8_t readGP1(void);
    uint8_t readGP2(void);
    uint8_t readGP3(void);

    /** Timing registers **/
    uint8_t readAntibouncingPeriod(void);
    uint8_t readDoublePushPeriod(void);
    uint8_t readFadeRGB(void);
    uint8_t readFadeGP(void);

    /** EEPROM register **/
    uint8_t readEEPROM(uint8_t add);




    /******    Write functions   ********/
    void writeGP1conf(uint8_t gp1);
    void writeGP2conf(uint8_t gp2);
    void writeGP3conf(uint8_t gp3);
    void writeInterruptConfig(uint8_t interrupt);

    /** Encoder functions **/
    void writeCounter(int32_t counter);
    void writeCounter(float counter);

    void writeMax(int32_t max);
    void writeMax(float max);

    void writeMin(int32_t min);
    void writeMin(float min);

    void writeStep(int32_t step);
    void writeStep(float step);

    /** RGB LED Functions **/
    void writeLEDR(uint8_t rled);
    void writeLEDG(uint8_t gled);
    void writeLEDB(uint8_t bled);
    void writeRGBCode(uint32_t rgb);

    /** GP LED Functions **/
    void writeGP1(uint8_t gp1);
    void writeGP2(uint8_t gp2);
    void writeGP3(uint8_t gp3);

    /** Timing registers **/
    void writeAntibouncingPeriod(uint8_t bounc);
    void writeDoublePushPeriod(uint8_t dperiod);
    void writeFadeRGB(uint8_t fade);
    void writeFadeGP(uint8_t fade);

    /** EEPROM register **/
    void writeEEPROM(uint8_t add, uint8_t data);


  private:
  
    InterruptFunction Events[SOURCE_INT_NUMB] = {NULL};

    uint8_t _add = 0x00;
    uint8_t _stat = 0x00;
    uint8_t _stat2 = 0x00;
    uint8_t _gconf = 0x00;
    union Data_v _tem_data;

    void eventcaller(SourceInt event);
    uint8_t readEncoderByte(uint8_t reg);
    int16_t readEncoderInt(uint8_t reg);
    int32_t readEncoderLong(uint8_t reg);
    float readEncoderFloat(uint8_t reg);
    void writeEncoder(uint8_t reg, uint8_t data);
    void writeEncoder(uint8_t reg, int32_t data);
    void writeEncoder(uint8_t reg, float data);
    void writeEncoder24bit(uint8_t reg, uint32_t data);

};

#endif