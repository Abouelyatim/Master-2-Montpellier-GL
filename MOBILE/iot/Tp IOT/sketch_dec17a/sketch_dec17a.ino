#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include <TFT_eSPI.h>
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();

// Replace with your network credentials
const char* ssid = "DESKTOP-0OACTKI 6570";
const char* password = "12345678";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameters in HTTP POST request
const char* PARAM_INPUT_1 = "longitude";
const char* PARAM_INPUT_2 = "latitude";

// Variables to save values from HTML form
String longitude;
String latitude;

// Variable to detect whether a new request occurred
bool newRequest = false;

String content = "<tr><td>Island Trading</td><td>Helen Bennett</td><td>UK</td></tr>";


// HTML to build the web page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Projet Parking</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <link rel="stylesheet" type="text/css" href="styles.css">
  <style>
    html {
    font-family: Arial;
    display: inline-block;
    margin: 0px auto;
    text-align: center;
    } 
    h1 {
    color: #0F3376;
    padding: 2vh;
    }
    p {
        font-size: 1.5rem;
    } 
    input[type=submit]:hover {
        background-color: #45a049;
    }
    input[type=submit] {
        background-color: #4CAF50;
        color: white;
        padding: 14px 20px;
        margin: 8px 0;
        border: none;
        border-radius: 4px;
        cursor: pointer;
    }
    input[type=number] {
        padding: 12px 20px;
        margin: 8px 0;
        display: inline-block;
        border: 1px solid #ccc;
        border-radius: 4px;
        box-sizing: border-box;
    }
    div {
        padding: 12px 20px;
        margin: 8px 0;
        background-color: #f2f2f2;
        padding: 20px;
    }
  </style>
</head>
<body>
  <h1>Projet Parking</h1>
  <p>Entrez votre position actuelle</strong></p>

  <div>
    <form action="/" method="post">
      <label for="log">Longitude:</label><br>
      <input type="number" id="longitude" step="any" name="longitude" value=""><br>
      <label for="lalti">Latitude:</label><br>
      <input type="number" id="latitude" step="any" name="latitude" value=""><br><br>
      <input type="submit" value="Submit">
    </form>
  </div>

</body>
</html>
)rawliteral";

// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

typedef struct Parck {
  const String id;
  const String name;
  const String path;
  const float lat;
  const float lon;
} Parck;

