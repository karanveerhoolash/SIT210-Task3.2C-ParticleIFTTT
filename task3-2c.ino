// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>

// NOTE : In this task we are using a temperature sensor to indicate whether there is light or not. We are assuming that if temperature is greater than 26, 
//         then there is light. Since my light sensor has not been soldered yet, Dr. Imali proposed to use temperature sensor itself for this task.

DHT dht(A0,DHT11);


void setup() {

dht.begin();
}

void loop() {
    
    bool email_light = false;
    bool email_dark = false;
    
    float temp = dht.getTempCelcius();
    
    
     // email is sent once when light is touched not every second to spam the user
     
     
    
    if ((temp > 26) && (email_light == false)){             // If there is light ; we send an email and set the bool variable email_light to true     
        Particle.publish("Light_Status", "Sun");            // we are not going to send another email even though there is still light  
        email_light = true;
    }
    else if ((temp <=26) && (email_dark ==false)){         // If there is no light ; we send one email only and wait till theres light  to send the next
        Particle.publish("Light_Status", "Dark");       // 
        email_dark = true;
    }
    
    // if we sent an email when light was on and off ;  need to reset again for next cycle
    
    if ((email_light == true) && (email_dark == true))
    {
        email_dark = false;
        email_light = false;
    }
    
    delay(300000);  // check every 5 minutes
    
  
}