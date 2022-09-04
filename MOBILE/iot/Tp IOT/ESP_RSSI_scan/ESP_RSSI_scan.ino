#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "D2CPGW33 9747";
const char* password = ">79Z0f38";

// Set web server port number to 80
WiFiServer server(80);

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

float X = 43.5;
float Y = 3.6;
float max_distance = 0.25;
int N = sizeof(data) / sizeof(Parck);
String baseUrl = "https://data.montpellier3m.fr/sites/default/files/ressources/";
String xmlExtension = ".xml";

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {

  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {
    currentTime = millis();
    previousTime = currentTime; 
    Serial.println("New Client."); 
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) { // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c); 
        header += c;
        if (c == '\n') { 
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /parcks") >= 0) {
              Serial.println("Get HTML page");

              // Display the HTML web page
              client.println("<!DOCTYPE html><html>");
              client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
              client.println("<link rel=\"icon\" href=\"data:,\">");
              // CSS to style the on/off buttons 
              // Feel free to change the background-color and font-size attributes to fit your preferences
              client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
              client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
              client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
              client.println(".button2 {background-color: #555555;}</style></head>");
  
              // Web Page Heading
              client.println("<body><h1>ESP32 Web Server</h1>");
  
  
             
                HTTPClient http;
  
                int i = 0;
                int selectedIndexArray [22];
                int selecetdArraySize = 0;
        
                for(i;i<N;i++){
                  if(distance(X,Y,data[i].lon,data[i].lat) <= max_distance){
                    selectedIndexArray[selecetdArraySize] = i;  
                    selecetdArraySize++;
                    }
                  }
                  
                  for(i =0;i<selecetdArraySize;i++){
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

                      client.println("<p>Parck name: " + data[i].name + " Status: " + parseParckXML(payload,"<Status>","</Status>") + " Free: " + parseParckXML(payload,"<Free>","</Free>")+"</p>");
                   
          
                      
                    }else{
                      Serial.print("Error code: ");
                      Serial.println(httpResponseCode);
                    }
                  }
                  // Free resources
                  http.end();
              
               client.println("</body></html>");
               // The HTTP response ends with another blank line
              client.println();
              break;
            }
 
          }else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
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
