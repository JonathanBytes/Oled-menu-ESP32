#ifndef BANKS_H
#define BANKS_H

const char banks[] PROGMEM = R"=====(
[
    {
      "name": "Iron Maiden",
      "presets": [
        {
          "name": "Clean",
          "onActivate": [
            {
              "type": "control_change",
              "address": 0,
              "value": 0
            },
            {
              "type": "program_change",
              "address": 0
            }
          ],
          "onDeactivate": [
            {
              "type": "control_change",
              "address": 0,
              "value": 127
            }
          ]
        },
        {
          "name": "Rythm",
          "onActivate": [
            {
              "type": "control_change",
              "address": 1,
              "value": 127
            },
            {
              "type": "program_change",
              "address": 1
            }
          ],
          "onDeactivate": [
            {
              "type": "control_change",
              "address": 1,
              "value": 0
            }
          ]
        },
        {
          "name": "Solo",
          "onActivate": [
            {
              "type": "control_change",
              "address": 2,
              "value": 127
            },
            {
              "type": "program_change",
              "address": 2
            }
          ],
          "onDeactivate": [
            {
              "type": "control_change",
              "address": 2,
              "value": 0
            }
          ]
        },
        {
          "name": "Rythm Big",
          "onActivate": [
            {
              "type": "control_change",
              "address": 3,
              "value": 127
            },
            {
              "type": "program_change",
              "address": 3
            }
          ],
          "onDeactivate": [
            {
              "type": "control_change",
              "address": 3,
              "value": 0
            }
          ]
        }
      ]
    },
    {
      "name": "Indie",
      "presets": [
        {
          "name": "Song2 Clean",
          "onActivate": [
            {
              "type": "control_change",
              "address": 4,
              "value": 127
            },
            {
              "type": "program_change",
              "address": 4
            }
          ],
          "onDeactivate": [
            {
              "type": "control_change",
              "address": 4,
              "value": 0
            }
          ]
        },
        {
          "name": "Song2 Dirt",
          "onActivate": [
            {
              "type": "control_change",
              "address": 5,
              "value": 127
            },
            {
              "type": "program_change",
              "address": 5
            }
          ],
          "onDeactivate": [
            {
              "type": "control_change",
              "address": 5,
              "value": 0
            }
          ]
        },
        {
          "name": "Take me out",
          "onActivate": [
            {
              "type": "control_change",
              "address": 6,
              "value": 127
            },
            {
              "type": "program_change",
              "address": 6
            }
          ],
          "onDeactivate": [
            {
              "type": "control_change",
              "address": 6,
              "value": 0
            }
          ]
        },
        {
          "name": "RU Mine",
          "onActivate": [
            {
              "type": "control_change",
              "address": 7,
              "value": 127
            },
            {
              "type": "program_change",
              "address": 7
            }
          ],
          "onDeactivate": [
            {
              "type": "control_change",
              "address": 7,
              "value": 0
            }
          ]
        }
      ]
    }
]
)=====";

#endif
