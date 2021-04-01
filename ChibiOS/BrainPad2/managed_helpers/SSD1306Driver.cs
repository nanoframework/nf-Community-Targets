/*
   modified driver to work with nanoFramework

   https://github.com/BeranekCZ/NETMF-Utils/blob/master/NETMF-Utils/Displays/SSD1306.cs


 */

using System;
using System.Diagnostics;
using Windows.Devices.I2c;
using System.Threading;


namespace nanoFramework.Driver.SSD1306
{
    public class SSD1306
    {

        private readonly int _width;
        private readonly int _height;
        private readonly int _pages;
        private byte[] buffer;
       // private int _timeout = 200;
        private bool _externalVcc = false;

        private I2cDevice _device;


        public int Width
        {
            get
            {
                return _width;
            }
        }

        public int Height
        {
            get
            {
                return _height;
            }
        }

        public SSD1306(string deviceName, int width = 128, int height = 64, int slaveaddresses=0x3C)
        {
            var device = I2cDevice.FromId(deviceName, new I2cConnectionSettings(slaveaddresses)
            {
                BusSpeed = I2cBusSpeed.StandardMode,
                SharingMode = I2cSharingMode.Shared
            });


            this._device = device;
            this._width = width;
            this._height = height;
            this._pages = _height / 8;
            buffer = new byte[width * _pages];

        }

        public void Clear()
        {
            for (int i = 0; i < buffer.Length; i++)
            {
                buffer[i] = 0;
            }
        }

        private void send(byte data)
        {
            byte[] toWrite = new byte[1];
            toWrite[0] = data;

            this._device.Write(toWrite);
        }

        private void send(byte[] data)
        {
            this._device.Write(data);
        }

        private void sendCommand(byte cmd)
        {
            // Co = 0, D/C = 0
            send(new byte[] { 0x00, cmd });
        }

        private void sendData(byte data)
        {
            // Co = 0, D/C = 1
            send(new byte[] { 0x40, data });
        }

        public void Init()
        {
            // Init sequence for 128x64 OLED module
            sendCommand(0xae);                      // 0xAE display off
            sendCommand(0xD5);                      // 0xD5 set display clock div.
            sendCommand(0x80);                      // the suggested ratio 0x80
            sendCommand(0xA8);                      // 0xA8 set multiplex
            sendCommand(0x3F);
            sendCommand(0xD3);                      // 0xD3 set display offset
            sendCommand(0x0);                       // no offset
            sendCommand(0x40 | 0x0);                // line #0 set display start line
            sendCommand(0x8D);                      // 0x8D charge pump
            if (_externalVcc)
            { sendCommand(0x10); }                  //disable charge pump
            else
            { sendCommand(0x14); }                  //enable charge pump
            sendCommand(0x20);                      // 0x20 set memory address mode
            sendCommand(0x00);                      // 0x0 horizontal addressing mode
            sendCommand(0xA0 | 0x1);                // set segment re-map
            sendCommand(0xc8);                      // set com output scan direction
            sendCommand(0xDA);                      // 0xDA set COM pins HW configuration
            sendCommand(0x12);
            sendCommand(0x81);                      // 0x81 Set Contrast Control for BANK0
            if (_externalVcc)
            { sendCommand(0x9F); }
            else
            { sendCommand(0xCF); }
            sendCommand(0xd9);                      // 0xd9 Set Pre-charge Period
            if (_externalVcc)
            { sendCommand(0x22); }
            else
            { sendCommand(0xF1); }
            sendCommand(0xDB);                      // 0xDB Set VCOMH Deselect Level
            sendCommand(0x40);                      // set display start line
            sendCommand(0xA4);                      // 0xA4 display ON
            sendCommand(0xA6);                      // 0xA6 set normal display


            sendCommand(0xAF);                      //--turn on oled panel

            //Thread.Sleep(100);
        }

        /// <summary>
        /// Send buffer to display
        /// </summary>
        public void Display()
        {
            //set column address
            sendCommand(0x21);
            sendCommand(0);
            sendCommand((byte)(_width - 1));

            //set page address
            sendCommand(0x22);
            sendCommand(0);
            sendCommand((byte)(_pages - 1));

            for (ushort i = 0; i < buffer.Length; i = (ushort)(i + 16))
            {
                sendCommand(0x40);
                SendArray(buffer, i, (ushort)(i + 16));
            }
        }

