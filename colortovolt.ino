// Pin Definitions
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define OUT 6

// Color voltage mapping
const char* colorNames[] = {
  "Light Gold", "Gold", "Purple", "Blue", "Light Blue", 
  "Green", "Yellow", "Pink", "Magenta", "Light Green", 
  "Cyan", "Orange", "Red", "Violet", "Dark Blue"
};

const int voltageValues[] = {
  15, 20, 25, 30, 35, 
  40, 45, 50, 55, 60, 
  65, 70, 75, 80, 85
};

// Number of color mappings
const int numColors = sizeof(colorNames) / sizeof(colorNames[0]);

// Thresholds for color detection (these may need to be calibrated)
const int colorThresholds[numColors] = {
  1500, 1400, 1300, 1200, 1100, 
  1000, 900, 800, 700, 600, 
  500, 400, 300, 200, 100
};

void setup() {
  Serial.begin(9600);
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  
  digitalWrite(S0, HIGH); // Set frequency scaling to 100%
  digitalWrite(S1, LOW);
}

void loop() {
  // Read Red Color
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int red = pulseIn(OUT, LOW);
  
  // Read Green Color
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int green = pulseIn(OUT, LOW);
  
  // Read Blue Color
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int blue = pulseIn(OUT, LOW);
  
  // Calculate the average intensity
  int average = (red + green + blue) / 3;
  
  // Determine the closest color
  int closestColorIndex = -1;
  int minDifference = 100000; // A large number for initial comparison

  for (int i = 0; i < numColors; i++) {
    int difference = abs(average - colorThresholds[i]);
    if (difference < minDifference) {
      minDifference = difference;
      closestColorIndex = i;
    }
  }
  
  // Output the color and the corresponding voltage
  if (closestColorIndex >= 0 && closestColorIndex < numColors) {
    Serial.print("Detected Color: ");
    Serial.print(colorNames[closestColorIndex]);
    Serial.print("\tVoltage Value: ");
    Serial.println(voltageValues[closestColorIndex]);
  } else {
    Serial.println("Color not recognized");
  }
  
  delay(500); // Delay before the next reading
}