const Parck data [22] = {
  { 
    "34172_ANTIGO",
  "Antigone", 
  "FR_MTP_ANTI",
  3.88881893, 
  43.6087160 

  },
  {
     "34172_ARCTRI",
     "Arc de Triomphe",
     "FR_MTP_ARCT",
     3.87320075,
     43.61100267
  },
  {
     "34172_TRIANG",
     "Triangle",
     "FR_MTP_TRIA",
     3.88184418,
     43.60923384
  },
  {
     "34172_PITOT",
     "Pitot",
     "FR_MTP_PITO",
     3.87019117,
     43.61224494
  },
  {
     "34057_SABLAS",
   "Notre Dame de Sablassou",
   "FR_CAS_SABL",
   3.922295360000000, 
   43.634191940000001
  },
  { 
     "34172_CIRCE",
   "CircÃ© Odysseum",
   "FR_MTP_CIRC", 
   3.917849500000000,
   43.604953770000002 
  },
  {
     "34172_ARCEAU",
     "Arceaux",
     "FR_MTP_ARCE",
     3.86749067,
     43.61171647
  },
  {
     "34172_GAMBET",
     "Gambetta",
     "FR_MTP_GAMB",
     3.87137436,
     43.60695138
  },
  {
     "34172_FOCHPR",
     "Foch PrÃ©fecture",
     "FR_MTP_FOCH",
     3.87657084,
     43.61074912
  },
  {
     "34172_COMEDI",
     "ComÃ©die",
     "FR_MTP_COME",
     3.87976196,
     43.60856092
  },
  {
     "34172_POLYGO",
     "Polygone",
     "FR_MTP_POLY",
     3.88476539,
     43.60837096
  },
  {
     "34172_ANTIGO",
     "Antigone",
     "FR_MTP_ANTI",
     3.88881893,
     43.60871606
  },
  {
     "34172_EUROPA",
     "Europa",
     "FR_MTP_EURO",
     3.89253074,
     43.60784971
  },
  {
     "34172_CORUM",
     "Corum",
     "FR_MTP_CORU",
     3.88225773,
     43.61388821
  },
  {
     "34172_SAINTRO",
     "Saint Roch",
     "FR_MTP_GARE",
     3.87855072,
     43.60329149
  },
  {
     "34057_DEGAUL",
     "Charles de Gaulle",
     "FR_CAS_CDGA",
     3.8977621,
     43.62854212
  },
  {
     "34172_LORCA",
     "Garcia Lorca",
     "FR_MTP_GARC",
     3.8907158,
     43.59098509
  },
  {
     "34172_SABINE",
     "Sabines",
     "FR_MTP_SABI",
     3.8602246,
     43.58383263
  },
  {
     "34172_MOSSON",
     "Mosson",
     "FR_MTP_MOSS",
     3.81966554,
     43.61623716
  },
  {
     "34172_EUROME",
     "EuromÃ©decine",
     "FR_MTP_MEDC",
     3.82772365,
     43.63895359
  },
  {
     "34172_OCCITA",
     "Occitanie",
     "FR_MTP_OCCI",
     3.84859796,
     43.63456232
  },
  {
     "34270_LESEC",
     "Saint-Jean-le-Sec",
     "FR_STJ_SJLC",
     3.8379312,
     43.57082225
  }
};

unsigned long timerDelay = 5000;

float max_distance = 0.28;
int N = sizeof(data) / sizeof(Parck);
String baseUrl = "https://data.montpellier3m.fr/sites/default/files/ressources/";
String xmlExtension = ".xml";

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  showScrn(IpAddress2String(WiFi.localIP()));
}

String IpAddress2String(const IPAddress& ipAddress)
{
    return String(ipAddress[0]) + String(".") +
           String(ipAddress[1]) + String(".") +
           String(ipAddress[2]) + String(".") +
           String(ipAddress[3]);
}

void setup() {
  Serial.begin(115200);

  showStratScrn();
  initWiFi();


  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", index_html);
  });

  // Web Server Root URL
  server.on("/parks", HTTP_GET, [](AsyncWebServerRequest *request){

    String content = "";
    HTTPClient http;
    int i = 0;
    int selectedIndexArray [22];
    int selecetdArraySize = 0;

    for(i;i<N;i++){
        if(distance(longitude.toFloat() , latitude.toFloat(), data[i].lon, data[i].lat ) <= max_distance){
          selectedIndexArray[selecetdArraySize] = i;  
          selecetdArraySize++;
      }
    }

    for(i =0;i<selecetdArraySize;i++) {
       String serverPath;
       serverPath = baseUrl + data[i].path + xmlExtension; 
          
       // Your Domain name with URL path or IP address with path
       http.begin(serverPath.c_str());
          
       // Send HTTP GET request
       int httpResponseCode = http.GET();

       if (httpResponseCode>0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String payload = http.getString();
          Serial.println(payload);

          content+="<tr><td>"+data[i].name+"</td><td>"+parseParckXML(payload,"<Status>","</Status>")+"</td><td>"+parseParckXML(payload,"<Free>","</Free>")+"</td></tr>";
              
          }else{
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
          }
          
      }
      // Free resources
      http.end();

      String first_part = "<!DOCTYPE html><html><head><style>html{font-family:Arial;display:inline-block;margin:0 auto;text-align:center}h2{color:#0F3376;padding:2vh}table{font-family:arial,sans-serif;border-collapse:collapse;width:50%;margin-left:auto;margin-right:auto}td,th{border:1px solid #ddd;text-align:left;padding:8px}tr:nth-child(even){background-color:#ddd}.button{border:none;color:#fff;padding:16px 32px;text-align:center;text-decoration:none;display:inline-block;font-size:16px;margin:3% 2px;transition-duration:.4s;cursor:pointer;background-color:#fff;color:#000;border:2px solid #4CAF50}.button:hover{background-color:#4CAF50;color:#fff}</style></head><body><h2>D&#233;tails des plus proches parks</h2><div><table><tr><th>Nom</th><th>Disponibilit&#233;</th><th>Nb de places libres</th></tr>";
      first_part += content;
      first_part += "</table><button class=\"button\" name=\"redirect\" onclick=\"redirect()\">Go Back</button></div></body><script type=\"text/javascript\">function redirect(){window.location.href=\"/\"}</script></html>";

      
      
      request->send(200, "text/html", /*parks_html*/first_part.c_str());
  });
  
  // Handle request (form)
  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
    int params = request->params();
    
    for(int i=0;i<params;i++){
      
      AsyncWebParameter* p = request->getParam(i);
      
      if(p->isPost()){
        
        // HTTP POST input1 value (direction)
        if (p->name() == PARAM_INPUT_1) {
          
          longitude = p->value().c_str();
          Serial.print("longitude : ");
          Serial.println(longitude);
          
        }
        // HTTP POST input2 value (steps)
        if (p->name() == PARAM_INPUT_2) {
          latitude = p->value().c_str();
          Serial.print("latitude : ");
          Serial.println(latitude);
        }
      }
      
    }
    //request->send(200, "text/html", index_html);
    newRequest = true;
    request->redirect("/parks");
  });

  server.begin();
}

