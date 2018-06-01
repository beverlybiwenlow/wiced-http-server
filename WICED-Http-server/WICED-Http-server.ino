/*********************************************************************
  This is an example for our WICED Feather WIFI modules

  Pick one up today in the adafruit shop!

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  MIT license, check LICENSE for more information
  All text above, and the splash screen below must be included in
  any redistribution
*********************************************************************/


#include <adafruit_feather.h>
#include <adafruit_http_server.h>
#include <strings.h>
#include <string>


// Wifi credentials
char WLAN_SSID_1[50] = "EinsteinWiz111";
char WLAN_PASS_1[50] = "benev0lence!2821";

// Hotspot credentials
//char WLAN_SSID_2[] = "srinidhi";
//char WLAN_PASS_2[] = "12345678";
char WLAN_SSID_2[] = "Judith";
char WLAN_PASS_2[] = "jujujuju";

bool new_wifi_added = false;


// The TCP port to use
#define PORT                 80

/* Modern browsers uses parallel loading technique which could
   open up to 6 or 8 connections to render an html page.
   Increase the MAX_CLIENTS if you often got the httpserver timeout
*/
#define MAX_CLIENTS          8

int ledPin = PA15;
int visit_count = 0;

void wifi_login_html_generator  (const char* url, const char* query, httppage_request_t* http_request);
void info_html_generator        (const char* url, const char* query, httppage_request_t* http_request);
void file_not_found_generator   (const char* url, const char* query, httppage_request_t* http_request);
void registered_generator   (const char* url, const char* query, httppage_request_t* http_request);

HTTPPage pages[] =
{
  HTTPPageRedirect("/", "/wifilogin.html"), // redirect root to wifi login page
  HTTPPage("/wifilogin.html", HTTP_MIME_TEXT_HTML, wifi_login_html_generator),
  HTTPPage("/info.html" , HTTP_MIME_TEXT_HTML, info_html_generator),
  HTTPPage("/registered.html" , HTTP_MIME_TEXT_HTML, registered_generator),
  HTTPPage("/404.html" , HTTP_MIME_TEXT_HTML, file_not_found_generator),
};

uint8_t pagecount = sizeof(pages) / sizeof(HTTPPage);


// Declare HTTPServer with max number of pages
AdafruitHTTPServer httpserver(pagecount);
/**************************************************************************/
/*!
   @brief  Example of generating dynamic HTML content on demand

   Link is separated to url and query

   @param url           url of this page
   @param query         query string after '?' e.g "var=value"

   @param http_request  This request's information
*/
/**************************************************************************/

void wifi_login_html_generator (const char* url, const char* query, httppage_request_t* http_request)
{
  (void) url;
  (void) query;
  (void) http_request;

  httpserver.print("<html><body>");
  httpserver.print("<h1>Wifi Registration Page</h1>");
  httpserver.print("<br>");

  httpserver.print("Please enter Wifi credentials to register: <br>");
  httpserver.print("Click <a href=\"/info.html\">here</a> for extra firmware details <br>");

  httpserver.print("<script language = \"JavaScript\">");
  httpserver.print("function formToJson(form){");
  httpserver.print("var pass = form.pass.value;");
  httpserver.print("var ssid = form.ssid.value;");
  httpserver.print("var jsonFormInfo = JSON.stringify({");
  httpserver.print("ssid:ssid,");
  httpserver.print("pass: pass");
  httpserver.print("});");
  httpserver.print("window.alert(jsonFormInfo);");
  httpserver.print("}");
  httpserver.print("</script>");

  httpserver.print("<form method=\"get\" action=\"/registered.html\">");
  httpserver.print("<label class=\"label\">SSID:  </label>");
  httpserver.print("<input type = \"text\" name = \"ssid\"/>");
  httpserver.print("<br/>");
  httpserver.print("<label>Password:  </label>");
  httpserver.print("<input type = \"text\" name = \"pass\"/>");
  httpserver.print("<br/>");
  httpserver.print("<input type=\"submit\" value=\"Submit\">");
  httpserver.print("</form>");
  httpserver.print("</body></html>");
}


void info_html_generator (const char* url, const char* query, httppage_request_t* http_request)
{
  (void) url;
  (void) query;
  (void) http_request;

  httpserver.print("<b>Bootloader</b> : ");
  httpserver.print( Feather.bootloaderVersion() );
  httpserver.print("<br>");

  httpserver.print("<b>WICED SDK</b> : ");
  httpserver.print( Feather.sdkVersion() );
  httpserver.print("<br>");

  httpserver.print("<b>FeatherLib</b> : ");
  httpserver.print( Feather.firmwareVersion() );
  httpserver.print("<br>");

  httpserver.print("<b>Arduino API</b> : ");
  httpserver.print( Feather.arduinoVersion() );
  httpserver.print("<br>");
  httpserver.print("<br>");

  visit_count++;
  httpserver.print("<b>visit count</b> : ");
  httpserver.print(visit_count);
}