        /// <summary>
        /// Coordinates start with index 0
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="colored">True = turn on pixel, false = turn off pixel</param>
        public void DrawPixel(int x, int y, bool colored)
        {
            DrawPixel((byte)x, (byte)y, colored);
        }

        /// <summary>
        /// Coordinates start with index 0
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="colored">True = turn on pixel, false = turn off pixel</param>
        public void DrawPixel(byte x, byte y, bool colored)
        {
            if (x < 0 || x >= _width || y < 0 || y >= _height)
            {
                Debug.WriteLine("DrawPixel error: Out of borders");
                return;
            }
            int index = y / 8 * _width + x;
            if (colored) buffer[index] = (byte)(buffer[index] | (byte)(1 << (y % 8)));
            else buffer[index] = (byte)(buffer[index] & ~(byte)(1 << (y % 8)));
        }

        //public void DrawLine(int x0, int y0, int x1, int y1, bool colored = true)
        //{
        //    DrawLine(x0, y0, x1, y1, colored);
        //}

        public void DrawHLine(int x0, int y0, int w, bool colored = true)
        {
            DrawLine(x0, y0, x0 + w - 1, y0, colored);
        }

        public void DrawVLine(int x0, int y0, int h, bool colored = true)
        {
            DrawLine(x0, y0, x0, y0 + h - 1, colored);
        }

        /// <summary>
        /// Source http://ericw.ca/notes/bresenhams-line-algorithm-in-csharp.html
        /// </summary>
        /// <param name="x0"></param>
        /// <param name="y0"></param>
        /// <param name="x1"></param>
        /// <param name="y1"></param>
        /// <param name="colored"></param>
        public void DrawLine(int x0, int y0, int x1, int y1, bool colored = true)
        {
            bool steep = System.Math.Abs(y1 - y0) > System.Math.Abs(x1 - x0);
            if (steep)
            {
                int t;
                t = x0; // swap x0 and y0
                x0 = y0;
                y0 = t;
                t = x1; // swap x1 and y1
                x1 = y1;
                y1 = t;
            }
            if (x0 > x1)
            {
                int t;
                t = x0; // swap x0 and x1
                x0 = x1;
                x1 = t;
                t = y0; // swap y0 and y1
                y0 = y1;
                y1 = t;
            }
            int dx = x1 - x0;
            int dy = System.Math.Abs(y1 - y0);
            int error = dx / 2;
            int ystep = (y0 < y1) ? 1 : -1;
            int y = y0;
            for (int x = x0; x <= x1; x++)
            {
                DrawPixel((steep ? y : x), (steep ? x : y), colored);
                error = error - dy;
                if (error < 0)
                {
                    y += ystep;
                    error += dx;
                }
            }

        }


        public void DrawCircle(int centerX, int centerY, int radius, bool colored = true)
        {
            radius--;
            int d = (5 - radius * 4) / 4;
            int x = 0;
            int y = radius;
            do
            {

                DrawPixel(centerX + x, centerY + y, colored);
                DrawPixel(centerX + x, centerY - y, colored);
                DrawPixel(centerX - x, centerY + y, colored);
                DrawPixel(centerX - x, centerY - y, colored);
                DrawPixel(centerX + y, centerY + x, colored);
                DrawPixel(centerX + y, centerY - x, colored);
                DrawPixel(centerX - y, centerY + x, colored);
                DrawPixel(centerX - y, centerY - x, colored);
                if (d < 0)
                {
                    d += 2 * x + 1;
                }
                else
                {
                    d += 2 * (x - y) + 1;
                    y--;
                }
                x++;

            } while (x <= y);
        }

        public void DrawFilledCircle(int centerX, int centerY, int radius, bool colored = true)
        {
            radius--;
            int d = (5 - radius * 4) / 4;
            int x = 0;
            int y = radius;
            do
            {
                DrawLine(centerX + x, centerY + y, centerX - x, centerY + y, colored);
                DrawLine(centerX + x, centerY - y, centerX - x, centerY - y, colored);

                DrawLine(centerX - y, centerY + x, centerX + y, centerY + x, colored);
                DrawLine(centerX - y, centerY - x, centerX + y, centerY - x, colored);
                if (d < 0)
                {
                    d += 2 * x + 1;
                }
                else
                {
                    d += 2 * (x - y) + 1;
                    y--;
                }
                x++;
            } while (x <= y);
        }