void loop() {
  // Check if there was a new request and move the stepper accordingly
  if (newRequest){
    
    newRequest = false;
  }
}

String parseParckXML(String source, String tagStart, String tagClose){
  int locStart = source.indexOf(tagStart);
  if (locStart==-1) return "";
  locStart += tagStart.length();
  int locFinish = source.indexOf(tagClose, locStart);
  if (locFinish==-1) return "";
  return source.substring(locStart, locFinish);
}

float distance(float x1, float y1, float x2, float y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

String processor(const String& var)
{
  if(var == "CONTENT") {
    String content = "";
    HTTPClient http;
    int i = 0;
    int selectedIndexArray [22];
    int selecetdArraySize = 0;

    for(i;i<N;i++){
        if(distance(longitude.toFloat() , latitude.toFloat(), data[i].lon, data[i].lat ) <= max_distance){
          selectedIndexArray[selecetdArraySize] = i;  
          selecetdArraySize++;
      }
    }

    for(i =0;i<selecetdArraySize;i++) {
       String serverPath;
       serverPath = baseUrl + data[i].path + xmlExtension; 
          
       // Your Domain name with URL path or IP address with path
       http.begin(serverPath.c_str());
          
       // Send HTTP GET request
       int httpResponseCode = http.GET();

       if (httpResponseCode>0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String payload = http.getString();
          Serial.println(payload);

          content+="<tr><td>"+data[i].name+"</td><td>"+parseParckXML(payload,"<Status>","</Status>")+"</td><td>"+parseParckXML(payload,"<Free>","</Free>")+"</td></tr>";
              
          }else{
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
          }
      }
      // Free resources
      http.end();
      Serial.println(content);
    return content;
  }
  return String();
}

void showScrn(String ipAddress) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(0, 30);
  tft.setFreeFont(&Orbitron_Light_24);
  tft.println("Berkane-Begoug");
  tft.drawLine(0, 35, 250, 35, TFT_BLUE);
  tft.setCursor(80, 60);
  tft.print("TP IOT");
  tft.setCursor(10, 90);
  tft.print(ipAddress);
  tft.setCursor(10, 120);
  tft.print("2021/2022");
}
void showStratScrn(){
  tft.begin();
  tft.setRotation(1); //Landscape
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(0, 30);
  tft.setFreeFont(&Orbitron_Light_24);
  tft.println("Connecting...");
}
