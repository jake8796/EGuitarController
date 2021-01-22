#define LIN_OUT 1 // turns linear function on of fht
#define FHT_N 256 // set to # of fht bins
#include <FHT.h> // include the library
int xmax = 0;
int j = 0;

void setup() {
    Serial.begin(9600); // use the serial port
    TIMSK0 = 0; // turn off timer0 for lower jitter
    ADCSRA = 0xe5; // set the adc to free running mode
    ADMUX = 0x40; // use adc0
    DIDR0 = 0x01; // turn off the digital input for adc0
   }
void loop() {
      while(1){// reduces jitter
        cli();  // UDRE interrupt slows this way down on arduino1.0
        for (int i = 0 ; i < FHT_N ; i++) { // save 64 samples
          while(!(ADCSRA & 0x10)); // wait for adc to be ready
          ADCSRA = 0xf6; // restart adc with a prescaler of 64 
          byte m = ADCL; // fetch adc data
          byte j = ADCH;
          int k = (j << 8) | m; // form into an int
          k -= 0x0200; // form into a signed int
          k <<= 6; // form into a 16b signed int
          fht_input[i] = k; // put real data into bins
       }
      fht_reorder(); // reorder the data before doing the fht
      fht_run(); // process the data in the fht
      fht_mag_lin(); // take the output of the fht
      sei();
      
      // prints off fht values to the serial monitor 
//      for( int i = 1; i < (FHT_N/2) ; i++){
//        Serial.print(i);
//        Serial.print(" ");
//        Serial.println(fht_lin_out[i]);
//      }
      // Finds maximum of frequencies
      for( int i = 1; i < (FHT_N/2); i++){
        
        int x = fht_lin_out[i];
        if( x > xmax){
          xmax = x;
          j = i;
        }
      }
//      Serial.print("Max: ");
//      Serial.print(xmax);
//      Serial.print(":");
//        Serial.println(j);
        Serial.print("a");
      switch(j){
        case 2:
//          Serial.println("Up");
          Serial.println("0");
          break;
        case 3:
//          Serial.println("Left");
          Serial.println("1");
          break;
        case 4:
//          Serial.println("Right");
          Serial.println("2");
          break;
        case 5:
//          Serial.println("Down");
          Serial.println("3");
          break;
        case 7: 
          Serial.println("4");
          break;
//        case 9:
//          Serial.println("e");
//          break;
        default:
          break; 
      }
      xmax = 0;
      j = 0;
      delay(500);
    }          
}
