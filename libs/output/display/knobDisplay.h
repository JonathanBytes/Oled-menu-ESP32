int string_width;

float pixel_x = 0;
float pixel_y = 0;
float line_x = 0;
float line_y = 0;
float text_x = 0;
float text_y = 0;

int center_x = 64;
int center_y = 96;
int radius_pixel = 70;
int radius_line = 74;
int radius_text = 65;
int text_value_y = 18;
int angle;
int tick_value;

byte precalculated_x_radius_pixel[180];
byte precalculated_y_radius_pixel[180];

int tick_pixel_array[50][2];
int tick_line_array[10][4];
int tick_text_array[10][3];

int tick_pixel_count;
int tick_line_count;
int tick_text_count;


// Function to calculate tick marks
void calculateTickMarks(int potentiometer_value) {
  tick_pixel_count = 0;
  tick_line_count = 0;
  tick_text_count = 0;

  for (int i = -48; i <= 48; i += 3) {
    angle = i + ((potentiometer_value * 3)) % 3;
    tick_value = round((potentiometer_value) + angle / 3.0);

    pixel_x = precalculated_x_radius_pixel[angle + 90];
    pixel_y = precalculated_y_radius_pixel[angle + 90];

    if (pixel_x > 0 && pixel_x < 128 && pixel_y > 0 && pixel_y < 64) {
      if (tick_value >= 0 && tick_value <= 100) {
        if (tick_value % 10 == 0) {
          line_x = sin(radians(angle)) * radius_line + center_x;
          line_y = -cos(radians(angle)) * radius_line + center_y;
          tick_line_array[tick_line_count][0] = line_x;
          tick_line_array[tick_line_count][1] = line_y;
          tick_line_array[tick_line_count][2] = pixel_x;
          tick_line_array[tick_line_count][3] = pixel_y;
          tick_line_count++;

          text_x = sin(radians(angle)) * radius_text + center_x;
          text_y = -cos(radians(angle)) * radius_text + center_y;
          tick_text_array[tick_text_count][0] = text_x;
          tick_text_array[tick_text_count][1] = text_y;
          tick_text_array[tick_text_count][2] = tick_value;
          tick_text_count++;
        } else {
          tick_pixel_array[tick_pixel_count][0] = pixel_x;
          tick_pixel_array[tick_pixel_count][1] = pixel_y;
          tick_pixel_count++;
        }
      }
    }
  }
}

// Function to update the display
void drawKnob(int potentiometer_value, int updatedPotIndex) {
  calculateTickMarks(potentiometer_value);
  // Draw pixels
  for (int i = 0; i < tick_pixel_count; i++) {
    display.setPixel(tick_pixel_array[i][0], tick_pixel_array[i][1]);
  }

  // Draw lines
  for (int i = 0; i < tick_line_count; i++) {
    display.drawLine(tick_line_array[i][0], tick_line_array[i][1],
                     tick_line_array[i][2], tick_line_array[i][3]);
  }

  // Draw labels
  display.setFont(Dialog_plain_8);
  for (int i = 0; i < tick_text_count; i++) {
    string_width = display.getStringWidth(String(tick_text_array[i][2]));
    display.drawString(tick_text_array[i][0] - string_width / 2,
                       tick_text_array[i][1], String(tick_text_array[i][2]));
  }

  // Draw the big value on top
  display.setFont(ArialMT_Plain_10);
  string_width = display.getStringWidth(String(potentiometer_value) + "%");
  display.fillRect(center_x - (string_width + 4) / 2,
                   center_y - radius_line - text_value_y + 11, string_width + 4,
                   2);
  display.drawTriangle(center_x - 4, center_y - radius_line - text_value_y + 11,
                       center_x + 4, center_y - radius_line - text_value_y + 11,
                       center_x, center_y - radius_line - text_value_y + 15);
  display.drawString(center_x - string_width / 2,
                     center_y - radius_line - text_value_y,
                     String(potentiometer_value) + "%");
  display.drawString(0, 0, String(potLabels[updatedPotIndex]));
}

