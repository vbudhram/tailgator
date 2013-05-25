
//Holds all the options in the main menu screen
char *mainScreen[3] = {"1)Passive Mode", "2)Manual Mode","3)Demo Mode"};

//Holds all the options in the first option screen, which is "Passive Mode"
char *option1Screen[1] = {"Passive Mode Running"};

//Holds all the options in the second option screen, which is "Manual Mode"
char *option2Screen[1] = {"Manual Mode Running"};

char *option3Screen[1] = {"Demo Mode Running"};

//Points to the lines that is currently  displayed on the mainScreen
int mainScreenLine[2] = {0,1};

int mainScreenLineSelected = 0;

//Points to the line that is currently displayed on the option1 view
int option1Line = 0;

//Points to the line that is currently displayed on the option2 view
int option2Line = 0;

//Points to the line that is currently displayed on the option3 view
int option3Line = 0;

//Stores whether the screen is on LCD or not, 1 is true, 0 is false
int mainScreenView = 1;
int option1View = 0;
int option2View = 0;
int option3View = 0;

//Stores which state the program is in.
int passiveMode = 0;
int manualMode = 0;
int demoMode = 0;

//Variable that is flaged when screen has been updated
int updateScreen = 0;

int backLight = 1;
unsigned long backLightCount=0;

int leftSwitch=0;
int rightSwitch=0;	

int passiveModeUpdate=0;
unsigned long passiveModeCount=0;
