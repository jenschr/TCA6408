# TCA6408
Very simple library and example for this I2C-based I/O expander

Tested with Teensy 3.2 and Particle Photon. Should work fine for all Arduino-like MCU's.

## Usage
Create an instance:

    TCA6408 ioExpanderInputs;

Set it up to use all ports as inputs:

    void setup() {
        ioExpanderInputs.begin( TCA6408_ADDR1 ); // Setup on I2C address 0x20
        ioExpanderInputs.writeByte( 0xFF, TCA6408_CONFIGURATION ); // set all channels as outputs (B111111)
    }

Read the inputs in the main loop

    void loop() {
        uint8_t input_values;// = ioExpanderInputs.readInput(1);
        ioExpanderInputs.readByte(&input_values, TCA6408_INPUT);
    }

To setup as 8 output ports, use this syntax:

    void setup() {
        ioExpanderOut.begin( TCA6408_ADDR1 );
        ioExpanderOut.writeByte( 0x00, TCA6408_CONFIGURATION ); // set all channels as outputs
    }
    
    void loop() {
        setExpanderOutput( 1, 1); // Turn on the first output
        setExpanderOutput( 3, 1); // Turn on the third output
        delay(1000);
        ioExpanderOut.writeByte(0x0, TCA6408_OUTPUT); // turn all off
        delay(1000);
    }
    
    void setExpanderOutput(uint8_t output_num, uint8_t value)
    {
        uint8_t output_values;
        ioExpanderOut.readByte(&output_values, TCA6408_OUTPUT); // Get current values
        
        // Update values
        if (value){
            output_values |= (1 << output_num);
        } else {
            output_values &= ~(1 << output_num);
        }
        
        ioExpanderOut.writeByte(output_values, TCA6408_OUTPUT); // Write values to IO-expander
    }
