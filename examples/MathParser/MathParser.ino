/*
Title: Sample Application based on TinyExpr library
Author: Rudranand Sahu
Date: 2021-06-05
*/

#include <tinyexpr.h>

const int buflen = 100;
int bufcnt = 0;
char buf[buflen];
int error;

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to TinyExpr demo");
}

void loop() {
  if(Serial.available()){
    char c = Serial.read();
    if(c=='\r' || c=='\n' || c==';'){
      if(bufcnt==0)
        return;
      if(bufcnt < buflen-1){
        buf[bufcnt] = '\0';
        Serial.println("Parsing Expression...");
        Serial.println(buf);
        double res = te_interp(buf, &error);
        if(error == 0){
          Serial.print("Result: ");
          Serial.println(res, 6);
        }
        else{
          while(--error) Serial.print(' ');
          Serial.println("^~~");
          Serial.println("Error in expression");
        }
      }
      else{
        Serial.println("Expression too long");
      }
      bufcnt = 0;
    }
    else {
      if(bufcnt < buflen-1){
        buf[bufcnt] = c;
      }
      bufcnt++;
    }
  }
}