        public void DrawRectangle(int xLeft, int yTop, int width, int height, bool colored = true)
        {
            width--;
            height--;
            DrawLine(xLeft, yTop, xLeft + width, yTop, colored);
            DrawLine(xLeft + width, yTop, xLeft + width, yTop + height, colored);
            DrawLine(xLeft + width, yTop + height, xLeft, yTop + height, colored);
            DrawLine(xLeft, yTop, xLeft, yTop + height, colored);

        }

        public void DrawFilledRectangle(int xLeft, int yTop, int width, int height, bool colored = true)
        {
            width--;
            height--;
            for (int i = 0; i <= height; i++)
            {
                DrawLine(xLeft, yTop + i, xLeft + width, yTop + i, colored);
            }
        }

        //Draw a rounded rectangle
        public void DrawRoundRect(int x, int y, int w, int h, int r, bool colored = true)
        {
            // smarter version
            DrawHLine(x + r, y, w - 2 * r, colored); // Top
            DrawHLine(x + r, y + h - 1, w - 2 * r, colored); // Bottom
            DrawVLine(x, y + r, h - 2 * r, colored); // Left
            DrawVLine(x + w - 1, y + r, h - 2 * r, colored); // Right
            // draw four corners
            drawCircleHelper(x + r, y + r, r, 1, colored);
            drawCircleHelper(x + w - r - 1, y + r, r, 2, colored);
            drawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, colored);
            drawCircleHelper(x + r, y + h - r - 1, r, 8, colored);
        }

