using System;
using System.Threading;
using Windows.Devices.Pwm;

namespace FirmwareSelectors
{
    class Buzzer
    {
        private PwmController controller;

        private PwmPin buzz;

        public Buzzer()
        {
            this.controller = PwmController.FromId("TIM4"); 
            this.buzz = controller.OpenPin(24);
        }

        public void Beep()
        {
            this.StartBuzzing(2500);
            Thread.Sleep(20);
            this.StopBuzzing();
        }
    
        public void StartBuzzing(double frequency)
        {
            this.StopBuzzing();
            if (frequency > 0)
            {
                this.controller.SetDesiredFrequency(frequency);
                this.buzz.Start();
                this.buzz.SetActiveDutyCyclePercentage(0.5);
            }
        }

        public void StopBuzzing()
        {
            this.buzz.Stop();
        }

   
    }
}