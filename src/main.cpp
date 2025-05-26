#include <Arduino.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Otto.h"
#include "ControllerHtml.h"
#include <ArduinoJson.h>

const char *ssid = "tp-peace";
const char *password = "xumingxin";
ESP8266WebServer server(80);

Otto ottoXX; // This is Otto!

#define LeftLeg 12
#define RightLeg 13
#define LeftFoot 14
#define RightFoot 15
#define Buzzer 5

void handleAction(String command, int value);
void handleCommand();
void handleProgram();
void handleRootPage();
void handleProgramPage();
void singRandom();
void handleOPTIONS();
void commandAction(String command);

void setup()
{
    Serial.begin(115200);

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

    // 添加路由处理
    server.on("/program", HTTP_OPTIONS, handleOPTIONS);
    server.on("/program", HTTP_POST, handleProgram);
    // 设置路由
    server.on("/command", HTTP_OPTIONS, handleOPTIONS);
    server.on("/command", HTTP_POST, handleCommand);

    // 启动Web服务器
    server.begin();
    Serial.println("HTTP服务器启动");
}

void loop()
{
    server.handleClient();
}

void handleRootPage()
{
    server.send(200, "text/html", INDEX_HTML);
}

void handleProgramPage()
{
    server.send(200, "text/html", PROGRAME_HTML);
}

void singRandom()
{
    int randomNum = random(1, 19); // 生成1到10之间的随机数
    ottoXX.sing(randomNum);
}

// 处理预检请求的函数
void handleOPTIONS()
{
    // 添加CORS相关的响应头
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    server.send(200, "text/plain", "");
}

// 处理机器人命令
void handleCommand()
{
    // 添加CORS头
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");

    if (server.method() == HTTP_POST)
    {
        String json = server.arg("plain");
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, json);

        if (error)
        {
            // JSON解析错误处理
            StaticJsonDocument<200> response;
            response["success"] = false;
            response["message"] = "无效的JSON格式";
            String responseJson;
            serializeJson(response, responseJson);
            server.send(400, "application/json", responseJson);
            return;
        }

        // 获取命令
        const char *command = doc["command"];

        commandAction(command);
        delay(100); // 确保命令执行完成
    }
}

// 处理程序的函数
void handleProgram()
{
    // 添加CORS响应头
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");

    if (server.method() == HTTP_POST)
    {
        if (server.hasArg("plain"))
        {
            String json = server.arg("plain");

            // 创建 JSON 文档
            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, json);

            if (error)
            {
                Serial.println("JSON 解析失败");
                server.send(400, "text/plain", "JSON 格式错误");
                return;
            }

            // 发送成功响应
            server.send(200, "text/plain", "OK");

            // 顺序执行每个命令
            JsonArray array = doc.as<JsonArray>();
            for (JsonVariant v : array)
            {
                String command = v["command"].as<String>();
                int commandValue = 2;
                if (v["songValue"].is<int>())
                {
                    commandValue = v["songValue"].as<int>();
                }
                else if (v["steps"].is<int>())
                {
                    commandValue = v["steps"].as<int>();
                }
                // 执行命令
                Serial.printf("执行命令: %s, 步数: %d\n", command.c_str(), commandValue);
                handleAction(command, commandValue);
                delay(100); // 命令之间的延迟
            }
        }
        else
        {
            server.send(400, "text/plain", "缺少数据");
        }
    }
    else
    {
        server.send(405, "text/plain", "方法不允许");
    }
}

void handleAction(String command, int value = 2)
{
    // 设置CORS头
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "text/plain", "OK");

    actions(command, value); // 调用动作函数
    Serial.printf("执行动作: %s, 步数: %d\n", command.c_str(), value);
}

void commandAction(String command)
{
    // 处理不同的命令
    bool success = true;
    String message = "命令执行成功";

    // 返回响应
    StaticJsonDocument<200> response;
    response["success"] = success;
    response["message"] = message;
    String responseJson;
    serializeJson(response, responseJson);
    server.send(200, "application/json", responseJson);

    if (command == "sing")
    {
    }
    else if (command == "forward")
    {
        actions("forward", 4); // 前进4步
    }
}

void actions(String command, int value = 2)
{
    ottoXX.home(); // 回到初始位置
                   // 执行相应的命令
    if (command == "sing")
    {
        ottoXX.sing(value); // value 是歌曲编号
    }
    else if (command == "forward")
    {
        ottoXX.walk(value, 1000, 1);
    }
    else if (command == "backward")
    {
        ottoXX.walk(value, 1000, -1);
    }
    else if (command == "left")
    {
        ottoXX.turn(value, 1000, -1);
    }
    else if (command == "right")
    {
        ottoXX.turn(value, 1000, 1);
    }
    else if (command == "stop")
    {
        ottoXX.home();
    }
    else if (command == "leftBend")
    {
        ottoXX.bend(value, 2000, 1);
    }
    else if (command == "rightBend")
    {
        ottoXX.bend(value, 2000, -1);
    }
    else if (command == "leftShake")
    {
        ottoXX.shakeLeg(value, 2000, 1);
    }
    else if (command == "rightShake")
    {
        ottoXX.shakeLeg(value, 2000, -1);
    }
    else if (command == "leftSpaceWalk")
    {
        ottoXX.moonwalker(value, 1000, 25, 1); // LEFT
    }
    else if (command == "rightSpaceWalk")
    {
        ottoXX.moonwalker(value, 1000, 25, -1); // RIGHT
    }
    else if (command == "leftFlap")
    {
        ottoXX.flapping(value, 1000, 20, 1);
    }
    else if (command == "rightFlap")
    {
        ottoXX.flapping(value, 1000, 20, -1);
    }
    else if (command == "leftCrusaito")
    {
        ottoXX.crusaito(value, 1000, 20, 1); // LEFT
    }
    else if (command == "rightCrusaito")
    {
        ottoXX.crusaito(value, 1000, 20, -1); // RIGHT
    }
    else if (command == "leftSwing")
    {
        ottoXX.swing(value, 1000, 20);
    }
    else if (command == "rightSwing")
    {
        ottoXX.tiptoeSwing(value, 1000, 20);
    }
    else if (command == "jitter")
    {
        ottoXX.jitter(value, 1000, 20); //(small T)
    }
    else if (command == "updown")
    {
        ottoXX.updown(value, 1500, 20); // 20 = H "HEIGHT of movement"T
    }
    else if (command == "ascendingTurn")
    {
        ottoXX.ascendingTurn(value, 1000, 50);
    }
    else
    {
        Serial.println("未知命令");
    }
    ottoXX.home(); // 回到初始位置
}
