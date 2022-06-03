using System;
using System.Threading;
using System.Device.Gpio;
using System.Diagnostics;
using STM32F4.Pins;
using nanoFramework.Driver.SSD1306;

namespace FirmwareSelectors
{
    public class Program
    {

        public static void Main()
        {
            BrainPad2.AllLedOff();

           // SSD1306 oled = new SSD1306("I2C1", 128, 64, 0x3C);

           // oled.Init();
           // oled.Clear();

           // oled.DrawText(0, 0, "                   ".ToCharArray(), 1);
           // oled.DrawText(0, 20, "              ".ToCharArray(), 1);

           //oled.Display();
            //Thread.Sleep(5000);
           //oled.Clear();

            TemperatureSensor tmpSensor = new TemperatureSensor();
            double tmpCelsious;

             Accelerometer accelerometer = new Accelerometer();
            //LightBulb lightBulb = new LightBulb();

            LightSensor lightSensor = new LightSensor();

            Buzzer buzzer = new Buzzer();



            while (true)
            {
               
                Debug.WriteLine("> Temp C="+tmpSensor.ReadTemperatureInCelsius().ToString());
                Debug.WriteLine("-------------------");

                Debug.WriteLine("X="+ accelerometer.ReadX()+ ",Y="+ accelerometer.ReadY() +",Z="+ accelerometer.ReadZ());
                Debug.WriteLine("Light Lumion = " + lightSensor.ReadLightLevel());

               // buzzer.Beep();
                //buzzer.StartBuzzing(200);
                Thread.Sleep(1000);
                //buzzer.StopBuzzing();

                //oled.Clear();
            
 
            }


        }

        public static int PinNumber(char port, byte pin)
        {
            if (port < 'A' || port > 'J')
                throw new ArgumentException();

            return ((port - 'A') * 16) + pin;
        }
    }
}
