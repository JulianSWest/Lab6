#!/usr/bin/python
import time
import RPi.GPIO as GPIO

# Configure the GPIO to BOARD numbering
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

# Define pin numbers for the LCD and buzzer
E_PULSE = 0.0005
E_DELAY = 0.0005
LCD_RS = 7
LCD_E = 11
LCD_D4 = 12
LCD_D5 = 13
LCD_D6 = 15
LCD_D7 = 16
IR_Sensor = 18
buzzer = 37

# Setup GPIO pins
GPIO.setup(buzzer, GPIO.OUT)
GPIO.setup(LCD_E, GPIO.OUT)  # E
GPIO.setup(LCD_RS, GPIO.OUT) # RS
GPIO.setup(LCD_D4, GPIO.OUT) # DB4
GPIO.setup(LCD_D5, GPIO.OUT) # DB5
GPIO.setup(LCD_D6, GPIO.OUT) # DB6
GPIO.setup(LCD_D7, GPIO.OUT) # DB7
GPIO.setup(IR_Sensor, GPIO.IN)

# Define some device constants
LCD_WIDTH = 16    # Maximum characters per line
LCD_CHR = True
LCD_CMD = False
LCD_LINE_1 = 0x80 # LCD RAM address for the 1st line
LCD_LINE_2 = 0xC0 # LCD RAM address for the 2nd line

def lcd_init():
    """
    Initialize LCD by sending different commands
    """
    lcd_byte(0x33,LCD_CMD) # 110011 Initialise
    lcd_byte(0x32,LCD_CMD) # 110010 Initialise
    lcd_byte(0x06,LCD_CMD) # 000110 Cursor move direction
    lcd_byte(0x0C,LCD_CMD) # 001100 Display On,Cursor Off, Blink Off
    lcd_byte(0x28,LCD_CMD) # 101000 Data length, number of lines, font size
    lcd_byte(0x01,LCD_CMD) # 000001 Clear display
    time.sleep(E_DELAY)

def lcd_byte(bits, mode):
    """
    Convert byte data into bits and send to LCD port
    """
    GPIO.output(LCD_RS, mode) # RS
    
    # High bits
    GPIO.output(LCD_D4, bits & 0x10 == 0x10)
    GPIO.output(LCD_D5, bits & 0x20 == 0x20)
    GPIO.output(LCD_D6, bits & 0x40 == 0x40)
    GPIO.output(LCD_D7, bits & 0x80 == 0x80)
    lcd_toggle_enable()
    
    # Low bits
    GPIO.output(LCD_D4, bits & 0x01 == 0x01)
    GPIO.output(LCD_D5, bits & 0x02 == 0x02)
    GPIO.output(LCD_D6, bits & 0x04 == 0x04)
    GPIO.output(LCD_D7, bits & 0x08 == 0x08)
    lcd_toggle_enable()

def lcd_toggle_enable():
    """
    Toggle the LCD enable pin
    """
    time.sleep(E_DELAY)
    GPIO.output(LCD_E, True)
    time.sleep(E_PULSE)
    GPIO.output(LCD_E, False)
    time.sleep(E_DELAY)

def lcd_string(message, line):
    """
    Print message on the specified line of the LCD
    """
    message = message.ljust(LCD_WIDTH, " ")
    lcd_byte(line, LCD_CMD)

    for i in range(LCD_WIDTH):
        lcd_byte(ord(message[i]), LCD_CHR)

def main():
    """
    Main program block
    """
    lcd_init()

    lcd_string("Welcome", LCD_LINE_1)
    time.sleep(2)

    try:
        while True:
            if GPIO.input(IR_Sensor):
                lcd_string("Obstacle Detected", LCD_LINE_1)
            else:
                lcd_string("Obstacle Removed", LCD_LINE_1)

            time.sleep(1)

    except KeyboardInterrupt:
        # Cleanup GPIO on CTRL+C exit
        GPIO.cleanup()

if __name__ == '__main__':
    main()