        public void DrawRoundFilledRect(int x, int y, int w, int h, int r, bool colored = true)
        {

            // smarter version
            //fillRect(x+r, y, w-2*r, h, color);
            for (int i = x + r; i < x + r + (w - 2 * r); i++)
            {
                DrawVLine(i, y, h, colored);
            }

            // draw four corners
            fillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, colored);
            fillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1, colored);

        }

        private void drawCircleHelper(int x0, int y0, int r, int cornername, bool colored = true)
        {
            int f = 1 - r;
            int ddF_x = 1;
            int ddF_y = -2 * r;
            int x = 0;
            int y = r;

            while (x < y)
            {
                if (f >= 0)
                {
                    y--;
                    ddF_y += 2;
                    f += ddF_y;
                }
                x++;
                ddF_x += 2;
                f += ddF_x;
                if ((cornername & 0x4) != 0)
                {
                    DrawPixel(x0 + x, y0 + y, colored);
                    DrawPixel(x0 + y, y0 + x, colored);
                }
                if ((cornername & 0x2) != 0)
                {
                    DrawPixel(x0 + x, y0 - y, colored);
                    DrawPixel(x0 + y, y0 - x, colored);
                }
                if ((cornername & 0x8) != 0)
                {
                    DrawPixel(x0 - y, y0 + x, colored);
                    DrawPixel(x0 - x, y0 + y, colored);
                }
                if ((cornername & 0x1) != 0)
                {
                    DrawPixel(x0 - y, y0 - x, colored);
                    DrawPixel(x0 - x, y0 - y, colored);
                }
            }
        }

        private void fillCircleHelper(int x0, int y0, int r, int cornername, int delta, bool colored)
        {

            int f = 1 - r;
            int ddF_x = 1;
            int ddF_y = -2 * r;
            int x = 0;
            int y = r;

            while (x < y)
            {
                if (f >= 0)
                {
                    y--;
                    ddF_y += 2;
                    f += ddF_y;
                }
                x++;
                ddF_x += 2;
                f += ddF_x;

                if ((cornername & 0x1) != 0)
                {
                    DrawVLine(x0 + x, y0 - y, 2 * y + 1 + delta, colored);
                    DrawVLine(x0 + y, y0 - x, 2 * x + 1 + delta, colored);
                }
                if ((cornername & 0x2) != 0)
                {
                    DrawVLine(x0 - x, y0 - y, 2 * y + 1 + delta, colored);
                    DrawVLine(x0 - y, y0 - x, 2 * x + 1 + delta, colored);
                }
            }
        }


        //// Draw a triangle
        public void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, bool colored = true)
        {
            DrawLine(x0, y0, x1, y1, colored);
            DrawLine(x1, y1, x2, y2, colored);
            DrawLine(x2, y2, x0, y0, colored);
        }

        public void DrawChar(int x, int y, char c, int size = 1, bool colored = true)
        {

            if ((x >= _width) || // Clip right
               (y >= _height) || // Clip bottom
               ((x + 6 * size - 1) < 0) || // Clip left
               ((y + 8 * size - 1) < 0))   // Clip top
                return;

            for (byte i = 0; i < 6; i++)
            {
                byte line;
                if (i == 5)
                    line = 0x0;
                else
                    //line = pgm_read_byte(font+(c*5)+i);
                    line = Glcfont.MEM[(c * 5) + i];

                for (byte j = 0; j < 8; j++)
                {
                    if ((line & 0x1) != 0)
                    {
                        if (size == 1) // default size
                            DrawPixel(x + i, y + j, colored);
                        else
                        {  // big size
                            DrawFilledRectangle(x + (i * size), y + (j * size), size, size, colored);
                        }
                    }
                    else
                    {
                        if (size == 1) // default size
                            DrawPixel(x + i, y + j, !colored);
                        else
                        {  // big size
                            DrawFilledRectangle(x + i * size, y + j * size, size, size, !colored);
                        }
                    }
                    line >>= 1;
                }
            }
        }



        public void DrawText(int x, int y, char[] text, int size = 1, bool colored = true, bool wrap = true)
        {
            int cursorX = x;
            int cursorY = y;


            foreach (char c in text)
            {
                if (c == '\n')
                {
                    cursorY += size * 8;
                    cursorX = 0;
                }
                else if (c == '\r')
                {
                    // skip em
                }
                else
                {
                    DrawChar(cursorX, cursorY, c, size, colored);
                    cursorX += size * 6;
                    if (wrap && (cursorX > (_width - size * 6)))
                    {
                        cursorY += size * 8;
                        cursorX = 0;
                    }
                }
            }

        }


        private bool isInScreen(int x, int y)
        {
            if (x < 0 || x >= _width) return false;
            if (y < 0 || y >= _height) return false;
            return true;
        }

        private void SendArray(byte[] array, ushort startIndex, ushort endIndex)
        {
            for (int i = startIndex; i < endIndex; i++)
            {
                sendData(array[i]);
            }
        }

        public void SetContrast(byte value = 0xFF)
        {
            //sendCommand(new byte[]{0x81,value});
            sendCommand(0x81);
            sendCommand(value);
        }

        public void SetInverseDisplay(bool inverse)
        {
            if (inverse) sendCommand(0xA7);
            else sendCommand(0xA6);
        }

        public void SetEntireDisplayON(bool setOn)
        {
            if (setOn) sendCommand(0xA5);
            else sendCommand(0xA4);
        }

        public void SetMemoryAddressingMode()
        {
            //TODO another modes
            sendCommand(0x20);
            sendCommand(0x00);
        }

        private void setColumnAddress(byte start = 0, byte end = 127)
        {
            //sendCommand(new byte[] { 0x21, start, end });
            sendCommand(0x21);
            sendCommand(start);
            sendCommand(end);
        }

        private void setPageAddress(byte start = 0, byte end = 7)
        {
            sendCommand(0x22);
            sendCommand(start);
            sendCommand(end);
        }

        /// <summary>
        /// Start horizontall scrolling
        /// </summary>
        /// <param name="left">true = scrolling to left, false = scrollong to right</param>
        /// <param name="start">Start page index</param>
        /// <param name="stop">Stop page index</param>
        public void StartScrollHorizontally(bool left, byte start, byte stop)
        {
            DeactivateScroll();

            if (left) sendCommand(0x27);
            else sendCommand(0x26);

            sendCommand(0x00);
            sendCommand(start); //start page index
            sendCommand(0x00);  //scroll interval in frames
            sendCommand(stop);  //end page index
            sendCommand(0x00);
            sendCommand(0xFF);

            sendCommand(0x2F);  //start scroll
        }

        /// <summary>
        /// Start vert. and hor. scrolling == diagonal
        /// </summary>
        /// <param name="left">true = scrolling to left, false = scrollong to right</param>
        /// <param name="start">Start page index</param>
        /// <param name="stop">Stop page index</param>
        /// <param name="verticalOffset"></param>
        public void StartScrollVerticallyHorizontally(bool left, byte start, byte stop, byte verticalOffset)
        {
            DeactivateScroll();

            if (left) sendCommand(0x2A);
            else sendCommand(0x29);

            sendCommand(0x00);
            sendCommand(start); //start page index
            sendCommand(0x00);  //scroll interval in frames
            sendCommand(stop);  //end page index
            sendCommand(verticalOffset);  //vertical scrolling offset

            sendCommand(0x2F);  //start scroll
        }

        /// <summary>
        /// Turn off scrolling
        /// </summary>
        public void DeactivateScroll()
        {
            sendCommand(0x2E);
        }

        public void SetVerticalScrollArea(byte topRow, byte numberOfRows)
        {
            DeactivateScroll();
            sendCommand(0xA3);
            sendCommand(topRow);
            sendCommand(numberOfRows);
            sendCommand(0x2F);
        }
    }

    public static class Glcfont
    {
        public static readonly byte[] MEM = {
            0x00, 0x00, 0x00, 0x00, 0x00,
            0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
            0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
            0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
            0x18, 0x3C, 0x7E, 0x3C, 0x18,
            0x1C, 0x57, 0x7D, 0x57, 0x1C,
            0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
            0x00, 0x18, 0x3C, 0x18, 0x00,
            0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
            0x00, 0x18, 0x24, 0x18, 0x00,
            0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
            0x30, 0x48, 0x3A, 0x06, 0x0E,
            0x26, 0x29, 0x79, 0x29, 0x26,
            0x40, 0x7F, 0x05, 0x05, 0x07,
            0x40, 0x7F, 0x05, 0x25, 0x3F,
            0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
            0x7F, 0x3E, 0x1C, 0x1C, 0x08,
            0x08, 0x1C, 0x1C, 0x3E, 0x7F,
            0x14, 0x22, 0x7F, 0x22, 0x14,
            0x5F, 0x5F, 0x00, 0x5F, 0x5F,
            0x06, 0x09, 0x7F, 0x01, 0x7F,
            0x00, 0x66, 0x89, 0x95, 0x6A,
            0x60, 0x60, 0x60, 0x60, 0x60,
            0x94, 0xA2, 0xFF, 0xA2, 0x94,
            0x08, 0x04, 0x7E, 0x04, 0x08,
            0x10, 0x20, 0x7E, 0x20, 0x10,
            0x08, 0x08, 0x2A, 0x1C, 0x08,
            0x08, 0x1C, 0x2A, 0x08, 0x08,
            0x1E, 0x10, 0x10, 0x10, 0x10,
            0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
            0x30, 0x38, 0x3E, 0x38, 0x30,
            0x06, 0x0E, 0x3E, 0x0E, 0x06,
            0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x5F, 0x00, 0x00,
            0x00, 0x07, 0x00, 0x07, 0x00,
            0x14, 0x7F, 0x14, 0x7F, 0x14,
            0x24, 0x2A, 0x7F, 0x2A, 0x12,
            0x23, 0x13, 0x08, 0x64, 0x62,
            0x36, 0x49, 0x56, 0x20, 0x50,
            0x00, 0x08, 0x07, 0x03, 0x00,
            0x00, 0x1C, 0x22, 0x41, 0x00,
            0x00, 0x41, 0x22, 0x1C, 0x00,
            0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
            0x08, 0x08, 0x3E, 0x08, 0x08,
            0x00, 0x80, 0x70, 0x30, 0x00,
            0x08, 0x08, 0x08, 0x08, 0x08,
            0x00, 0x00, 0x60, 0x60, 0x00,
            0x20, 0x10, 0x08, 0x04, 0x02,
            0x3E, 0x51, 0x49, 0x45, 0x3E,
            0x00, 0x42, 0x7F, 0x40, 0x00,
            0x72, 0x49, 0x49, 0x49, 0x46,
            0x21, 0x41, 0x49, 0x4D, 0x33,
            0x18, 0x14, 0x12, 0x7F, 0x10,
            0x27, 0x45, 0x45, 0x45, 0x39,
            0x3C, 0x4A, 0x49, 0x49, 0x31,
            0x41, 0x21, 0x11, 0x09, 0x07,
            0x36, 0x49, 0x49, 0x49, 0x36,
            0x46, 0x49, 0x49, 0x29, 0x1E,
            0x00, 0x00, 0x14, 0x00, 0x00,
            0x00, 0x40, 0x34, 0x00, 0x00,
            0x00, 0x08, 0x14, 0x22, 0x41,
            0x14, 0x14, 0x14, 0x14, 0x14,
            0x00, 0x41, 0x22, 0x14, 0x08,
            0x02, 0x01, 0x59, 0x09, 0x06,
            0x3E, 0x41, 0x5D, 0x59, 0x4E,
            0x7C, 0x12, 0x11, 0x12, 0x7C,
            0x7F, 0x49, 0x49, 0x49, 0x36,
            0x3E, 0x41, 0x41, 0x41, 0x22,
            0x7F, 0x41, 0x41, 0x41, 0x3E,
            0x7F, 0x49, 0x49, 0x49, 0x41,
            0x7F, 0x09, 0x09, 0x09, 0x01,
            0x3E, 0x41, 0x41, 0x51, 0x73,
            0x7F, 0x08, 0x08, 0x08, 0x7F,
            0x00, 0x41, 0x7F, 0x41, 0x00,
            0x20, 0x40, 0x41, 0x3F, 0x01,
            0x7F, 0x08, 0x14, 0x22, 0x41,
            0x7F, 0x40, 0x40, 0x40, 0x40,
            0x7F, 0x02, 0x1C, 0x02, 0x7F,
            0x7F, 0x04, 0x08, 0x10, 0x7F,
            0x3E, 0x41, 0x41, 0x41, 0x3E,
            0x7F, 0x09, 0x09, 0x09, 0x06,
            0x3E, 0x41, 0x51, 0x21, 0x5E,
            0x7F, 0x09, 0x19, 0x29, 0x46,
            0x26, 0x49, 0x49, 0x49, 0x32,
            0x03, 0x01, 0x7F, 0x01, 0x03,
            0x3F, 0x40, 0x40, 0x40, 0x3F,
            0x1F, 0x20, 0x40, 0x20, 0x1F,
            0x3F, 0x40, 0x38, 0x40, 0x3F,
            0x63, 0x14, 0x08, 0x14, 0x63,
            0x03, 0x04, 0x78, 0x04, 0x03,
            0x61, 0x59, 0x49, 0x4D, 0x43,
            0x00, 0x7F, 0x41, 0x41, 0x41,
            0x02, 0x04, 0x08, 0x10, 0x20,
            0x00, 0x41, 0x41, 0x41, 0x7F,
            0x04, 0x02, 0x01, 0x02, 0x04,
            0x40, 0x40, 0x40, 0x40, 0x40,
            0x00, 0x03, 0x07, 0x08, 0x00,
            0x20, 0x54, 0x54, 0x78, 0x40,
            0x7F, 0x28, 0x44, 0x44, 0x38,
            0x38, 0x44, 0x44, 0x44, 0x28,
            0x38, 0x44, 0x44, 0x28, 0x7F,
            0x38, 0x54, 0x54, 0x54, 0x18,
            0x00, 0x08, 0x7E, 0x09, 0x02,
            0x18, 0xA4, 0xA4, 0x9C, 0x78,
            0x7F, 0x08, 0x04, 0x04, 0x78,
            0x00, 0x44, 0x7D, 0x40, 0x00,
            0x20, 0x40, 0x40, 0x3D, 0x00,
            0x7F, 0x10, 0x28, 0x44, 0x00,
            0x00, 0x41, 0x7F, 0x40, 0x00,
            0x7C, 0x04, 0x78, 0x04, 0x78,
            0x7C, 0x08, 0x04, 0x04, 0x78,
            0x38, 0x44, 0x44, 0x44, 0x38,
            0xFC, 0x18, 0x24, 0x24, 0x18,
            0x18, 0x24, 0x24, 0x18, 0xFC,
            0x7C, 0x08, 0x04, 0x04, 0x08,
            0x48, 0x54, 0x54, 0x54, 0x24,
            0x04, 0x04, 0x3F, 0x44, 0x24,
            0x3C, 0x40, 0x40, 0x20, 0x7C,
            0x1C, 0x20, 0x40, 0x20, 0x1C,
            0x3C, 0x40, 0x30, 0x40, 0x3C,
            0x44, 0x28, 0x10, 0x28, 0x44,
            0x4C, 0x90, 0x90, 0x90, 0x7C,
            0x44, 0x64, 0x54, 0x4C, 0x44,
            0x00, 0x08, 0x36, 0x41, 0x00,
            0x00, 0x00, 0x77, 0x00, 0x00,
            0x00, 0x41, 0x36, 0x08, 0x00,
            0x02, 0x01, 0x02, 0x04, 0x02,
            0x3C, 0x26, 0x23, 0x26, 0x3C,
            0x1E, 0xA1, 0xA1, 0x61, 0x12,
            0x3A, 0x40, 0x40, 0x20, 0x7A,
            0x38, 0x54, 0x54, 0x55, 0x59,
            0x21, 0x55, 0x55, 0x79, 0x41,
            0x22, 0x54, 0x54, 0x78, 0x42, // a-umlaut
	        0x21, 0x55, 0x54, 0x78, 0x40,
            0x20, 0x54, 0x55, 0x79, 0x40,
            0x0C, 0x1E, 0x52, 0x72, 0x12,
            0x39, 0x55, 0x55, 0x55, 0x59,
            0x39, 0x54, 0x54, 0x54, 0x59,
            0x39, 0x55, 0x54, 0x54, 0x58,
            0x00, 0x00, 0x45, 0x7C, 0x41,
            0x00, 0x02, 0x45, 0x7D, 0x42,
            0x00, 0x01, 0x45, 0x7C, 0x40,
            0x7D, 0x12, 0x11, 0x12, 0x7D, // A-umlaut
	        0xF0, 0x28, 0x25, 0x28, 0xF0,
            0x7C, 0x54, 0x55, 0x45, 0x00,
            0x20, 0x54, 0x54, 0x7C, 0x54,
            0x7C, 0x0A, 0x09, 0x7F, 0x49,
            0x32, 0x49, 0x49, 0x49, 0x32,
            0x3A, 0x44, 0x44, 0x44, 0x3A, // o-umlaut
	        0x32, 0x4A, 0x48, 0x48, 0x30,
            0x3A, 0x41, 0x41, 0x21, 0x7A,
            0x3A, 0x42, 0x40, 0x20, 0x78,
            0x00, 0x9D, 0xA0, 0xA0, 0x7D,
            0x3D, 0x42, 0x42, 0x42, 0x3D, // O-umlaut
	        0x3D, 0x40, 0x40, 0x40, 0x3D,
            0x3C, 0x24, 0xFF, 0x24, 0x24,
            0x48, 0x7E, 0x49, 0x43, 0x66,
            0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
            0xFF, 0x09, 0x29, 0xF6, 0x20,
            0xC0, 0x88, 0x7E, 0x09, 0x03,
            0x20, 0x54, 0x54, 0x79, 0x41,
            0x00, 0x00, 0x44, 0x7D, 0x41,
            0x30, 0x48, 0x48, 0x4A, 0x32,
            0x38, 0x40, 0x40, 0x22, 0x7A,
            0x00, 0x7A, 0x0A, 0x0A, 0x72,
            0x7D, 0x0D, 0x19, 0x31, 0x7D,
            0x26, 0x29, 0x29, 0x2F, 0x28,
            0x26, 0x29, 0x29, 0x29, 0x26,
            0x30, 0x48, 0x4D, 0x40, 0x20,
            0x38, 0x08, 0x08, 0x08, 0x08,
            0x08, 0x08, 0x08, 0x08, 0x38,
            0x2F, 0x10, 0xC8, 0xAC, 0xBA,
            0x2F, 0x10, 0x28, 0x34, 0xFA,
            0x00, 0x00, 0x7B, 0x00, 0x00,
            0x08, 0x14, 0x2A, 0x14, 0x22,
            0x22, 0x14, 0x2A, 0x14, 0x08,
            0xAA, 0x00, 0x55, 0x00, 0xAA,
            0xAA, 0x55, 0xAA, 0x55, 0xAA,
            0x00, 0x00, 0x00, 0xFF, 0x00,
            0x10, 0x10, 0x10, 0xFF, 0x00,
            0x14, 0x14, 0x14, 0xFF, 0x00,
            0x10, 0x10, 0xFF, 0x00, 0xFF,
            0x10, 0x10, 0xF0, 0x10, 0xF0,
            0x14, 0x14, 0x14, 0xFC, 0x00,
            0x14, 0x14, 0xF7, 0x00, 0xFF,
            0x00, 0x00, 0xFF, 0x00, 0xFF,
            0x14, 0x14, 0xF4, 0x04, 0xFC,
            0x14, 0x14, 0x17, 0x10, 0x1F,
            0x10, 0x10, 0x1F, 0x10, 0x1F,
            0x14, 0x14, 0x14, 0x1F, 0x00,
            0x10, 0x10, 0x10, 0xF0, 0x00,
            0x00, 0x00, 0x00, 0x1F, 0x10,
            0x10, 0x10, 0x10, 0x1F, 0x10,
            0x10, 0x10, 0x10, 0xF0, 0x10,
            0x00, 0x00, 0x00, 0xFF, 0x10,
            0x10, 0x10, 0x10, 0x10, 0x10,
            0x10, 0x10, 0x10, 0xFF, 0x10,
            0x00, 0x00, 0x00, 0xFF, 0x14,
            0x00, 0x00, 0xFF, 0x00, 0xFF,
            0x00, 0x00, 0x1F, 0x10, 0x17,
            0x00, 0x00, 0xFC, 0x04, 0xF4,
            0x14, 0x14, 0x17, 0x10, 0x17,
            0x14, 0x14, 0xF4, 0x04, 0xF4,
            0x00, 0x00, 0xFF, 0x00, 0xF7,
            0x14, 0x14, 0x14, 0x14, 0x14,
            0x14, 0x14, 0xF7, 0x00, 0xF7,
            0x14, 0x14, 0x14, 0x17, 0x14,
            0x10, 0x10, 0x1F, 0x10, 0x1F,
            0x14, 0x14, 0x14, 0xF4, 0x14,
            0x10, 0x10, 0xF0, 0x10, 0xF0,
            0x00, 0x00, 0x1F, 0x10, 0x1F,
            0x00, 0x00, 0x00, 0x1F, 0x14,
            0x00, 0x00, 0x00, 0xFC, 0x14,
            0x00, 0x00, 0xF0, 0x10, 0xF0,
            0x10, 0x10, 0xFF, 0x10, 0xFF,
            0x14, 0x14, 0x14, 0xFF, 0x14,
            0x10, 0x10, 0x10, 0x1F, 0x00,
            0x00, 0x00, 0x00, 0xF0, 0x10,
            0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
            0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
            0xFF, 0xFF, 0xFF, 0x00, 0x00,
            0x00, 0x00, 0x00, 0xFF, 0xFF,
            0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
            0x38, 0x44, 0x44, 0x38, 0x44,
            0xFC, 0x4A, 0x4A, 0x4A, 0x34, // sharp-s or beta
	        0x7E, 0x02, 0x02, 0x06, 0x06,
            0x02, 0x7E, 0x02, 0x7E, 0x02,
            0x63, 0x55, 0x49, 0x41, 0x63,
            0x38, 0x44, 0x44, 0x3C, 0x04,
            0x40, 0x7E, 0x20, 0x1E, 0x20,
            0x06, 0x02, 0x7E, 0x02, 0x02,
            0x99, 0xA5, 0xE7, 0xA5, 0x99,
            0x1C, 0x2A, 0x49, 0x2A, 0x1C,
            0x4C, 0x72, 0x01, 0x72, 0x4C,
            0x30, 0x4A, 0x4D, 0x4D, 0x30,
            0x30, 0x48, 0x78, 0x48, 0x30,
            0xBC, 0x62, 0x5A, 0x46, 0x3D,
            0x3E, 0x49, 0x49, 0x49, 0x00,
            0x7E, 0x01, 0x01, 0x01, 0x7E,
            0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
            0x44, 0x44, 0x5F, 0x44, 0x44,
            0x40, 0x51, 0x4A, 0x44, 0x40,
            0x40, 0x44, 0x4A, 0x51, 0x40,
            0x00, 0x00, 0xFF, 0x01, 0x03,
            0xE0, 0x80, 0xFF, 0x00, 0x00,
            0x08, 0x08, 0x6B, 0x6B, 0x08,
            0x36, 0x12, 0x36, 0x24, 0x36,
            0x06, 0x0F, 0x09, 0x0F, 0x06,
            0x00, 0x00, 0x18, 0x18, 0x00,
            0x00, 0x00, 0x10, 0x10, 0x00,
            0x30, 0x40, 0xFF, 0x01, 0x01,
            0x00, 0x1F, 0x01, 0x01, 0x1E,
            0x00, 0x19, 0x1D, 0x17, 0x12,
            0x00, 0x3C, 0x3C, 0x3C, 0x3C,
            0x00, 0x00, 0x00, 0x00, 0x00
        };

    }
}