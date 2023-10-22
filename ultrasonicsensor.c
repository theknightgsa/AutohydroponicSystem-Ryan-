#include <wiringPi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int Measuredist (int sigpin)
{
    int counter =0;
    
    pinMode(sigpin,OUTPUT);
    
    digitalWrite(sigpin, LOW);
    delay(5);
    digitalWrite(sigpin, HIGH);
    delay(5);
    digitalWrite(sigpin, LOW);
    
    
    
    pinMode(sigpin,INPUT);

    while(digitalRead(sigpin)==0)
    {
	
	}//wait for high reading before counting
	
    while(digitalRead(sigpin)==1) // measuring the pulse (time between next high and proceeding low)
    {
	for(int x=0; x<50;x++)
	{
	    if(1)
	    {
		}
	    }
	counter++; 
}
    
    return counter;
}

int appendHistory(int ultrasonic,int TDS, char* filename)
{
    FILE *fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }
    // write to the text file
    
    
    time_t t;   // not a primitive datatype
    time(&t);
    
    fprintf(fp, "Water distance in inches:%d	TDS PPM:%d	TIME:%s\n", ultrasonic,TDS,ctime(&t));
    fclose(fp);
}

int main(void)
{
    printf("programstarted\n");
    wiringPiSetupGpio();

    
    int sigpin=23;//GPIO 23 a.k.a. pin 16 will be SIG PIN
    
    
    while(1)
    {
    int d= Measuredist(sigpin);
    d*=6;
    d/=1000;
    printf("Measured distance in inches: %d\n",d);
    

    int TDS = 355+(rand() % 50);//implement once I get analog voltage reader

    appendHistory(d,TDS, "sensorHistory.txt");
    
    delay(2000);
    }
    return 0;
}
