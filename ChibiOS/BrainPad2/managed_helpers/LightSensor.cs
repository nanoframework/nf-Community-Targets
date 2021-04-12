using System;
using Windows.Devices.Adc;

namespace FirmwareSelectors
{
    class LightSensor
    {
        private AdcChannel input = AdcController.GetDefault().OpenChannel(1);

        public LightSensor()
        {

        }

        public int ReadLightLevel()
        {
            return (int)(this.input.ReadRatio() * 100);
        }
    }
}
