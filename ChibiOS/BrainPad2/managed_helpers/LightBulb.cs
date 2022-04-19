using System;
using System.Device.Pwm;
using STM32F4.Pins;

namespace FirmwareSelectors
{
    public class LightBulb
    {
        private PwmPin red;

        private PwmPin green;

        private PwmPin blue;

        public LightBulb()
        {
            PwmController pwmController = PwmController.FromId("TIM3");
            pwmController.SetDesiredFrequency(10000);

            this.red = pwmController.OpenPin(BrainPad2.Light.Red);
            this.green = pwmController.OpenPin(BrainPad2.Light.Greeen);
            this.blue = pwmController.OpenPin(BrainPad2.Light.Blue);

            this.red.Start();
            this.green.Start();
            this.blue.Start();
            this.TurnColor(0, 0, 0);
        }


        public void TurnBlue()
        {
            this.TurnColor(0, 0, 80);
        }

        public void TurnColor(double r, double g, double b)
        {
            if (r < 0 || r > 100)
            {
                throw new ArgumentOutOfRangeException("red", "red must be between zero and one hundred.");
            }
            if (g < 0 || g > 100)
            {
                throw new ArgumentOutOfRangeException("green", "green must be between zero and one hundred.");
            }
            if (b < 0 || b > 100)
            {
                throw new ArgumentOutOfRangeException("blue", "blue must be between zero and one hundred.");
            }
            this.red.SetActiveDutyCyclePercentage(r / 100);
            this.green.SetActiveDutyCyclePercentage(g / 100);
            this.blue.SetActiveDutyCyclePercentage(b / 100);
        }

        public void TurnGreen()
        {
            this.TurnColor(0, 30, 0);
        }

        public void TurnOff()
        {
            this.TurnColor(0, 0, 0);
        }

        public void TurnRed()
        {
            this.TurnColor(40, 0, 0);
        }

        public void TurnWhite()
        {
            this.TurnColor(40, 30, 80);
        }

    }
}
