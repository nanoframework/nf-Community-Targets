using System;
using Windows.Devices.Adc;


namespace FirmwareSelectors
{
    class TemperatureSensor
    {
        private AdcChannel input = AdcController.GetDefault().OpenChannel(1);
        private readonly int voltage = 3300;

        public TemperatureSensor()
        {
        }

        public double ReadTemperatureInCelsius()
        {
            double num = 0;
            for (int i = 0; i < 10; i++)
            {
                num += this.input.ReadRatio();
            }
            num /= 10;
            return (num * (double)this.voltage - 400) / 19.5;
        }

        public double ReadTemperatureInFahrenheit()
        {
            return 1.8 * this.ReadTemperatureInCelsius() + 32;
        }

    }
}
