#include "perseus-monicare.h"

// Variables
device_state_t device_state = CONNECTING_TO_WIFI_DS;
panic_state_t panic_state;
uint64_t last_user_interaction = 0;

// DS18B20
sensor_port_t DS18B20 = { 27, 0 };
OneWire one_wire_DS18B20(DS18B20.port);
DallasTemperature dallas_DS18B20(&one_wire_DS18B20);
DeviceAddress DS18B20_addr;

// Oximeter
MAX30105 oximeter;
uint32_t ir_buffer[OXI_BUFFER_LENGTH];
uint32_t red_buffer[OXI_BUFFER_LENGTH];
int32_t spo2;
int8_t valid_spo2;
int32_t heart_rate;
int8_t valid_heart_rate;
long last_beat = 0;
double beats_per_minute;
int beat_avg = 0;
int spo2_avg = 0;

// Matrix Keypad
char keypad_keys[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

byte keypad_row_pins[KEYPAD_ROWS] = { 12, 18, 5, 17 };
byte keypad_col_pins[KEYPAD_COLS] = { 16, 4, 15, 13 };

Keypad keypad = Keypad(makeKeymap(keypad_keys), keypad_row_pins, keypad_col_pins, KEYPAD_ROWS, KEYPAD_COLS);

// LCD
bool lcd_is_on = true;
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

// standby
bool standby_indicator_led_state = false;

// WiFi Connection
WiFiClient wifi_client;

// API
api_client_t api_client(SERVER_IP, SERVER_PORT);
