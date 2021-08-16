#include <Utility.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncWebSocketClient *globalClient = NULL;

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{

  if (type == WS_EVT_CONNECT)
  {

    Serial.println("Websocket client connection received");
    globalClient = client;
  }
  else if (type == WS_EVT_DISCONNECT)
  {

    Serial.println("Websocket client connection finished");
    globalClient = NULL;
  }
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "404 Not found");
}

bool initSPIFFS() {
  bool SPIFFS_Status = !SPIFFS.begin(true);
  if (SPIFFS_Status)
  {
      Serial.println("Erreur SPIFFS...");
      return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  
  while (file)
  {
      Serial.print("File: ");
      Serial.println(file.name());
      file.close();
      file = root.openNextFile();
  }

  return SPIFFS_Status;
}

bool initWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    return false;
  }

  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  return true;
}

void startServe() {
  //Pages
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println(request->url());
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.serveStatic("/", SPIFFS, "/public/");
  server.onNotFound(notFound);

  // ws.onEvent(onWsEvent);
  // server.addHandler(&ws);

  server.begin();
  Serial.println("Serveur actif!");
}