void registered_generator (const char* url, const char* query, httppage_request_t* http_request)
{
  (void) url;
  (void) query;
  (void) http_request;

    char query1[100];
    strcpy(query1, query);
    char * ssid = strtok(query1, "&");
    char * pass = strtok(NULL, "&");
    char * ssid_value1 = strtok(ssid, "=");
    char * ssid_value = strtok(NULL, "=");
    char * pass_value1 = strtok(pass, "=");
    char * pass_value = strtok(NULL, "=");
    
    strcpy(WLAN_SSID_1, ssid_value);
    strcpy(WLAN_PASS_1, pass_value);
        
    httpserver.print("<html><body>");
    httpserver.print("<h1>Wifi Registered!</h1>");
    httpserver.print("<br>");
  
    httpserver.print("You have registered the following credentials: <br>");
    httpserver.print("SSID: ");
    httpserver.print(WLAN_SSID_1);
    httpserver.print("<br> Password: ");
    httpserver.print(WLAN_PASS_1);
    httpserver.print("</body></html>");

    Serial.print("Please wait to connect to ");
    Serial.print(WLAN_SSID_1);
    Serial.println(" ...");

    new_wifi_added = true;
}


/**************************************************************************/
/*!
   @brief  HTTP Page 404 generator, HTTP Server will automatically response
   with page "/404.html" when it coulnd't found requested url in Registered Pages

   Link is separated to url and query

   @param url           url of this page
   @param query         query string after '?' e.g "var=value"

   @param http_request  This request's information
*/
/**************************************************************************/
void file_not_found_generator (const char* url, const char* query, httppage_request_t* http_request)
{
  (void) url;
  (void) query;
  (void) http_request;

  httpserver.print("<html><body>");
  httpserver.print("<h1>Error 404 File Not Found!</h1>");
  httpserver.print("<br>");

  httpserver.print("Available pages are:");
  httpserver.print("<br>");

  httpserver.print("<ul>");
  for (int i = 0; i < pagecount; i++)
  {
    httpserver.print("<li>");
    httpserver.print(pages[i].url);
    httpserver.print("</li>");
  }
  httpserver.print("</ul>");

  httpserver.print("</body></html>");
}



void setup()
{
  Serial.begin(115200);

  // Wait for the Serial Monitor to open
  while (!Serial)
  {
    /* Delay required to avoid RTOS task switching problems */
    delay(1);
  }

  Serial.println("HTTP Server to Register new Wifi connections\r\n");

  // Print all software versions
  Feather.printVersions();
}



void loop()
{
  Serial.println("LOOOOOP");
  char ssid_array[50];
  strcpy(ssid_array, Feather.SSID());
  
  if(Feather.connected()){
    
    if(strcmp(ssid_array, WLAN_SSID_1) == 0){
      Serial.println("SUCCESSFULLY REGISTERED WIFI");
      Feather.printNetwork();
      delay(60000);
    }
    
    else if (strcmp(ssid_array, WLAN_SSID_2) == 0){
      
      if (! httpserver.started()){
        // Tell the HTTP client to auto print error codes and halt on errors
        httpserver.err_actions(true, true);
  
        // Configure HTTP Server Pages
        Serial.println("Adding Pages to HTTP Server");
        httpserver.addPages(pages, pagecount);
  
        Serial.print("Starting HTTP Server ... ");
        httpserver.begin(PORT, MAX_CLIENTS);
        Feather.printNetwork();
        Serial.println(" OK. Go to Local IP now.");
      }
      
      else{
        
        if(new_wifi_added){
          Serial.print("New wifi added: ");
          Serial.println(WLAN_SSID_1);
          httpserver.stop();
          Feather.disconnect();
          Serial.println(Feather.connected());
          connectAP(WLAN_SSID_1, WLAN_PASS_1);
          Feather.printNetwork();
        }
        
        else{
          Serial.println("Please go to the webpage to register new wifi.");
        }
        
      }
      
      delay(10000);
    }
  }
  
  else{
    Serial.println("No wifi credentials registered. Opening hotspot...");
    connectAP(WLAN_SSID_2, WLAN_PASS_2);
    delay(5000);
  }
  
}


/**************************************************************************/
/*!
    @brief  Connect to the defined access point (AP)
*/
/**************************************************************************/
bool connectAP(char* WLAN_SSID, char* WLAN_PASS)
{
  // Attempt to connect to an AP
  Serial.print("Please wait while connecting to: ");
  Serial.print(WLAN_SSID);
      
    if ( Feather.connect(WLAN_SSID, WLAN_PASS) )
    {
      Serial.print("... Connected!");
    }
    else
    {
      Serial.printf("Failed! %s (%d)", Feather.errstr(), Feather.errnum());
      Serial.println();
    }
  
  Serial.println();

//  if (Feather.config(3232246543, 3232246529, 4294967040)){
//        Serial.print("Static IP added.");
//  }
//  Serial.println(Feather.localIP());
//  Serial.println(Feather.gatewayIP());
//  Serial.println(Feather.subnetMask());

  return Feather.connected();
}

/**************************************************************************/
/*!
    @brief  TCP/HTTP disconnect callback
*/
/**************************************************************************/
void disconnect_callback(void)
{
  Serial.println();
  Serial.println("---------------------");
  Serial.println("DISCONNECTED CALLBACK");
  Serial.println("---------------------");
  Serial.println();

  httpserver.stop();
}
