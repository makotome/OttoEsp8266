#include <Arduino.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Otto.h"
#include "ControllerHtml.h"

const char *ssid = "tp-peace";
const char *password = "xumingxin";
ESP8266WebServer server(80);

Otto ottoXX; // This is Otto!

#define LeftLeg 12
#define RightLeg 13
#define LeftFoot 14
#define RightFoot 15
#define Buzzer 5
void playAll();

void handleRoot()
{
    server.send(200, "text/html", INDEX_HTML);
}

void singRandom()
{
    int randomNum = random(1, 19); // 生成1到10之间的随机数
    ottoXX.sing(randomNum);
}

void handleCommand(const String &command)
{
    // 设置CORS头
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "OK");

    singRandom();  // 随机唱歌
    ottoXX.home(); // 回到初始位置
    // 执行相应的命令
    if (command == "forward")
    {
        ottoXX.walk(2, 1000, 1); // 2 steps, "TIME". IF HIGHER THE VALUE THEN SLOWER (from 600 to 1400), 1 FORWARD
    }
    else if (command == "backward")
    {
        ottoXX.walk(2, 1000, -1); // 2 steps, T, -1 BACKWARD
    }
    else if (command == "left")
    {
        ottoXX.turn(2, 1000, -1); // 3 steps turning LEFT
    }
    else if (command == "right")
    {
        ottoXX.turn(2, 1000, 1); // 3 steps turning RIGHT
    }
    else if (command == "stop")
    {
        ottoXX.home();
    }
    else if (command == "num1")
    {
        ottoXX.shakeLeg(1, 2000, -1);
    }
    else if (command == "num2")
    {
        ottoXX.moonwalker(3, 1000, 25, -1); // RIGHT
    }
    else if (command == "num3")
    {
        ottoXX.crusaito(2, 1000, 20, -1);
    }
    else if (command == "num4")
    {
        ottoXX.flapping(2, 1000, 20, -1);
    }
    else if (command == "num5")
    {
        ottoXX.swing(2, 1000, 20);
    }
    else if (command == "num6")
    {
        ottoXX.tiptoeSwing(2, 1000, 20);
    }
    else if (command == "num7")
    {
        ottoXX.jitter(2, 1000, 20); //(small T)
    }
    else if (command == "num8")
    {
        ottoXX.updown(2, 1500, 20); // 20 = H "HEIGHT of movement"T
    }
    else if (command == "num9")
    {
        ottoXX.jump(1, 500); // It doesn't really jumpl ;P
    }
    else
    {
        Serial.println("未知命令");
    }
    ottoXX.home(); // 回到初始位置
}

void setup()
{
    Serial.begin(115200);

    delay(1000);

    // 设置引脚模式
    ottoXX.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); // Set the servo pins and Buzzer pin
    ottoXX.sing(S_connection);                                         // ottoXX wake up!
    ottoXX.home();

    // 配置WiFi
    WiFi.begin(ssid, password);
    Serial.println("\nWiFi正在连接");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi连接成功");
    Serial.print("IP地址: ");
    Serial.println(WiFi.localIP());

    // 设置Web服务器路由
    server.on("/", HTTP_GET, handleRoot);

    // 设置命令路由
    server.on("/forward", HTTP_GET, []()
              { handleCommand("forward"); });
    server.on("/backward", HTTP_GET, []()
              { handleCommand("backward"); });
    server.on("/left", HTTP_GET, []()
              { handleCommand("left"); });
    server.on("/right", HTTP_GET, []()
              { handleCommand("right"); });
    server.on("/stop", HTTP_GET, []()
              { handleCommand("stop"); });
    server.on("/num1", HTTP_GET, []()
              { handleCommand("num1"); });
    server.on("/num2", HTTP_GET, []()
              { handleCommand("num2"); });
    server.on("/num3", HTTP_GET, []()
              { handleCommand("num3"); });
    server.on("/num4", HTTP_GET, []()
              { handleCommand("num4"); });
    server.on("/num5", HTTP_GET, []()
              { handleCommand("num5"); });
    server.on("/num6", HTTP_GET, []()
              { handleCommand("num6"); });
    server.on("/num7", HTTP_GET, []()
              { handleCommand("num7"); });
    server.on("/num8", HTTP_GET, []()
              { handleCommand("num8"); });
    server.on("/num9", HTTP_GET, []()
              { handleCommand("num9"); });
    server.onNotFound([]()
                      { server.send(404, "text/plain", "404 Not Found"); });

    // 启动Web服务器
    server.begin();
    Serial.println("HTTP服务器启动");
}

void loop()
{
    server.handleClient();
}

void playAll()
{
    ottoXX.walk(2, 1000, 1);  // 2 steps, "TIME". IF HIGHER THE VALUE THEN SLOWER (from 600 to 1400), 1 FORWARD
    ottoXX.walk(2, 1000, -1); // 2 steps, T, -1 BACKWARD
    ottoXX.turn(2, 1000, 1);  // 3 steps turning LEFT
    ottoXX._tone(10, 3, 1);
    ottoXX.bendTones(100, 200, 1.04, 10, 10);
    ottoXX.home();
    delay(100);
    ottoXX.turn(2, 1000, -1); // 3 steps turning RIGHT
    ottoXX.bend(1, 500, 1);   // usually steps =1, T=2000
    ottoXX.bend(1, 2000, -1);
    ottoXX.shakeLeg(1, 1500, 1);
    ottoXX.home();
    delay(100);
    ottoXX.shakeLeg(1, 2000, -1);
    ottoXX.moonwalker(3, 1000, 25, 1);  // LEFT
    ottoXX.moonwalker(3, 1000, 25, -1); // RIGHT
    ottoXX.crusaito(2, 1000, 20, 1);
    ottoXX.crusaito(2, 1000, 20, -1);
    delay(100);
    ottoXX.flapping(2, 1000, 20, 1);
    ottoXX.flapping(2, 1000, 20, -1);
    delay(100);
    ottoXX.swing(2, 1000, 20);
    ottoXX.tiptoeSwing(2, 1000, 20);
    ottoXX.jitter(2, 1000, 20); //(small T)
    ottoXX.updown(2, 1500, 20); // 20 = H "HEIGHT of movement"T
    ottoXX.ascendingTurn(2, 1000, 50);
    ottoXX.jump(1, 500); // It doesn't really jumpl ;P
    ottoXX.home();
    delay(100);
}
