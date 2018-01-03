## Preparation of the board ##

The board used in this community contribution has its ST-LINK part cut-off. This will effectively remove the 8 MHz x-tal for the HSE as well. In order to use an HSE x-tal again we have to prepare the board. This can be read in user manual UM1724 on page 24, for the manual itself visit http://www.st.com and search for NUCLEO-F411RE. You can visit the MBED developer site at https://developer.mbed.org/platforms/ST-Nucleo-F411RE/ for references to pin outs, supported shields and more detailed info on the board.

After the board preparation, JP5 has to be set to use the E5V and not the U5V. Furthermore I prepared a custom made USB cable by cutting off one end and figuring out the required D+, D-, 5V and GND. These need to be connected as follows:

USB V5  ->  E5V on CN7
USB GND ->  GND on CN7
USB D-  ->  PA11 on CN10 (outer row 7th pin from top)
USB D+  ->  PA12 on CN10 (outer row 6th pin from top)

Once these are connected and we shorten BOOT0 pin on CN7 and +3.3V (pin above that, so pin 5, 7) with a jumper and plug in the other end of the USB cable into a PC it will boot in DFU mode. Here you can use the ST Utilities to get the image made to the FLASH of the MCU. 

You can basically follow these steps:

- Get the sources to your PC by forking, cloning the repository (make sure to include the sub-module)
- Run vscode on the repository folder
- Prepare the cmake-variants.json in the repository root
- Select the proper build type in VS Code, let it run and once it is finished hit F7 to compile
- Once the compile has been successfull, you will have all kinds of binaries in you build folder
- Now use the DfuFileMgr to start generating a DFU file. 
- Set the device productid to 0x5740 and the version to 0x0200
- Click the Multi BIN button and browse for the nanoBooter.bin image and set the address to 0x08000000, hit Add to list button
- Browse again for the nanoCLR.bin image and, for a start, set the address to 0x08008000, hit Add to list button
- You should now have two entries in your list. Click OK to continue
- Optionally you can give your Target a meaningful name so later on you can recognize it
- Generate the DFU file and give it a meaningful name, remember the name and location.
- Close the DfuFileMgr if it is not already closed

Now we have the DFU file and the NUCLEO board in DFU mode, we can start burning the generated DFU file (download) to FLASH.

- Start the ST DFU Tester program
- You should see a device being in DFU Mode
- Choose the Protocol tab at the top of the window
- Select in the Operation action list Erase
- Click on Create from MAP
- Click on Go, after some seconds the Erase process will complete
- Now click on Load DFU file, browse and select the DFU file as made according to the steps further above
- Once loaded, some recognizable names should be visible in the DFU Tester window
- Set the Operation action to Download and click on the Go button
- After some time the images are downloaded, burned to flash

After this all has been successful, remove the BOOT0 Jumper and press the black button on the NUCLEO board to reset. Now watch the green LED LD2 on the board, this should be on for approximately one second and than start to blink at a rather fast rate.

If you manage to get the nf-ANT to run it will show you the FLASH MAP organization along with some text identifying the NUCLEO board.

You can have a look at and make yourself familiar with the various aspects of this community build.

**NOTE: This configuration was successfully tested in a NUCLEO_F411RE board with the ST-LINK cut off using the MCUs PA11, PA12 as the USB connection.**
