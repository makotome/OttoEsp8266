#include "ControllerServer.h"
#include "ControllerHtml.h"

ControllerServer::ControllerServer() : server(80) // 初始化 AsyncWebServer 在端口 80
{
  // 如果有其他成员需要初始化，可以在这里进行
}

void ControllerServer::setWiFiApMode(const char *ssid, const char *password)
{

  // 设置AP模式的固定IP（关键修改点）
  IPAddress localIP(192, 168, 1, 100);         // AP的IP地址
  IPAddress subnet(255, 255, 255, 0);          // 子网掩码
  WiFi.softAPConfig(localIP, localIP, subnet); // AP模式的IP配置函数

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  dnsServer.start(53, "*", WiFi.softAPIP());
}

void ControllerServer::setWiFi(const char *ssid, const char *password)
{
  wifiSsid = ssid;
  wifiPassword = password;
}

void ControllerServer::connectWiFi()
{
  WiFi.begin(wifiSsid, wifiPassword);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void ControllerServer::initServer()
{
  // 设置HTTP服务器路由
  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  //           { request->redirect("/controller"); });

  static const size_t htmlContentLength = strlen_P(htmlContent);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if (request->hasParam("who")) {
      Serial.printf("Who? %s\n", request->getParam("who")->value().c_str());
    }

    request->send(200, "text/html", (uint8_t *)htmlContent, htmlContentLength); });
}
