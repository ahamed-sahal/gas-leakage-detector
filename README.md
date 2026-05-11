# 🔥 Smart IoT Gas Leakage Detector with Level Monitoring

An IoT-based gas leakage detection system built with ESP8266 that monitors LPG gas levels in real time and sends instant mobile alerts via the Blynk app when a leak is detected.

-----

## 📋 Features

- Real-time gas level monitoring using MQ-2 sensor
- Instant push notifications via Blynk app on gas detection
- Visual alerts with Red / Yellow / Green LEDs
- Audible buzzer alarm on gas leak
- Automatic ventilation fan trigger via relay
- Live status display on 16x2 I2C LCD screen
- Wi-Fi connected via ESP8266 (NodeMCU)

-----

## 🛠️ Hardware Components

|Component                |Description                              |
|-------------------------|-----------------------------------------|
|ESP8266 (NodeMCU)        |Main microcontroller with Wi-Fi          |
|MQ-2 Gas Sensor          |Detects LPG, smoke, and combustible gases|
|16x2 I2C LCD             |Displays system status                   |
|Red / Yellow / Green LEDs|Visual status indicators                 |
|Buzzer                   |Audible alert on gas detection           |
|Relay Module             |Controls ventilation fan                 |

-----

## 📱 Software & Libraries

- [Arduino IDE](https://www.arduino.cc/en/software)
- [Blynk IoT Platform](https://blynk.io/)
- `ESP8266WiFi.h`
- `BlynkSimpleEsp8266.h`
- `LiquidCrystal_I2C.h`

-----

## ⚙️ Setup Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/ahamed-sahal/gas-leakage-detector.git
```

### 2. Configure Your Credentials

Open `gas_leakage_detector.ino` and replace the placeholders with your own values:

```cpp
#define BLYNK_TEMPLATE_ID "your_template_id"
#define BLYNK_AUTH_TOKEN  "your_auth_token"

char ssid[] = "your_wifi_name";
char pass[] = "your_wifi_password";
```

> ⚠️ **Never commit real credentials to a public repository.**

### 3. Install Libraries

In Arduino IDE, go to **Sketch → Include Library → Manage Libraries** and install:

- `Blynk`
- `LiquidCrystal I2C`

### 4. Flash to ESP8266

- Select board: **NodeMCU 1.0 (ESP-12E Module)**
- Select the correct COM port
- Click **Upload**

-----

## 🔌 Circuit Diagram

|ESP8266 Pin  |Connected To       |
|-------------|-------------------|
|D5           |MQ-2 Digital Output|
|D3           |Green LED          |
|D4           |Yellow LED         |
|D2           |Red LED            |
|D8           |Buzzer             |
|D0           |Relay Module       |
|D1 / D2 (I2C)|LCD SDA / SCL      |

-----

## 🚀 How It Works

1. On startup, the ESP8266 connects to Wi-Fi and initialises the Blynk cloud
1. The MQ-2 sensor continuously reads gas concentration
1. If gas is detected (sensor reads HIGH):
- Red LED turns on, buzzer sounds, relay activates the fan
- LCD displays **“GAS LEAK! Danger!”**
- A Blynk push notification is sent to your phone (once per event)
1. When air is clear again:
- Green LED turns on, buzzer and fan turn off
- LCD displays **“System Safe”**

-----

## 👤 Author

**Ahamed Sahal**

- LinkedIn: [linkedin.com/in/ahamed-sahal](https://linkedin.com/in/ahamed-sahal)
- GitHub: [github.com/ahamed-sahal](https://github.com/ahamed-sahal)

-----

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
