/**
 * Code de base pour l'utilisation de la shield Arduino LCD de DFRobots (LCD uniquement).
 */

/* Dépendances */
#include <LiquidCrystal.h>


/** Objet LiquidCrystal pour communication avec l'écran LCD */
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


/** Fonction setup() */
void setup() {
 lcd.begin(16, 2);
 lcd.print("HubIS sensor v1.0");
}

/** Fonction loop() */
void loop() {
 lcd.setCursor(0,0);
 lcd.print("Sensor value :");
 lcd.setCursor(6,1);
 lcd.print(int(analogRead(A1)/3.3*5/4));
 delay(1000);
 lcd.clear();
 
 }
