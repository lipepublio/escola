#include <SPI.h>
#include <EtherEncLib.h>
#include <avr/pgmspace.h>
#include <Thermistor.h>


const PROGMEM char resp200Txt[] = {"HTTP/1.0 200 OK\n\rContent-Type: text/html\n\rPragma: no-cache\n\r\n\r"};

int RelayPin = 5;

Thermistor temp(0);

EtherEncLib lib(80);

static unsigned char ipaddr[] = { 192, 168, 1, 2 };
static unsigned char macaddr[] = { 0x54, 0x55, 0x58, 0x10, 0x00, 0x25 };


void setup()
{
    Serial.begin(115200);
    Serial.begin(9600); 

    pinMode(10,OUTPUT);	
    
    
    lib.begin(ipaddr, macaddr);
    
   
    pinMode(RelayPin, OUTPUT);
    digitalWrite(RelayPin, LOW);
    
    Serial.println("EtherEncLib.h started!");
    
}

void loop()
{
   
    int temperature = temp.getTemp();
    
   
    if (lib.available())
    {
        
        char *params = lib.getParams();
        
        Serial.print("Params: ");
        Serial.println(params);
        
        
        lib.print("<HTML>");
        lib.print("<HEAD><TITLE>Arduino EtherEncLib.h</TITLE></HEAD>");
        lib.print("<BODY>");
        
        
        lib.print("<h3>Controle sua Cafeteira!</h3>");
        
        
        if (strncmp(&params[1], "button", 5) == 0 )
        {
            
            if (strncmp(&params[8], "1", 1) == 0)
            {
                digitalWrite(RelayPin, HIGH);
                
               
                lib.print("<p><a href=/?button=0>Fazendo</a></p>");
            }
            else
            {
               
                digitalWrite(RelayPin, LOW);
                
               
                lib.print("<p><a href=/?button=1>Fazer Cafe</a></p>");
            }
        }
        else
        {
           
            lib.print("<p><a href=/?button=1>Fazer Cafe</a></p>");
        }

        lib.print (" Temperatura do Cafe: ");
        lib.print (temperature);
        lib.print (" *C ");
        
        
        lib.print("</BODY>");
        lib.print("</HTML>");
        
        lib.close();
    }

}
