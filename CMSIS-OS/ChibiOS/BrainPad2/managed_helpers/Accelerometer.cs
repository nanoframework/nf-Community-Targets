using System;
using Windows.Devices.I2c;

namespace FirmwareSelectors
{
   public class Accelerometer
    {
        private I2cDevice device;

        private byte[] buffer1 = new byte[1];

        private byte[] buffer2 = new byte[2];

        public bool EnableFullRange
        {
            get;
            set;
        }

        public Accelerometer()
        {

            device = I2cDevice.FromId("I2C1", new I2cConnectionSettings(28)
            {
                BusSpeed = I2cBusSpeed.FastMode,
                SharingMode = I2cSharingMode.Exclusive
            });

            I2cConnectionSettings i2cConnectionSetting = new I2cConnectionSettings(28)
            {
                SharingMode = I2cSharingMode.Shared,
                BusSpeed = I2cBusSpeed.FastMode
            };

            this.WriteRegister(42, 1);
        }



        private int ReadAxis(byte register)
        {
            this.ReadRegisters(register, this.buffer2);
            double num = (double)(this.buffer2[0] << 2 | this.buffer2[1] >> 6);
            if (num > 511)
            {
                num -= 1024;
            }
            int num1 = (int)(num / 256 * 100);
            if (this.EnableFullRange)
            {
                return num1;
            }
            if (num1 > 100)
            {
                return 100;
            }
            if (num1 < -100)
            {
                return -100;
            }
            return num1;
        }

        private void ReadRegisters(byte register, byte[] data)
        {
            this.buffer1[0] = register;
            this.device.WriteRead(this.buffer1, data);
        }

        public int ReadX()
        {
            return this.ReadAxis(3);
        }

        public int ReadY()
        {
            return -1 * this.ReadAxis(1);
        }

        public int ReadZ()
        {
            return -1 * this.ReadAxis(5);
        }

        private void WriteRegister(byte register, byte data)
        {
            this.buffer2[0] = register;
            this.buffer2[1] = data;
            this.device.Write(this.buffer2);
        }
    }
}
