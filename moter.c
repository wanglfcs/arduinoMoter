const int STEP = 13;
const int DIR = 12;
long runSpeed = 0;
long runSteps = 0;
long cmdNum;
long runTime = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
}

void loop()
{
  if(Serial.available() > 0)
  {
    //new commander is comming;
    cmdNum = (long)Serial.parseFloat();
    runSpeed = (long)Serial.parseFloat();
    runSteps = (long)Serial.parseFloat();
    switch(cmdNum)
    {
      case 3:
      digitalWrite(DIR, LOW);
      runTime = 1000*runSteps/runSpeed; 
      tone(STEP, runSpeed, runTime);
      break;
      case 4:
      digitalWrite(DIR, HIGH);
      runTime = 1000*runSteps/runSpeed;
      tone(STEP, runSpeed, runTime);
      break;
      case 5:
      noTone(STEP);
      break;
    }
    
  }

}
