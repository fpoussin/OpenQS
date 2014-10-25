#include "threads.h"
#include "ssd1306.h"
#include "menu.h"
#include "string.h"

display_t display = {DISPLAY_OFF};
const char version[] = VERSION;
const char enabled[] = "Enabled";
const char disabled[] = "Disabled";

void showDiag(void);
void showInfo(void);
void setCutMode(void);
void setOutputMode(void);
void startBootloader(void);

/* Settings menu */
const menuItem_t cutModeMenuList[] = {{"Fixed", &setCutModeFixed, NULL},
                                 {"Adaptive", &setCutModeAdaptive, NULL},
                                 {"Min Time", &setCutMinTime, NULL},
				 {"Max Time", &setCutMaxTime, NULL}};
				 
const menuStruct_t cutModeMenu = {"Cut Mode", sizeof(cutModeMenuList)/sizeof(menuItem_t), cutModeMenuList};

/* Settings menu */
const menuItem_t settingsMenuList[] = {{"Cut mode", NULL, &cutModeMenu},
                                 {"Output mode", &setOutputMode, NULL},
                                 {"Shifter sensor setup", &setShifter, NULL}};

const menuStruct_t settingsMenu = {"Settings Menu", sizeof(settingsMenuList)/sizeof(menuItem_t), settingsMenuList};
/**/

/* Main menu */
const menuItem_t mainMenuItemList[] = {{"Settings", NULL, &settingsMenu},
                                 {"Diagnostics", &showDiag, NULL},
                                 {"Informations", &showInfo, NULL},
                                 {"Update", &startBootloader, NULL}};

const menuStruct_t mainMenu = {"Main Menu", sizeof(mainMenuItemList)/sizeof(menuItem_t), mainMenuItemList};
/**/

void startDisplay(void) {


    ssd1306Init(SSD1306_SWITCHCAPVCC);
    ssd1306TurnOn();
    display.state = DISPLAY_ON;

    ssd1306DrawString(40, 20, "OpenQS", Font_System7x8);
    chThdSleepMilliseconds(100); // Fails

    serDbg("startDisplay Complete\r\n");

    while (true) {

        serDbg("Display OFF\r\n");
        ssd1306TurnOff();
        display.state = DISPLAY_OFF;

        while (!BUTTON_SEL) /* Wait until the select button is pressed */
        {
            palTogglePad(GPIOC, GPIOC_LED4); /* Display heartbeat */
            chThdSleepMilliseconds(250);
        }
        serDbg("Display ON\r\n");
        ssd1306ClearScreen();
        ssd1306TurnOn();
        display.state = DISPLAY_ON;
        openMenu(&mainMenu);
    }
}

void drawTitle(char * str)
{
    const uint8_t len = Font_System7x8.u8Width*strlen(str);
    ssd1306DrawString(64-(len/2), 0, str, Font_System7x8);
}

void startBootloader(void)
{
// Reset board

}

void showDiag(void)
{
    char str[10] = "";

    while (!BUTTON_SEL) {

        drawTitle("Diagnostics");

        ssd1306DrawString(0, 30, "Shifter:", Font_System5x8);
        itoa(sensors.strain_gauge, str);
        ssd1306DrawString(45, 30, str, Font_System5x8);

        ssd1306DrawString(0, 40, "TC Switch:", Font_System5x8);
        itoa(sensors.tc_switch, str);
        ssd1306DrawString(55, 40, str, Font_System5x8);

        chThdSleepMilliseconds(100);
    }
}

void showInfo(void)
{
    drawTitle("Version");
    ssd1306DrawString(0, 10, version, Font_System5x8);

    ssd1306DrawString(0, 20, "Cut mode:", Font_System5x8);
    if (settings.data.functions == SETTINGS_CUT_ANALOG)
    {
        ssd1306DrawString(25, 20, "Analog", Font_System5x8);
    }
    else if (settings.data.functions == SETTINGS_CUT_NORMAL)
    {
        ssd1306DrawString(25, 20, "Normal", Font_System5x8);
    }
    else
    {
        ssd1306DrawString(25, 20, disabled, Font_System5x8);
    }

    while (!BUTTON_SEL) chThdSleepMilliseconds(100);
}

void setCutMode(void)
{
    drawTitle("Output Mode");

    if (settings.data.functions == SETTINGS_CUT_FIXED)
    {
        ssd1306DrawString(25, 0, "Fixed", Font_System5x8);
        settings.data.functions = SETTINGS_CUT_FIXED;
    }
    else
    {
        ssd1306DrawString(25, 0, "Adaptive", Font_System5x8);
        settings.data.functions = SETTINGS_CUT_ADAPTIVE;
    }
    writeSettings(&settings);
    chThdSleepMilliseconds(2000);
}

void setOutputMode(void)
{
    drawTitle("Output Mode");

    if (settings.data.functions == SETTINGS_OUTPUT_NORMAL)
    {
        ssd1306DrawString(25, 0, "Analog", Font_System5x8);
        settings.data.functions = SETTINGS_OUTPUT_ANALOG;
    }
    else
    {
        ssd1306DrawString(25, 0, "Normal", Font_System5x8);
        settings.data.functions = SETTINGS_OUTPUT_NORMAL;
    }
    writeSettings(&settings);
    chThdSleepMilliseconds(2000);
}

void setShifter(void)
{
    drawTitle("Shifter Sensor Setup");

    uint8_t i;
    uint16_t peak;

    ssd1306DrawString(0, 25, "Shift a gear", Font_System5x8);
    ssd1306DrawString(10, 10, "to detect direction", Font_System5x8);

    chThdSleepMilliseconds(2000);

    peak = 0;
    for (i=0; i<40; i++)
    {
        if (sensors.strain_gauge >= peak)
            peak = sensors.strain_gauge;

        chThdSleepMilliseconds(100);
    }

    ssd1306ClearScreen();

    /* Peak >= 1.65v */
    if (peak >= 0x8000)
    {
        ssd1306DrawString(0, 10, "Normal direction", Font_System5x8);
        settings.data.sensor_direction = SETTINGS_SENSOR_NORMAL;
    }
    else
    {
        ssd1306DrawString(0, 5, "Reverse direction", Font_System5x8);
        settings.data.sensor_direction = SETTINGS_SENSOR_REVERSE;
    }

    settings.data.sensor_threshold = peak;
    writeSettings(&settings);

    chThdSleepMilliseconds(2000);

    while (!BUTTON_SEL) chThdSleepMilliseconds(100);
}
